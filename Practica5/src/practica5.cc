/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#include <GL/gl.h>
#include <GL/glut.h>

#include "escena.h"
#include "camara.h"


Escena *escena;
bool clickR = false;
int xant = 0, yant = 0;

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
	if(escena->getJerarquico().getModoAnimacion()){
		glutPostRedisplay();
	}
}

void clickRaton(int boton, int estado, int x, int y){
  switch(boton) {
    case GLUT_RIGHT_BUTTON:
        if(estado == GLUT_DOWN)	clickR = true;
        else clickR = false;
      	break;
  }
}

void ratonMovido(int x, int y){
  if(clickR){
  	escena->girarCamaraActiva(y-yant,x-xant);
  	xant = x;
	yant = y;
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
	  glutCreateWindow("Práctica 5: RAUL DEL POZO MORENO");

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

	  // funcion de animacion
	  glutIdleFunc(idle);

	  // funciones de raton
	  glutMouseFunc(clickRaton);
	  glutMotionFunc(ratonMovido);

	  // inicio del bucle de eventos
	  glutMainLoop();

	  return 0;
}
