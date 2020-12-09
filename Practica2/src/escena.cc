/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "escena.h"
#include "figura.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "ply.h"
#include "revolucion.h"


using namespace std;

Escena::Escena(){
  Front_plane=50;
  Back_plane=2000;
  Observer_distance = 4*Front_plane;
  Observer_angle_x = Observer_angle_y=0;
  ejes.changeAxisSize(5000);

  //Inicializacion de las figuras Tetraedro, Cubo, Octaedro y Revolucion (lectura desde teclado)
  tetraedro = new Tetraedro();
  cubo = new Cubo();
  octaedro = new Octaedro();

  //******************************************//

  vector<float> vPrueba;
  vPrueba.push_back(3);   vPrueba.push_back(5);   vPrueba.push_back(0);         //Vertice 0 (3,5,0)
  vPrueba.push_back(3);   vPrueba.push_back(4);   vPrueba.push_back(0);         //Vertice 1 (3,4,0)
  vPrueba.push_back(3);   vPrueba.push_back(3);   vPrueba.push_back(0);         //Vertice 2 (3,3,0)
  vPrueba.push_back(2);   vPrueba.push_back(2);   vPrueba.push_back(0);         //Vertice 3 (2,2,0)
  vPrueba.push_back(1.5); vPrueba.push_back(1);   vPrueba.push_back(0);         //Vertice 4 (1.5,1,0)
  vPrueba.push_back(1);   vPrueba.push_back(0);   vPrueba.push_back(0);         //Vertice 5 (1,0,0)

  char op;
  do{
    std::cout << "Quieres leer por teclado? S/N: ";
    std::cin >> op;
  }
  while(toupper(op)!='S' && toupper(op)!='N');
  if(op == 'N'){
     revolucion = new Revolucion(vPrueba);
     tipoPLY = "r";
   }
  else{
    revolucion = new Revolucion();
    tipoPLY = "r";
    revolucion->leerVertTeclado();
  }
}

Escena::Escena(char **argv){

    //Para seleccionar entre carga ply y revolucion
    tipoPLY = argv[2];
    string sr = "r", sc = "c";

    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);

    //Inicializacion de las figuras Tetraedro, Cubo, Octaedro, Ply y Revolucion (desde fichero)
    tetraedro = new Tetraedro();
    cubo = new Cubo();
    octaedro = new Octaedro();
    if(tipoPLY == sc) ply = new Ply(argv[1]);
    else if(tipoPLY == sr) revolucion = new Revolucion(argv[1]);
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
    case 0:
      octaedro->dibujar(modo);
      break;
    //Dibujado del tetraedro
    case 1:
      tetraedro->dibujar(modo);
      break;
    //Dibujado del cubo
    case 2:
      cubo->dibujar(modo);
      break;
    //Dibujado de carga de un archivo ply
    case 3:
      ply->dibujar(modo);
      break;
    //Dibujado por revolucion de un perfil ply
    case 4:
      //Si se selecciona aumentar las revoluciones del perfil, se aumenta en 1 las revoluciones actuales
      if(modoVariarRevolucion == 1) revolucion->aumentarRevoluciones();
      //Si se selecciona decrecer las revoluciones, se reduce en 1 las revoluciones actuales
      else if(modoVariarRevolucion == 2) revolucion->reducirRevoluciones();
      //Si se ha cambiado el numero de revoluciones, rehacemos la figura con las revoluciones nuevas
      if(modoVariarRevolucion != -1) revolucion->nuevosVertInd(modo);
      //Si se ha cambiado la visualizacion a con tapa, rehacemos la figura con las revoluciones actuales
      if(modoC == 1) revolucion->nuevosVertInd(modoC);
      //Sino, se pinta sin tapa
      else if(modoC == 2) revolucion->nuevosVertInd(modoC);
      //Dibujado de revolucion desde un archivo ply
      revolucion->dibujar(modo);
      break;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //Redimensionado del frustum para variar el zoom del objeto por pantalla
  if(modoRedimensionado == 1) nuevo_tam += 1;
  else if(modoRedimensionado == 2) nuevo_tam -= 1;
  glFrustum(-Width/nuevo_tam,Width/nuevo_tam,-Height/nuevo_tam,Height/nuevo_tam,Front_plane,Back_plane);

  //Se resetea los valores para que se mantenga en el mismo estado mientras no se vuelvan a pulsar
  modoRedimensionado = -1;
  modoVariarRevolucion = -1;
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
  Tecla1 = toupper(Tecla1);
  switch(Tecla1){
    //Puntos
    case 'P':
      modo = 0;
      break;
    //Lineas/Aristas
    case 'L':
      modo = 1;
      break;
    //Relleno
    case 'F':
      modo = 2;
      break;
    //Ajedrez
    case 'C':
      modo = 3;
      break;
    //Modo Prueba 1 -> Combinacion de Puntos, Aristas y Relleno
    case 'H':
      modo = 4;
      break;
    //Tapas OFF
    case 'Y':
      modoC = 1;
      break;
    //Tapas ON
    case 'U':
      modoC = 2;
      break;
    //Aumneto de revoluciones
    case '+':
      if(modoF == 4 && tipoPLY == "r") modoVariarRevolucion = 1;
      break;
    //Disminucion de revoluciones
    case '-':
      if(modoF == 4 && tipoPLY == "r") modoVariarRevolucion = 2;
      break;
    //Aumento del zoom
    case '*':
      modoRedimensionado = 1;
      break;
    //Disminucion del zoom
    case '/':
      modoRedimensionado = 2;
      break;
    //Figura seleccionada: Octaedro
    case '0':
      modoF = 0;
      break;
    //Figura seleccionada: Tetraedro
    case '1':
      modoF = 1;
      break;
    //Figura seleccionada: Cubo
    case '2':
      modoF = 2;
      break;
    //Figura seleccionada: Archivo PLY
    case '3':
      modoF = 3;
      break;
    //Figura seleccionada: Archivo revolucion
    case '4':
      modoF = 4;
      break;
  }
  //Si se presiona Q se sale del programa
  if (toupper(Tecla1)=='Q') return 1;
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
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
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
