/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "ply.h"
#include "revolucion.h"
#include "jerarquico.h"
#include "luz.h"
#include "material.h"
#include "textura.h"

class Escena {
	private:

		//************************************************************************//

		//Tamaño de los ejes
		#define AXIS_SIZE 5000
		Ejes ejes;

		//************************************************************************//

		//Creacion de objetos y reserva de memoria
		Octaedro    * octaedro   = new Octaedro();
		Tetraedro   * tetraedro  = new Tetraedro();
		Cubo        * cubo       = new Cubo();
		Ply         * ply        = new Ply();
		Revolucion  * revolucion = new Revolucion();
		Jerarquico  * jerarquico = new Jerarquico();
		Textura     * textura    = new Textura();

		Luz         * luz1       = new Luz(); //Posicional
		Luz         * luz2       = new Luz(); //Direccional
		Luz					* luz3			 = new Luz(); //Posicional

		Material    * material   = new Material();

		//************************************************************************//

		int modo;										//Activa el modo de visualizado
		int modoF;									//Activa el modo de figura
		char modoDibujadoArchivo;		//Bandera para el tipo de archivo leido
		bool modoVariarRevolucion;	//Bandera para los cambios al revolucionar
		bool modoVariarTapas;				//Bandera para las tapas revolucion
		bool modoFigura;						//Activa el menu de Figuras
		bool modoDibujado;					//Activa el menu de visualizado
		bool modoIluminacion;				//Activa la visualizacion
		bool modoSombreado;					//Activa el sombreado
		bool modoTextura;						//Activa la textura
		bool modoMovimiento;				//Activa movimiento luces

		//************************************************************************//

		//Variables que definen la posicion de la camara en coordenadas polares
		GLfloat Observer_distance;
		GLfloat Observer_angle_x;
		GLfloat Observer_angle_y;

		//Variables que controlan la ventana y la transformacion de perspectiva
		GLfloat Width, Height, Front_plane, Back_plane, ratio, zoom;

		//************************************************************************//

	private:

		//************************************************************************//

		void clear_window();
		void draw_axis();
		void draw_objects();

		//************************************************************************//

		//Transformacion de camara
		void change_projection();
		void change_observer();

		//************************************************************************//

	public:

		//************************************************************************//

		//Constructor
		Escena();

		//************************************************************************//

		//Metodo que inicializa la escena
		void inicializar(int UI_window_width,int UI_window_height);
		//Metodo que redimensiona la escena
		void redimensionar(int newWidth,int newHeight) ;
		//Metodo qu dibuja la escena
		void dibujar() ;
		//Metodo que detecta la tecla pulsada
		int teclaPulsada(unsigned char Tecla1,int x,int y) ;
		//Metodo que detecta la tecla especial pulsada
		void teclaEspecial(int Tecla1,int x,int y);

		//************************************************************************//

		//Consulta de objeto jerarquico, para la animacion
		Jerarquico getJerarquico();

		//************************************************************************//
};
#endif
