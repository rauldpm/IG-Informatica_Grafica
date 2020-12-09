/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#define ESC '\x1B'

#include <GL/glut.h>
#include <GL/gl.h>
#include "escena.h"

using namespace std;

//******************************************************************************
// Constructor de la escena
//******************************************************************************
Escena::Escena(){

  //**************************************************************************//
  
  Front_plane=50;
  Back_plane=2000;  
  ejes.changeAxisSize(5000);
  
  //**************************************************************************//
  
  modo                 = 1;
  modoF                = 1;
  modoFigura           = false;
  modoDibujado         = false;
  modoIluminacion      = false;
  modoSombreado        = false;
  modoTextura          = false;
  modoVariarTapas      = false;
  modoVariarRevolucion = true;
  modoMovimiento       = false;
  modoDibujadoArchivo  = 'a';
  modoCamara           = false;

  //**************************************************************************//

  char opcion;
  do{
    std::cout << "¿Leer archivo externo? (S/N)?: ";
    std::cin >> opcion;
  }while(opcion != 'S' && opcion != 'N');

  if(opcion == 'S') {
    std::cout << "Archivo a dibujar: ";
    string archivoTemp;
    std::cin >> archivoTemp;
    const char *archivo = archivoTemp.c_str();

    do{
      std::cout << "Dibujado por Revolucion o Carga (R/C): ";
      std::cin >> opcion;
    }while(opcion != 'R' && opcion != 'C');

    modoDibujadoArchivo = opcion;
    if(opcion == 'R') revolucion = new Revolucion(archivo,50);
    else if(opcion == 'C') ply = new Ply(archivo);
  }
  else if(opcion == 'N'){
    do{
      std::cout << "¿Revolucion por teclado? (S/N): ";
      std::cin >> opcion;
    }while(opcion != 'S' && opcion != 'N');
    if(opcion == 'S') {
      revolucion = new Revolucion();
      revolucion-> leerVertTeclado();
    }
    else{
      //Prueba 2 Practicas IG - Generar objeto revolucion a partir de un perfil dado al reves
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
  do{
    std::cout << "¿Cargar textura personalizada? (S/N)?: ";
    std::cin >> opcion;
  }while(opcion != 'S' && opcion != 'N');
  if(opcion == 'S'){
    std::cout << "Archivo a dibujar: ";
    string archivoTemp;
    std::cin >> archivoTemp;
    const char *archivo = archivoTemp.c_str();
    textura = new Textura(archivo);
  }
  else textura = new Textura("data/imagenes_texturas/logo.jpg");


  //Se introducen valores iniciales personalizados de las luces 2 y 3
  luz2->setPosicion(0,6.0);
  luz2->setPosicion(1,0.0);
  luz2->setPosicion(2,0.0);
  luz2->setPosicion(3,0.0);

  luz3->setPosicion(0,0.0);
  luz3->setPosicion(1,9.0);
  luz3->setPosicion(2,0.0);
  luz3->setPosicion(3,1.0);

  camaraActiva = 0;

  camaras.push_back(camara0);
  camaras.push_back(camara1);
  camaras.push_back(camara2);

  //**************************************************************************//
}

//******************************************************************************
// Funcion que inicializa la escena
//******************************************************************************
void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);    //se indica el color para limpiar la ventana	(r,v,a,al)
	glEnable(GL_DEPTH_TEST);	//se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
}

//******************************************************************************
// Funcion que dibuja objetos en la escena
//******************************************************************************
void Escena::draw_objects() {

  luz1->iluminar(GL_LIGHT1);  //Posicional
  luz2->iluminar(GL_LIGHT2);  //Direccional
  luz3->iluminar(GL_LIGHT3);  //Direccional

  switch (modoF) {
    //Dibujado del octaedro
    case 1: octaedro->dibujar(modo);  break;
    //Dibujado del tetraedro
    case 2: tetraedro->dibujar(modo); break;
    //Dibujado del cubo
    case 3: cubo->dibujar(modo); break;
    //Dibujado de carga de un archivo ply
    case 4: if(modoDibujadoArchivo == 'C') ply->dibujar(modo); break;
    //Dibujado por revolucion de un perfil ply
    case 5: if(modoDibujadoArchivo == 'R'){
              if(modoVariarRevolucion || modoVariarTapas) revolucion->nuevosVertInd(revolucion->getEstadoTapa());
                modoVariarRevolucion = false;
                modoVariarTapas = false;
                revolucion->dibujar(modo);
              }
            break;
    //Dibujado del Modelo Jerarquico
    case 6: if(jerarquico->getModoAnimacion()){
              jerarquico->dibujarJ(modo);
              jerarquico->animacion();
            }
            else jerarquico->dibujarJ(modo);
            break;
    case 7: textura->setTextura(modo); textura->setVertTex(); break;
  }
  change_projection();
}

