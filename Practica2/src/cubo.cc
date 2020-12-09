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

#include "cubo.h"

Cubo::Cubo(){
  //Vertices para el cubo
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(50.0f);  //1
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(50.0f);  //2
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(100.0f);Figura::vertices.push_back(50.0f);  //3
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(100.0f);Figura::vertices.push_back(50.0f);  //4
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(-50.0f); //5
  Figura::vertices.push_back(-50.0f);Figura::vertices.push_back(100.0f);Figura::vertices.push_back(-50.0f); //6
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(100.0f);Figura::vertices.push_back(-50.0f); //7
  Figura::vertices.push_back(50.0f); Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(-50.0f); //8
  //Caras para el cubo
  Figura::caras.push_back(3);  Figura::caras.push_back(5);  Figura::caras.push_back(2);
  Figura::caras.push_back(2);  Figura::caras.push_back(5);  Figura::caras.push_back(6);
  Figura::caras.push_back(5);  Figura::caras.push_back(4);  Figura::caras.push_back(6);
  Figura::caras.push_back(6);  Figura::caras.push_back(4);  Figura::caras.push_back(7);
  Figura::caras.push_back(4);  Figura::caras.push_back(0);  Figura::caras.push_back(7);
  Figura::caras.push_back(7);  Figura::caras.push_back(0);  Figura::caras.push_back(1);
  Figura::caras.push_back(0);  Figura::caras.push_back(3);  Figura::caras.push_back(2);
  Figura::caras.push_back(0);  Figura::caras.push_back(2);  Figura::caras.push_back(1);
  Figura::caras.push_back(5);  Figura::caras.push_back(3);  Figura::caras.push_back(4);
  Figura::caras.push_back(4);  Figura::caras.push_back(3);  Figura::caras.push_back(0);
  Figura::caras.push_back(7);  Figura::caras.push_back(1);  Figura::caras.push_back(6);
  Figura::caras.push_back(6);  Figura::caras.push_back(1);  Figura::caras.push_back(2);
  //Caras para el modo ajedrez
  rellenarCarasParesImpares();
  //Colores
  rellenarColores();
}
