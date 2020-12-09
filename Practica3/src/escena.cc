/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#define ESC '\x1B'

#include <GL/gl.h>
#include <GL/glut.h>

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "ply.h"
#include "revolucion.h"
#include "grua.h"
#include "escena.h"

Escena::Escena(){

  Front_plane=50;
  Back_plane=2000;
  Observer_distance = 4*Front_plane;
  Observer_angle_x = Observer_angle_y=0;
  ejes.changeAxisSize(5000);

  char opcion;
  do{
    std::cout << "Quiere dibujar un archivo externo (S/N) o quiere introducir vertices para revolucionar por teclado? (T): ";
    std::cin >> opcion;
    opcion = toupper(opcion);
  }while(opcion != 'S' && opcion != 'N' && opcion != 'T');

  if(opcion == 'S'){
    std::cout << "Introduzca el nombre del archivo a dibujar: ";
    string archivoTemp;
    std::cin >> archivoTemp;
    const char *archivo = archivoTemp.c_str();

    do{
      std::cout << "Quiere dibujarlo mediante Revolucion o Carga (R/C): ";
      std::cin >> opcion;
      opcion = toupper(opcion);
    }while(opcion != 'R' && opcion != 'C');

    modoDibujadoArchivo = opcion;
    if(opcion == 'R') revolucion = new Revolucion(archivo,30);
    else if(opcion == 'C') ply = new Ply(archivo);
  }
  else if(opcion == 'T'){
    revolucion = new Revolucion();
    revolucion-> leerVertTeclado();
    modoDibujadoArchivo = 'R';
  }
  else{
    //Prueba 2 Practicas IG - Generar objeto revolucion a partir de un perfil dado al reves
    std::cout << std::endl << "Cargando datos de la prueba 2 como Revolucion" << std::endl << std::endl;
    vector<float> vPrueba;
    vPrueba.push_back(3);   vPrueba.push_back(5);   vPrueba.push_back(0);       //Vertice 0 (3,5,0)
    vPrueba.push_back(3);   vPrueba.push_back(4);   vPrueba.push_back(0);       //Vertice 1 (3,4,0)
    vPrueba.push_back(3);   vPrueba.push_back(3);   vPrueba.push_back(0);       //Vertice 2 (3,3,0)
    vPrueba.push_back(2);   vPrueba.push_back(2);   vPrueba.push_back(0);       //Vertice 3 (2,2,0)
    vPrueba.push_back(1.5); vPrueba.push_back(1);   vPrueba.push_back(0);       //Vertice 4 (1.5,1,0)
    vPrueba.push_back(1);   vPrueba.push_back(0);   vPrueba.push_back(0);       //Vertice 5 (1,0,0)
    revolucion = new Revolucion(vPrueba,30);
    modoDibujadoArchivo = 'R';
  }
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {
  switch (modoF) {
    //Dibujado del octaedro
    case 0: octaedro->dibujar(modo); break;
    //Dibujado del tetraedro
    case 1: tetraedro->dibujar(modo); break;
    //Dibujado del cubo
    case 2: cubo->dibujar(modo); break;
    //Dibujado de carga de un archivo ply
    case 3: if(modoDibujadoArchivo == 'C') ply->dibujar(modo); break;
    //Dibujado por revolucion de un perfil ply
    case 4:
      if(modoDibujadoArchivo == 'R'){
        //Se hace la figura con las revoluciones nuevas indicando se se crea con o sin tapas
        if(modoVariarRevolucion || modoVariarTapas) revolucion->nuevosVertInd(revolucion->getEstadoTapa());
        //Dibujado de revolucion desde un archivo
        revolucion->dibujar(modo);
      }
      break;
    //Dibujado del Modelo Jerarquico
    case 5:
      //Si se indica que se haga la nimacion, se dibuja el objeto y se anima
      if(grua->getModoAnimacion()) {grua->dibujarJ(modo); grua->animacion();}
      //Sino, se dibuja la figura con los ultimos valores que tenga la grua
      else grua->dibujarJ(modo);
      break;
  }

  change_projection();
  //Se resetean las variables que indican que se ha procedido a cambiar un estado
  modoVariarRevolucion = false;
  modoVariarTapas = false;
}

void Escena::dibujar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
  glEnable(GL_CULL_FACE);
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {
  std::cout << "Tecla" << Tecla1<< std::endl;
  switch(Tecla1){
    //Puntos
    case 'p': modo = 0; break;
    //Lineas/Aristas
    case 'l': modo = 1; break;
    //Relleno
    case 'f': modo = 2; break;
    //Ajedrez
    case 'v': modo = 3; break;
    //Modo Prueba 1 -> Combinacion de Puntos, Aristas y Relleno
    case 'h': modo = 4; break;
    //Tapas OFF
    case 'T': if(modoF == 4){revolucion->setEstadoTapa(false); modoVariarTapas = true;} break;
    //Tapas ON
    case 't': if(modoF == 5){revolucion->setEstadoTapa(true); modoVariarTapas = true;} break;
    //Aumento de revoluciones
    case '+': if(modoF == 4 && modoDibujadoArchivo == 'R'){revolucion->aumentarRevoluciones(); modoVariarRevolucion = true;} break;
    //Disminucion de revoluciones
    case '-': if(modoF == 4 && modoDibujadoArchivo == 'R'){revolucion->reducirRevoluciones(); modoVariarRevolucion = true;} break;
    //Aumento del zoom
    case '*': zoom++; break;
    //Disminucion del zoom
    case '/': zoom--; break;
    //Aumento de la rotacion de la grua en el eje y
    case 'Z': if(modoF == 5) grua->setGradoLibertad(0, grua->getGradoLibertad(0) + grua->getVelocidad(0)); break;
    //Disminucion de la rotacion de la grua en el eje y
    case 'z': if(modoF == 5) grua->setGradoLibertad(0, grua->getGradoLibertad(0) -grua->getVelocidad(0)); break;
    //Aumento de la traslacion del brazo extensible de la grua
    case 'X': if(modoF == 5 && grua->getGradoLibertad(1) <= 2) grua->setGradoLibertad(1, grua->getGradoLibertad(1) + grua->getVelocidad(1)); break;
    //Disminucion de la traslacion del brazo extensible de la grua
    case 'x': if(modoF == 5 && grua->getGradoLibertad(1) > 0) grua->setGradoLibertad(1, grua->getGradoLibertad(1) - grua->getVelocidad(1)); break;
    //Aumento de la traslacion de la carga de la grua
    case 'C': if(modoF == 5 && grua->getGradoLibertad(2) >= -3) grua->setGradoLibertad(2, grua->getGradoLibertad(2) - grua->getVelocidad(2)); break;
    //Disminucion de la traslacion de la carga de la grua
    case 'c': if(modoF == 5 && grua->getGradoLibertad(2) < 0) grua->setGradoLibertad(2, grua->getGradoLibertad(2) + grua->getVelocidad(2));  break;
    //Activa la animacion de la grua
    case 'A': if(modoF == 5) grua->setModoAnimacion(true); break;
    //Desactiva la animacion de la grua
    case 'a': if(modoF == 5) grua->setModoAnimacion(false); break;
    //Aumento velocidad grado libertad 1
    case 'B': if(modoF == 5) grua->setVelocidad(0, grua->getVelocidad(0)+1); break;
    //Disminucion velocidad grado libertad 1
    case 'b': if(modoF == 5) grua->setVelocidad(0, grua->getVelocidad(0)-1); break;
    //Aumento velocidad grado libertad 2
    case 'N': if(modoF == 5) grua->setVelocidad(1, grua->getVelocidad(1)+0.1); break;
    //Disminucion velocidad grado libertad 2
    case 'n': if(modoF == 5 && grua->getVelocidad(1)-0.1 > 0) grua->setVelocidad(1, grua->getVelocidad(1)-0.1); break;
    //Aumento velocidad grado libertad 3
    case 'M': if(modoF == 5) grua->setVelocidad(2, grua->getVelocidad(2)+0.1); break;
    //Disminucion velocidad grado libertad 1
    case 'm': if(modoF == 5 && grua->getVelocidad(2)-0.1 > 0) grua->setVelocidad(2, grua->getVelocidad(2)-0.1); break;
    //Puesta a 0 de la velocidad del grado de libertad 1
    case 'q': if(modoF == 5) grua->setVelocidad(0, 0); break;
    //Puesta a 0 de la velocidad del grado de libertad 2
    case 'w': if(modoF == 5) grua->setVelocidad(1, 0); break;
    //Puesta a 0 de la velocidad del grado de libertad 3
    case 'e': if(modoF == 5) grua->setVelocidad(3, 0); break;
    //Aumento velocidad grado libertad 4
    case ';': if(modoF == 5) grua->setVelocidad(3, grua->getVelocidad(3)+0.1); break;
    //Disminucion velocidad grado libertad 4
    case ',': if(modoF == 5) grua->setVelocidad(3, grua->getVelocidad(3)-0.1); break;
    //Aumento de la translacion de la cuerda PRUEBA 3
    case 'S': if(modoF == 5 && grua->getGradoLibertad(1) > 2 && grua->getGradoLibertad(3) < 0) grua->setGradoLibertad(3, grua->getGradoLibertad(3) + grua->getVelocidad(3)); break;
    //Disminucion de la translacion de la cuerda PRUEBA 3
    case 's': if(modoF == 5 && grua->getGradoLibertad(1) > 2 && grua->getGradoLibertad(3) > -2) grua->setGradoLibertad(3, grua->getGradoLibertad(3) - grua->getVelocidad(3)); break;
    //Figura seleccionada: Octaedro
    case '0': modoF = 0; break;
    //Figura seleccionada: Tetraedro
    case '1': modoF = 1; break;
    //Figura seleccionada: Cubo
    case '2': modoF = 2; break;
    //Figura seleccionada: Archivo PLY
    case '3': modoF = 3; break;
    //Figura seleccionada: Archivo revolucion
    case '4': modoF = 4; break;
    //Figura seleccionada: Modelo Jerarquico
    case '5': modoF = 5; break;
  }
  //Si se presiona Esc se sale del programa
  if (toupper(Tecla1)==ESC) return 1;
	else return 0;
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width/zoom,Width/zoom,-Height/zoom,Height/zoom,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}

//Metodo para acceder desde practica3.cc al objeto Grua de escena
Grua Escena::getGrua(){
  return *grua;
}
