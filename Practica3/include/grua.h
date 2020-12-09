/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#ifndef _GRUA_H
#define _GRUA_H

#include "cubo.h"
#include "ply.h"

class Grua{
  private:
    Cubo * cubo = new Cubo();
    Ply * cilindro = new Ply("data/cilindro.ply");
    Ply * vaca = new Ply("data/vaca.ply");
    float gradosLibertad[4];
    float velocidad[4];
    bool esta_animado = false;
  public:
    Grua();

    //Metodos de dibujado
    void dibujarJ(int modo);
    void dibujaCubo(float modo, float escalaX, float escalaY, float escalaZ, float color1, float color2, float color3);
    void dibujaCilindro(int modo, float escalaX, float escalaY, float escalaZ);
    void dibujaVaca(int modo);

    //Metodos de grados de libertad
    void setGradoLibertad(int pos, float valor);
    float getGradoLibertad(int pos);

    //Metodos de velocidad
    void setVelocidad(int pos, float valor);
    float getVelocidad(int pos);

    //Metodos de animacion
    void animacion();
    void setModoAnimacion(bool estado);
  	bool getModoAnimacion();
};
#endif