//******************************************************************************
// Funcion que dibuja la escena
//******************************************************************************
void Escena::dibujar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //Limpiar la pantalla
  if(modoF != 5) glEnable(GL_CULL_FACE);
  else glDisable(GL_CULL_FACE);
	change_observer();
	draw_axis();
	draw_objects();
}

//******************************************************************************
// Funcion que detecta la tecla pulsada
//******************************************************************************
int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {
  //std::cout << "Tecla" << Tecla1<< std::endl;

  //Acciones sobre objetos, dibujado de objetos y objeto revolucion/ply
  if(modoMovimiento){
    switch (Tecla1) {
      case '1': if(luz1->getIluminacion()){ luz1->setPosicion(0,luz1->getPosicion(0)-1);
                                            jerarquico->setGradoLibertadLuz1(0, jerarquico->getGradoLibertadLuz1(0) - 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(0,luz2->getPosicion(0)-1);
                                            jerarquico->setGradoLibertadLuz2(0, jerarquico->getGradoLibertadLuz2(0) - 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(0,luz3->getPosicion(0)-1);
                                            jerarquico->setGradoLibertadLuz3(0, jerarquico->getGradoLibertadLuz3(0) - 1);
                                          }
                break;
      case '2': if(luz1->getIluminacion()){ luz1->setPosicion(1,luz1->getPosicion(1)-1);
                                            jerarquico->setGradoLibertadLuz1(1, jerarquico->getGradoLibertadLuz1(1) - 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(1,luz2->getPosicion(1)-1);
                                            jerarquico->setGradoLibertadLuz2(1, jerarquico->getGradoLibertadLuz2(1) - 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(1,luz3->getPosicion(1)-1);
                                            jerarquico->setGradoLibertadLuz3(1, jerarquico->getGradoLibertadLuz3(1) - 1);
                                          }
                break;
      case '3': if(luz1->getIluminacion()){ luz1->setPosicion(2,luz1->getPosicion(2)-1);
                                            jerarquico->setGradoLibertadLuz1(2, jerarquico->getGradoLibertadLuz1(2) - 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(2,luz2->getPosicion(2)-1);
                                            jerarquico->setGradoLibertadLuz2(2, jerarquico->getGradoLibertadLuz2(2) - 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(2,luz3->getPosicion(2)-1);
                                            jerarquico->setGradoLibertadLuz3(2, jerarquico->getGradoLibertadLuz3(2) - 1);
                                          }
                break;
      case '4': if(luz1->getIluminacion()){ luz1->setPosicion(0,luz1->getPosicion(0)+1);
                                            jerarquico->setGradoLibertadLuz1(0, jerarquico->getGradoLibertadLuz1(0) + 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(0,luz2->getPosicion(0)+1);
                                            jerarquico->setGradoLibertadLuz2(0, jerarquico->getGradoLibertadLuz2(0) + 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(0,luz3->getPosicion(0)+1);
                                            jerarquico->setGradoLibertadLuz3(0, jerarquico->getGradoLibertadLuz3(0) + 1);
                                          }

                break;
      case '5': if(luz1->getIluminacion()){ luz1->setPosicion(1,luz1->getPosicion(1)+1);
                                            jerarquico->setGradoLibertadLuz1(1, jerarquico->getGradoLibertadLuz1(1) + 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(1,luz2->getPosicion(1)+1);
                                            jerarquico->setGradoLibertadLuz2(1, jerarquico->getGradoLibertadLuz2(1) + 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(1,luz3->getPosicion(1)+1);
                                            jerarquico->setGradoLibertadLuz3(1, jerarquico->getGradoLibertadLuz3(1) + 1);
                                          }
                break;
      case '6': if(luz1->getIluminacion()){ luz1->setPosicion(2,luz1->getPosicion(2)+1);
                                            jerarquico->setGradoLibertadLuz1(2, jerarquico->getGradoLibertadLuz1(2) + 1);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(2,luz2->getPosicion(2)+1);
                                            jerarquico->setGradoLibertadLuz2(2, jerarquico->getGradoLibertadLuz2(2) + 1);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(2,luz3->getPosicion(2)+1);
                                            jerarquico->setGradoLibertadLuz3(2, jerarquico->getGradoLibertadLuz3(2) + 1);
                                          }
                break;
      case '7': if(luz1->getIluminacion()){ luz1->setPosicion(0,0);
                                            jerarquico->setGradoLibertadLuz1(0, 0);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(0,0);
                                            jerarquico->setGradoLibertadLuz2(0, 0);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(0,0);
                                            jerarquico->setGradoLibertadLuz3(0, 0);
                                          }
                break;
      case '8': if(luz1->getIluminacion()){ luz1->setPosicion(1,0);
                                            jerarquico->setGradoLibertadLuz1(1, 0);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(1,0);
                                            jerarquico->setGradoLibertadLuz2(1, 0);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(1,0);
                                            jerarquico->setGradoLibertadLuz3(1, 0);
                                          }
                break;
      case '9': if(luz1->getIluminacion()){ luz1->setPosicion(2,0);
                                            jerarquico->setGradoLibertadLuz1(2, 0);
                                          }
                if(luz2->getIluminacion()){ luz2->setPosicion(2,0);
                                            jerarquico->setGradoLibertadLuz2(2, 0);
                                          }
                if(modoF == 6 && luz3->getIluminacion()){ luz3->setPosicion(2,0);
                                            jerarquico->setGradoLibertadLuz3(2, 0);
                                          }
                break;
    }
  }
  else if(modoCamara){
    switch(Tecla1){
      case 'w': camaras[camaraActiva]->avanzar(); break;
      case 's': camaras[camaraActiva]->retroceder(); break;
      case 'a': camaras[camaraActiva]->izquierda(); break;
      case 'd': camaras[camaraActiva]->derecha(); break;
      case 'r': camaras[camaraActiva]->restablecer(); break;
    }
  }
  else if(modoFigura){
    modoFigura = false;
    modoMovimiento = false;
    switch (Tecla1) {
      //Figura seleccionada: Octaedro
      case '1': modoF = 1; break;
      //Figura seleccionada: Tetraedro
      case '2': modoF = 2; break;
      //Figura seleccionada: Cubo
      case '3': modoF = 3; break;
      //Figura seleccionada: Archivo PLY
      case '4': modoF = 4; break;
      //Figura seleccionada: Archivo revolucion
      case '5': modoF = 5; break;
      //Figura seleccionada: Modelo Jerarquico
      case '6': modoF = 6; break;
      //Figura seleccionada: Tablero
      case '7': modoF = 7; break;
    }
  }
  else if(modoDibujado){
    modoDibujado = false;
    modoMovimiento = false;
    switch (Tecla1) {
      //Puntos
      case '1': modo = 1; break;
      //Lineas/Aristas
      case '2': modo = 2; break;
      //Relleno
      case '3': modo = 3; break;
      //Ajedrez
      case '4': modo = 4; break;
      //Modo Prueba 1 -> Combinacion de Puntos, Aristas y Relleno
      case '5': modo = 5; break;
    }
  }
  else if(modoF == 6){
    switch (Tecla1) {

      //****************************************************//

      //Aumento de la rotacion de la jerarquico en el eje y
      case 'Z': jerarquico->setGradoLibertad(0, jerarquico->getGradoLibertad(0) + jerarquico->getVelocidad(0)); break;
      //Disminucion de la rotacion de la jerarquico en el eje y
      case 'z': jerarquico->setGradoLibertad(0, jerarquico->getGradoLibertad(0) -jerarquico->getVelocidad(0)); break;
      //Aumento de la traslacion del brazo extensible de la jerarquico
      case 'X': if(jerarquico->getGradoLibertad(1) <= 2) jerarquico->setGradoLibertad(1, jerarquico->getGradoLibertad(1) + jerarquico->getVelocidad(1)); break;
      //Disminucion de la traslacion del brazo extensible de la jerarquico
      case 'x': if(jerarquico->getGradoLibertad(1) > 0) jerarquico->setGradoLibertad(1, jerarquico->getGradoLibertad(1) - jerarquico->getVelocidad(1)); break;
      //Aumento de la traslacion de la carga de la jerarquico
      case 'C': if(jerarquico->getGradoLibertad(2) >= -3) jerarquico->setGradoLibertad(2, jerarquico->getGradoLibertad(2) - jerarquico->getVelocidad(2)); break;
      //Disminucion de la traslacion de la carga de la jerarquico
      case 'c': if(jerarquico->getGradoLibertad(2) < 0) jerarquico->setGradoLibertad(2, jerarquico->getGradoLibertad(2) + jerarquico->getVelocidad(2));  break;
      //Aumento de la translacion de la cuerda PRUEBA 3
      case 'V': if(jerarquico->getGradoLibertad(1) > 2 && jerarquico->getGradoLibertad(3) < 0) jerarquico->setGradoLibertad(3, jerarquico->getGradoLibertad(3) + jerarquico->getVelocidad(3)); break;
      //Disminucion de la translacion de la cuerda PRUEBA 3
      case 'v': if(jerarquico->getGradoLibertad(1) > 2 && jerarquico->getGradoLibertad(3) > -2) jerarquico->setGradoLibertad(3, jerarquico->getGradoLibertad(3) - jerarquico->getVelocidad(3)); break;

      //****************************************************//

      //Aumento velocidad grado libertad 1
      case 'A': jerarquico->setVelocidad(0, jerarquico->getVelocidad(0)+1); break;
      //Disminucion velocidad grado libertad 1
      case 'a': jerarquico->setVelocidad(0, jerarquico->getVelocidad(0)-1); break;
      //Aumento velocidad grado libertad 2
      case 'S': jerarquico->setVelocidad(1, jerarquico->getVelocidad(1)+0.1); break;
      //Disminucion velocidad grado libertad 2
      case 's': if(jerarquico->getVelocidad(1)-0.1 > 0) jerarquico->setVelocidad(1, jerarquico->getVelocidad(1)-0.1); break;
      //Aumento velocidad grado libertad 3
      case 'D': jerarquico->setVelocidad(2, jerarquico->getVelocidad(2)+0.1); break;
      //Disminucion velocidad grado libertad 3
      case 'd': if(jerarquico->getVelocidad(2)-0.1 > 0) jerarquico->setVelocidad(2, jerarquico->getVelocidad(2)-0.1); break;
      //Aumento velocidad grado libertad 4
      case 'F': jerarquico->setVelocidad(3, jerarquico->getVelocidad(3)+0.1); break;
      //Disminucion velocidad grado libertad 4
      case 'f': jerarquico->setVelocidad(3, jerarquico->getVelocidad(3)-0.1); break;

      //****************************************************//

      //Puesta a 0 de la velocidad del grado de libertad 1
      case 'q': jerarquico->setVelocidad(0, 0); break;
      //Puesta a 0 de la velocidad del grado de libertad 2
      case 'w': jerarquico->setVelocidad(1, 0); break;
      //Puesta a 0 de la velocidad del grado de libertad 3
      case 'e': jerarquico->setVelocidad(3, 0); break;

      //****************************************************//

      //Activa la animacion de la jerarquico
      case 'R': jerarquico->setModoAnimacion(true); break;
      //Desactiva la animacion de la jerarquico
      case 'r': jerarquico->setModoAnimacion(false); break;

      //****************************************************//
    }
  }
  else if(modoF == 5){
    switch (Tecla1) {

      //****************************************************//

      //Tapas OFF
      case 'T': revolucion->setEstadoTapa(false); modoVariarTapas = true; break;
      //Tapas ON
      case 't': revolucion->setEstadoTapa(true); modoVariarTapas = true;break;

      //****************************************************//

      //Aumento de revoluciones
      case '+': revolucion->aumentarRevoluciones(); modoVariarRevolucion = true; break;
      //Disminucion de revoluciones
      case '-': revolucion->reducirRevoluciones(); modoVariarRevolucion = true; break;

      //****************************************************//
    }
  }

  //Acciones globales sobre toda la escena
  switch (Tecla1) {
    case ESC: return 1;
    case 'p': modoFigura   = true; break;
    case 'o': modoDibujado = true; break;
    case 'm': if(!modoMovimiento){ modoMovimiento = true; }
              else{modoMovimiento = false;}
              break;
    case 'y': if(!modoSombreado){
                modoSombreado = true;
                glShadeModel(GL_SMOOTH);
              }
              else{
                modoSombreado = false;
                glShadeModel(GL_FLAT);
              }
              break;
    case 'i': if(!modoIluminacion){
                modoIluminacion = true;
                glEnable(GL_NORMALIZE);
                glEnable(GL_LIGHTING);
              }
              else{
                modoIluminacion = false;
                glDisable(GL_NORMALIZE);
                glDisable(GL_LIGHTING);
              }
              break;
    case 'u': if(!modoTextura && modoF == 7){
                modoTextura = true;
                glEnable(GL_TEXTURE_2D);
              }
              else{
                modoTextura = false;
                glDisable(GL_TEXTURE_2D);
              }
              break;
    case 'l': if(!modoCamara) modoCamara = true;
              else modoCamara = false;
  }

  return 0;
}

//******************************************************************************
// Funcion que detecta la tecla especial pulsada
//******************************************************************************
void Escena::teclaEspecial(int Tecla1,int x,int y) {
  if(modoCamara) {
    switch (Tecla1){
      case GLUT_KEY_F1:
        modoCamara=false;
        camaraActiva = 0;
        break;
      case GLUT_KEY_F2:
        modoCamara=false;
        camaraActiva = 1;
        break;
      case GLUT_KEY_F3:
        modoCamara=false;
        camaraActiva = 2;
        break;
    }
  }
  else{   
    switch (Tecla1){
    	case GLUT_KEY_LEFT:      camaras[camaraActiva]->disminuirObserverAngleY();break;
    	case GLUT_KEY_RIGHT:     camaras[camaraActiva]->aumentarObserverAngleY(); break;
    	case GLUT_KEY_UP:        camaras[camaraActiva]->disminuirObserverAngleX();break;
    	case GLUT_KEY_DOWN:      camaras[camaraActiva]->aumentarObserverAngleX(); break;
    	case GLUT_KEY_PAGE_DOWN: if(camaras[camaraActiva]->getZoom() > 1) camaras[camaraActiva]->disminuirZoom();break;
      case GLUT_KEY_PAGE_UP:   camaras[camaraActiva]->aumentarZoom(); break; 

      //Activa Luz 1
      case GLUT_KEY_F1: if(!luz1->getIluminacion()){ luz1->setIluminacion(true); glEnable(GL_LIGHT1); }
                        else{ luz1->setIluminacion(false); glDisable(GL_LIGHT1); }
                        break;
      //Activa Luz 2
      case GLUT_KEY_F2: if(!luz2->getIluminacion()){ luz2->setIluminacion(true); glEnable(GL_LIGHT2); }
                        else{ luz2->setIluminacion(false); glDisable(GL_LIGHT2); }
                        break;
      //Activar luz 3
      case GLUT_KEY_F3: if(modoF == 6){
                          if(!luz3->getIluminacion()){ luz3->setIluminacion(true); glEnable(GL_LIGHT3); }
                          else{ luz3->setIluminacion(false); glDisable(GL_LIGHT3); }
                        }
                        break;
      //Modifica Pos Luz 1
      case GLUT_KEY_F4: if(luz1->getIluminacion()) luz1->cambiar('x'); break;
      //Modifica Pos Luz 2
      case GLUT_KEY_F5: if(luz2->getIluminacion()) luz2->cambiar('y'); break;
      //Activar Material 1
      case GLUT_KEY_F6: material->setMaterial1(); material->asignarMaterial(); break;
      //Activar Material 2
      case GLUT_KEY_F7: material->setMaterial2(); material->asignarMaterial(); break;
      //Activar Material 3
      case GLUT_KEY_F8: material->setMaterial3(); material->asignarMaterial(); break;
      //Activar Material 4
      case GLUT_KEY_F9: material->setMaterial4(); material->asignarMaterial(); break;
    }
  }
}

//**************************************************************************
// Funcion para definir la transformacion de proyeccion
//***************************************************************************
void Escena::change_projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int zoom = camaras[camaraActiva]->getZoom();
  
  if(camaraActiva==2) glOrtho(-Width/zoom*ratio,Width/zoom*ratio,-Height/zoom*ratio,Height/zoom*ratio,Front_plane,Back_plane);
  else glFrustum(-Width/zoom*ratio,Width/zoom*ratio,-Height/zoom*ratio,Height/zoom*ratio,Front_plane,Back_plane);
}

//******************************************************************************
// Funcion que redimensiona la escena
//******************************************************************************
void Escena::redimensionar(int newWidth,int newHeight) {
  change_projection();
  ratio = newWidth/newHeight;
  Width=newWidth/10;
  Height=newHeight/10;
  glViewport(0,0,newWidth,newHeight);
}

//**************************************************************************
// Funcion para definir la transformacion de vista (posicionar la camara)
//***************************************************************************
void Escena::change_observer() {
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  camaras[camaraActiva]->setObservador();
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void Escena::draw_axis() {
  glDisable(GL_LIGHTING);
  ejes.draw();
  if(modoIluminacion) glEnable(GL_LIGHTING);
}

//******************************************************************************
// Funcion que obtiene el objeto jerarquico
//******************************************************************************
Jerarquico Escena::getJerarquico(){
  return *jerarquico;
}

void Escena::girarCamaraActiva(int x, int y){
  camaras[camaraActiva]->girar(x,y);
}
