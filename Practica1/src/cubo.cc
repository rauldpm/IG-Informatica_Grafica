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
#include "cubo.h"
#include "figura.h"

using namespace std;

// Constructor con parametros
Cubo::Cubo(){

  // Coordenadas para el cubo
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(100.0f);Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(100.0f);Figura::vertices.push_back(50.0f);
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(-50.0f);
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(100.0f);Figura::vertices.push_back(-50.0f);
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(100.0f);Figura::vertices.push_back(-50.0f);
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(-50.0f);
  // Indices para el cubo
  Figura::indices.push_back(3);  Figura::indices.push_back(5);  Figura::indices.push_back(2);
  Figura::indices.push_back(2);  Figura::indices.push_back(5);  Figura::indices.push_back(6);
  Figura::indices.push_back(5);  Figura::indices.push_back(4);  Figura::indices.push_back(6);
  Figura::indices.push_back(6);  Figura::indices.push_back(4);  Figura::indices.push_back(7);
  Figura::indices.push_back(4);  Figura::indices.push_back(0);  Figura::indices.push_back(7);
  Figura::indices.push_back(7);  Figura::indices.push_back(0);  Figura::indices.push_back(1);
  Figura::indices.push_back(0);  Figura::indices.push_back(3);  Figura::indices.push_back(2);
  Figura::indices.push_back(0);  Figura::indices.push_back(2);  Figura::indices.push_back(1);
  Figura::indices.push_back(5);  Figura::indices.push_back(3);  Figura::indices.push_back(4);
  Figura::indices.push_back(4);  Figura::indices.push_back(3);  Figura::indices.push_back(0);
  Figura::indices.push_back(7);  Figura::indices.push_back(1);  Figura::indices.push_back(6);
  Figura::indices.push_back(6);  Figura::indices.push_back(1);  Figura::indices.push_back(2);
  // Indices pares para el cubo
  int contador = 0;
  bool puedeEscribir = true;
  for(int i = 0 ; i < indices.size() ; i++){
    if(puedeEscribir){
      indicesPares.push_back(indices[i]);
      contador++;
      if(contador == 3){
        contador = 0;
        puedeEscribir = false;
      }
    }
    else if(!puedeEscribir){
      indicesImpares.push_back(indices[i]);
      contador++;
      if(contador == 3){
        contador = 0;
        puedeEscribir = true;
      }
    }
  }
  // Colores
  for(int i = 0 ; i < vertices.size()/2 ; i++){
    // Color 1 para el tetraedro //Verde
    Figura::color1.push_back(0.0f); Figura::color1.push_back(1.0f); Figura::color1.push_back(0.0f);
    // Color 2 para el tetraedro //Azul
    Figura::color2.push_back(0.0f); Figura::color2.push_back(0.0f); Figura::color2.push_back(1.0f);
    // Color 3 para el tetraedro //Rojo
    Figura::color3.push_back(1.0f); Figura::color3.push_back(0.0f); Figura::color3.push_back(0.0f);
  }
  Figura::setNIndices(indices.size());
  Figura::setNVertices(vertices.size());

}
