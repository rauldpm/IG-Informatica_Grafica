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

#include "figura.h"

Figura::Figura(){
  this->vertices.resize(0);
  this->indices.resize(0);
  this->indicesPares.resize(0);
  this->indicesImpares.resize(0);
  this->color1.resize(0);
  this->color2.resize(0);
}

void Figura::dibujar(int modo){
  glCullFace(GL_FRONT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glPointSize(10);

  //Modo puntos, arista/alambre, solido
  if(modo < 3){
    if(modo == 0)       glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    else if (modo == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (modo == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);
  }
  //Modo ajedrez
  else if(modo == 3){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_COLOR_ARRAY);

    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indicesPares.size(),GL_UNSIGNED_INT,&indicesPares[0]);

    glColorPointer(3,GL_FLOAT,0,&color2[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indicesImpares.size(),GL_UNSIGNED_INT,&indicesImpares[0]);

    glDisableClientState(GL_COLOR_ARRAY);
  }
  //Modo PRUEBA PRACTICA 1 -> mostrar puntos, arista/alambre y solido a la vez con colores diferentes
  else if(modo == 4){
    glEnableClientState(GL_COLOR_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColorPointer(3,GL_FLOAT,0,&color2[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorPointer(3,GL_FLOAT,0,&color3[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,&indices[0]);

    glDisableClientState(GL_COLOR_ARRAY);

  }
  glDisableClientState(GL_VERTEX_ARRAY);
}
