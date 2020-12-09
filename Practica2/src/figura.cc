/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "figura.h"

Figura::Figura(){};

void Figura::dibujar(int modo){
  //Se activan las caras frontales, el array de vertices, el de colores y se marca el tamaño de los puntos a 5
  glCullFace(GL_FRONT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glPointSize(5);

  //Modo puntos, arista/alambre, solido
  if(modo < 3){
    if(modo == 0)
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    else if (modo == 1)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (modo == 2)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorPointer(3,GL_FLOAT,0,&color4[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);
  }
  //Modo ajedrez
  else if(modo == 3){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColorPointer(3,GL_FLOAT,0,&color3[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,carasPares.size(),GL_UNSIGNED_INT,&carasPares[0]);

    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,carasImpares.size(),GL_UNSIGNED_INT,&carasImpares[0]);
  }
  //Modo PRUEBA PRACTICA 1 -> mostrar puntos, arista/alambre y solido a la vez con colores diferentes
  else if(modo == 4){
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColorPointer(3,GL_FLOAT,0,&color2[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorPointer(3,GL_FLOAT,0,&color3[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);

  }
  //Se desactiva el array de vertices y el de colores
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Figura::escribirCarasTerminal(){
  for(int i = 0 ; i < caras.size() ; i+=3)
    std::cout << caras[i] << " " << caras[i+1] << " " << caras[i+2] << std::endl;
  std::cout << std::endl;
}

void Figura::escribirVerticesTerminal(){
  for(int i = 0 ; i < vertices.size() ; i+=3)
    std::cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << std::endl;
  std::cout << std::endl;
}


void Figura::rellenarColores(){
  for(int i = 0 ; i < vertices.size()/2 ; i++){
    //Color 1 para el tetraedro //Verde
    color1.push_back(0.0f); color1.push_back(1.0f); color1.push_back(0.0f);
    //Color 2 para el tetraedro //Azul
    color2.push_back(0.0f); color2.push_back(0.0f); color2.push_back(1.0f);
    //Color 3 para el tetraedro //Rojo
    color3.push_back(1.0f); color3.push_back(0.0f); color3.push_back(0.0f);
    //Color4 para el ply //Magenta
    color4.push_back(1.0f); color4.push_back(0.0f); color4.push_back(1.0f);
  }
}

void Figura::rellenarCarasParesImpares(){
  for(int i = 0 ; i < caras.size() ; i+=6){
    //Caras pares
    carasPares.push_back(caras[i]);
    carasPares.push_back(caras[i+1]);
    carasPares.push_back(caras[i+2]);
    //Caras impares
    carasImpares.push_back(caras[i+3]);
    carasImpares.push_back(caras[i+4]);
    carasImpares.push_back(caras[i+5]);
  }
}
