/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#ifndef _TEXTURA_H
#define _TEXTURA_H


#include "CImg.h"
#include <stdlib.h>
#include <ctype.h>
#include "cuadro.h"

using namespace cimg_library;

class Textura{
  private:
    //Imagen leida
    CImg<unsigned char> img;
    //Vector de almacenamiento de los datos de la imagen
    std::vector<unsigned char> data;
    //Identificador de la imagen
    GLuint textura_id;
    //Tablero donde se almacena la imagen
    Cuadro * tablero = new Cuadro();
    int alto, ancho;
    //Vector de vertices de texturas
    vector<float> texVertices;
  public:
    Textura();
    Textura(const char *fichero);
    void setTextura(int modo);
    //Metodo que rellena los vertices de la textura
    void setVertTex();
    //Rotar vertices texturas
    void setRot();
};
#endif
