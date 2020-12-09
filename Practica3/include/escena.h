/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "ply.h"
#include "revolucion.h"
#include "grua.h"

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
Grua * grua = new Grua();

//Para cambiar modo de visualizado de figura
int modo = 0;
//Para cambiar figura "0"->octaedro "1"->tetraedro "2"->cubo "3"->ply "4"->revolucion "5"->grua
int modoF = 1;
//Para generar mas o menos revoluciones (solo modo revolucion)
bool modoVariarRevolucion = true;
bool modoVariarTapas = false;
//Para cambiar la visualizacion de la figura (zoom)
int zoom = 1;
//Tipo de dibujado, se se dibuja un objeto por revolucion o no, para controlar los controles de algunas teclas
char modoDibujadoArchivo = 'a';

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

	//Consulta de objeto grua
	Grua getGrua();

//***************************************************************************************************//

};
#endif
