/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#ifndef _CUADRO_H
#define _CUADRO_H

#include "figura.h"

class Cuadro : public Figura {
  public:
    Cuadro();
    Cuadro(int alto, int ancho);
};
#endif
