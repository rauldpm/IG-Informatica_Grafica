/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"

using namespace std;
class Escena {
private:
// tamaño de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

//Creacion de objetos y reserva de memoria
Tetraedro * tetraedro = new Tetraedro();
Cubo * cubo = new Cubo();
//Para cambiar modo de visualizado de figura
int modo = 0;
//Para cambiar figura 1->tetraedro 2->cubo
int modoF = 1;



// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:

	void clear_window();
	void draw_axis();
	void draw_objects();

    // Transformacion de camara
	void change_projection();
	void change_observer();


public:
  Escena();
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;

	// Interaccion con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);


  void setModo(int i);
	void setModoF(int i);



};
#endif
