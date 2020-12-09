/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#ifndef _PLY_H
#define _PLY_H

#include "figura.h"

class Ply : public Figura {
  public:
    Ply();
    Ply(const char *fichero);
};
#endif
