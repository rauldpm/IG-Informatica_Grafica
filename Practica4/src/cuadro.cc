/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#include "cuadro.h"

Cuadro::Cuadro(){};

Cuadro::Cuadro(int alto, int ancho){

  if(ancho < alto){
    float p = float(ancho)/float(alto);
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //0,0,0
    Figura::vertices.push_back(p);     Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //1,0,0
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f); //0,1,0
    Figura::vertices.push_back(p);     Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f); //1,1,0
  }
  else if(ancho > alto){

    float p = float(alto)/float(ancho);
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //0,0,0
    Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //1,0,0
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(p);     Figura::vertices.push_back(0.0f); //0,1,0
    Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(p);     Figura::vertices.push_back(0.0f); //1,1,0
  }
  else{
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //0,0,0
    Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(0.0f); //1,0,0
    Figura::vertices.push_back(0.0f);  Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f); //0,1,0
    Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(1.0f);  Figura::vertices.push_back(0.0f); //1,1,0
  }

  Figura::caras.push_back(0); Figura::caras.push_back(1); Figura::caras.push_back(2); //1
  Figura::caras.push_back(1); Figura::caras.push_back(3); Figura::caras.push_back(2); //2

  //Calculo de las normales
  calculoNormales();
  //Caras para el modo ajedrez
  rellenarCarasParesImpares();
  //Colores
  rellenarColores();
}
