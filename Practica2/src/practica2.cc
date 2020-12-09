/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "escena.h"

Escena *escena;

void draw_scene(void)  {
	if (escena!=NULL)	escena->dibujar();
	glutSwapBuffers();
}

void change_window_size(int newWidth,int newHeight)  {
	if (escena!=NULL)	escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}

void normal_keys(unsigned char Tecla1,int x,int y)  {

	int salir=0;
	if (escena!=NULL)	salir=escena->teclaPulsada(Tecla1,x,y);
	if (salir) {
		delete escena;
		exit(0);
	} else
		glutPostRedisplay();
}

void special_keys(int Tecla1,int x,int y) {
	if (escena!=NULL)
		escena->teclaEspecial(Tecla1,x,y);
	glutPostRedisplay();
}

int main(int argc, char **argv){

		//Si solo se pasa el ejecutable
		if(argc == 1){
			std::cout << "Creando escena -> Modo Octaedro(Tecla: 0)" << std::endl;
			std::cout << "Creando escena -> Modo Tetraedro(Tecla: 1)" << std::endl;
			std::cout << "Creando escena -> Modo Cubo(Tecla: 2)" << std::endl;
			std::cout << "Creando escena -> Modo Revolucion(Tecla: 4)" << std::endl;
			escena = new Escena();
		}
		//Si se pasa el ejecutable y 1 parametro
		else if(argc == 2){
			std::cout << "ERROR EN LOS PARAMETROS" << std::endl;
			return 0;
		}
		//Si se pasa el ejecutable y 2 parametros (ejecutable + fichero + modo)
		else if (argc == 3){
			string tipo(argv[2]);
			string r = "r", c = "c";
			if(tipo == r || tipo == c){
				std::cout << "Creando escena -> Modo Octaedro(Tecla: 0)" << std::endl;
				std::cout << "Creando escena -> Modo Tetraedro(Tecla: 1)" << std::endl;
				std::cout << "Creando escena -> Modo Cubo(Tecla: 2)" << std::endl;
				std::cout << "Creando escena -> Modo Ply(Tecla: 3)" << std::endl;
				std::cout << "Creando escena -> Modo Revolucion(Tecla: 4)" << std::endl;
				escena = new Escena(argv);
			}
			else{
				std::cout << "ERROR EN LOS PARAMETROS" << std::endl;
				return 0;
			}
		}
		else{
			std::cout << "ERROR EN LOS PARAMETROS" << std::endl;
			return 0;
		}

	  // se llama a la inicialización de glut
	  glutInit(&argc, argv);

	  // se indica las caracteristicas que se desean para la visualización con OpenGL
	  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	  // variables que determninan la posicion y tamaño de la ventana X
	  int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

	  // posicion de la esquina inferior izquierdad de la ventana
	  glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);
	  // tamaño de la ventana (ancho y alto)
	  glutInitWindowSize(UI_window_width,UI_window_height);

	  // llamada para crear la ventana, indicando el titulo
	  glutCreateWindow("Práctica 2: RAUL DEL POZO MORENO");

	  // asignación de la funcion llamada "dibujar" al evento de dibujo
	  glutDisplayFunc(draw_scene);
	  // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	  glutReshapeFunc(change_window_size);
	  // asignación de la funcion llamada "tecla_normal" al evento correspondiente
	  glutKeyboardFunc(normal_keys);
	  // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	  glutSpecialFunc(special_keys);

	  // funcion de inicialización
	  escena->inicializar(UI_window_width,UI_window_height);
	  // inicio del bucle de eventos
	  glutMainLoop();

	  return 0;

}
