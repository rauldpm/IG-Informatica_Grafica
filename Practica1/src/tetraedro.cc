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

#include <vector>
#include "tetraedro.h"
#include "figura.h"

using namespace std;

//Constructor con parametros
Tetraedro::Tetraedro(){
  //Coordenadas para el tetraedro
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(0.0f); Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(0.0f); Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); Figura::vertices.push_back(-50.0f);
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(50.0f);Figura::vertices.push_back(0.0f);
  //Indices para el tetraedro
  Figura::indices.push_back(0);  Figura::indices.push_back(3);  Figura::indices.push_back(1);
  Figura::indices.push_back(1);  Figura::indices.push_back(3);  Figura::indices.push_back(2);
  Figura::indices.push_back(2);  Figura::indices.push_back(3);  Figura::indices.push_back(0);
  Figura::indices.push_back(2);  Figura::indices.push_back(0);  Figura::indices.push_back(1);
  //Indices pares tetraedro
  for(int i = 0, j = indices.size()/2 ; i < indices.size()/2 ; i++,j++){
    indicesPares.push_back(indices[i]);
    indicesImpares.push_back(indices[j]);
  }
  //Colores
  for(int i = 0 ; i < vertices.size()/2 ; i++){
    //Color 1 para el tetraedro //Verde
    Figura::color1.push_back(0.0f); Figura::color1.push_back(1.0f); Figura::color1.push_back(0.0f);
    //Color 2 para el tetraedro //Azul
    Figura::color2.push_back(0.0f); Figura::color2.push_back(0.0f); Figura::color2.push_back(1.0f);
    //Color 3 para el tetraedro //Rojo
    Figura::color3.push_back(1.0f); Figura::color3.push_back(0.0f); Figura::color3.push_back(0.0f);
  }

  Figura::setNIndices(indices.size());
  Figura::setNVertices(vertices.size());
}
