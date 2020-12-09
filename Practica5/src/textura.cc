/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "textura.h"

Textura::Textura(){};

Textura::Textura(const char *fichero){

  img.load(fichero);
  for (long y = img.height()-1 ; y >= 0 ; y --)
    for (long x = 0; x < img.width(); x ++){
  	 unsigned char *r = img.data(x, y, 0, 0);
  	 unsigned char *g = img.data(x, y, 0, 1);
  	 unsigned char *b = img.data(x, y, 0, 2);
  	 data.push_back(*r);
  	 data.push_back(*g);
  	 data.push_back(*b);
  }

  alto = img.height()-1;
  ancho = img.width()-1;
  tablero = new Cuadro(alto,ancho);
}

void Textura::setTextura(int modo){

  glGenTextures(1, &textura_id);
  glBindTexture(GL_TEXTURE_2D, textura_id);

  gluBuild2DMipmaps(GL_TEXTURE_2D,  GL_RGB,ancho,alto,  GL_RGB,GL_UNSIGNED_BYTE,&data[0]);

  glActiveTexture(GL_TEXTURE0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);

  tablero->dibujar(modo);
}

void Textura::setVertTex(){
  texVertices.push_back(0); texVertices.push_back(0);
  texVertices.push_back(1); texVertices.push_back(0);
  texVertices.push_back(0); texVertices.push_back(1);
  texVertices.push_back(1); texVertices.push_back(1);
}

void Textura::setRot(){
  float copia = texVertices[0];
  for(unsigned int i = 0 ; i < texVertices.size()-1 ; i++) texVertices[i] = texVertices[i+1];
  texVertices[texVertices.size()-1] = copia;
}
