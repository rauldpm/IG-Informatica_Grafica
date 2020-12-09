/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "escena.h"
#include "tetraedro.h"
#include "cubo.h"

using namespace std;
Escena::Escena(){
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);

    // Inicializacion de las figuras Tetraedro y Cubo
    tetraedro = new Tetraedro();
    cubo = new Cubo();
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1); // Se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// Se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {
  //Si esta seleccionado el modo tetraedro, llama al dibujado de un tetraedro
  if(this->modoF == 1) tetraedro->dibujar(this->modo);
  //Si esta seleccionado el modo cubo, llama al dibujado de un cubo
  else if(this->modoF == 2) cubo->dibujar(this->modo);
}

void Escena::setModo(int i){
  modo = i;
}

void Escena::setModoF(int i){
  modoF = i;
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
    // Puntos
    case 'P':
      this->setModo(0);
      break;
    // Lineas/Aristas
    case 'L':
      this->setModo(1);
      break;
    // Relleno
    case 'F':
      this->setModo(2);
      break;
    // Ajedrez
    case 'C':
      this->setModo(3);
      break;
    case 'H':
      this->setModo(4);
      break;
    // Tetraedro
    case '1':
      this->setModoF(1);
      break;
    // Cubo
    case '2':
      this->setModoF(2);
      break;
  }

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
// Funcion para definir la transformacion de proyeccion
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
// Funcion para definir la transformacion de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {

// Posicion del observador
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
