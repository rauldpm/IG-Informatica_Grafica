/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#ifndef _PLY_H
#define _PLY_H

#include "figura.h"

class Ply : public Figura {
  public:
    //Constructor por defecto
    Ply();
    //Constructor con parametros
    Ply(char *fichero);
};
#endif
