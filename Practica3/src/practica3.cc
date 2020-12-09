/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

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

void idle(){
	if(escena->getGrua().getModoAnimacion()){
		glutPostRedisplay();
	}
}

int main(int argc, char **argv){

		escena = new Escena();

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
	  glutCreateWindow("Práctica 3: RAUL DEL POZO MORENO");

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

		glutIdleFunc(idle);

	  // inicio del bucle de eventos
	  glutMainLoop();

	  return 0;
}