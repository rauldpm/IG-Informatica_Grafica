/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#include "tetraedro.h"

//Constructor por defecto
Tetraedro::Tetraedro(){
  //Vertices para el tetraedro
  Figura::vertices.push_back(-1.0f);Figura::vertices.push_back(0.0f); Figura::vertices.push_back(1.0f);
  Figura::vertices.push_back(1.0f); Figura::vertices.push_back(0.0f); Figura::vertices.push_back(1.0f);
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); Figura::vertices.push_back(-1.0f);
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);Figura::vertices.push_back(0.0f);
  //Caras para el tetraedro
  Figura::caras.push_back(0);  Figura::caras.push_back(1);  Figura::caras.push_back(3);
  Figura::caras.push_back(1);  Figura::caras.push_back(2);  Figura::caras.push_back(3);
  Figura::caras.push_back(2);  Figura::caras.push_back(0);  Figura::caras.push_back(3);
  Figura::caras.push_back(2);  Figura::caras.push_back(1);  Figura::caras.push_back(0);
  //Caras para el modo ajedrez
  rellenarCarasParesImpares();
  //Colores
  rellenarColores();
}
