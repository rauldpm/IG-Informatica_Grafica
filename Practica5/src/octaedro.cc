/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#include "octaedro.h"

Octaedro::Octaedro(){
  //Vertices para el octaedro
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f);  //1
  Figura::vertices.push_back(0.5f);  Figura::vertices.push_back(0.5f);  Figura::vertices.push_back(0.0f);  //2
  Figura::vertices.push_back(-0.5f); Figura::vertices.push_back(0.5f);  Figura::vertices.push_back(0.0f);  //3
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.5f);  Figura::vertices.push_back(0.5f);  //4
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.5f);  Figura::vertices.push_back(-0.5f); //5
  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f);  //6
  //Caras para el octaedro
  Figura::caras.push_back(0);  Figura::caras.push_back(3);  Figura::caras.push_back(2); //1
  Figura::caras.push_back(0);  Figura::caras.push_back(1);  Figura::caras.push_back(3); //2
  Figura::caras.push_back(0);  Figura::caras.push_back(4);  Figura::caras.push_back(1); //3
  Figura::caras.push_back(0);  Figura::caras.push_back(2);  Figura::caras.push_back(4); //4
  Figura::caras.push_back(1);  Figura::caras.push_back(5);  Figura::caras.push_back(3); //5
  Figura::caras.push_back(3);  Figura::caras.push_back(5);  Figura::caras.push_back(2); //6
  Figura::caras.push_back(2);  Figura::caras.push_back(5);  Figura::caras.push_back(4); //7
  Figura::caras.push_back(4);  Figura::caras.push_back(5);  Figura::caras.push_back(1); //8

  //Calculo de las normales
  calculoNormales();
  //Se rellenan las caras para el modo Ajedrez
  rellenarCarasParesImpares();
  //Colores
  rellenarColores();
}
