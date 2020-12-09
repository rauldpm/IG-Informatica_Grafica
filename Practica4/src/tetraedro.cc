/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#include "tetraedro.h"

//Constructor por defecto
Tetraedro::Tetraedro(){
  //Vertices para el tetraedro
  Figura::vertices.push_back(-1.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);  //1
  Figura::vertices.push_back(1.0f);   Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);  //2
  Figura::vertices.push_back(0.0f);   Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(-1.0f); //3
  Figura::vertices.push_back(0.0f);   Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f);  //4
  //Caras para el tetraedro
  Figura::caras.push_back(0);  Figura::caras.push_back(1);  Figura::caras.push_back(3); //1
  Figura::caras.push_back(1);  Figura::caras.push_back(2);  Figura::caras.push_back(3); //2
  Figura::caras.push_back(2);  Figura::caras.push_back(0);  Figura::caras.push_back(3); //3
  Figura::caras.push_back(2);  Figura::caras.push_back(1);  Figura::caras.push_back(0); //4

  calculoNormales();
  rellenarCarasParesImpares();
  rellenarColores();
}
