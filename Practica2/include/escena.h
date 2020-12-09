/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "ply.h"
#include "revolucion.h"

class Escena {
private:
// tama�o de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

//***************************************************************************************************//

//Creacion de objetos y reserva de memoria
Tetraedro * tetraedro = new Tetraedro();
Cubo * cubo = new Cubo();
Octaedro * octaedro = new Octaedro();
Ply * ply = new Ply();
Revolucion * revolucion = new Revolucion();

//Para cambiar modo de visualizado de figura
int modo = 0;
//Para cambiar figura "1"->tetraedro "2"->cubo "3"->ply "4"->revolucion
int modoF = 1;
//Para mostrar tapas o no
int modoC = 1;
//Para cambiar el modoRedimensionado "/"->mas pequeño "*"->mas grande
int modoRedimensionado = -1;
//Para generar mas o menos revoluciones (solo modo revolucion) "-" -> menos revoluciones "+" -> mas revoluciones
int modoVariarRevolucion = -1;
//Para cambiar la visualizacion de la figura (zoom)
int nuevo_tam = 1;
//Tipo de dibujado del ply, para que solo cambie las revoluciones si se va a dibujar un revolucionado
string tipoPLY = "a";


//***************************************************************************************************//

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

//Transformaci�n de c�mara
	void change_projection();
	void change_observer();



public:

	//Constructor sin parametros (por defecto)
	Escena();
	//Constructor con parametros, crea lo mismo que el sin parametros pero permitiendo
	//elegir adicionalmente el modo entre revolucion y carga ply
	Escena(char **argv);

	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;

	// Interacci�n con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);

//***************************************************************************************************//

};
#endif
