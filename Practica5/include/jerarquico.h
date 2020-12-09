/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#ifndef _GRUA_H
#define _GRUA_H

#include "cubo.h"
#include "ply.h"

class Jerarquico{
  private:
    Cubo * cubo = new Cubo();
    Ply * cilindro = new Ply("data/modelos_jerarquicos/cilindro.ply");
    Ply * vaca = new Ply("data/modelos_jerarquicos/vaca.ply");
    Ply * esfera = new Ply("data/modelos_jerarquicos/esfera.ply");

    float gradosLibertad[4];
    float velocidad[4];
    bool esta_animado = false;

    float luz1[4];
    float luz2[4];
    float luz3[4];

  public:
    Jerarquico();

    //Metodos de dibujado
    void dibujarJ(int modo);
    void dibujaCubo(float modo, float escalaX, float escalaY, float escalaZ, float color1, float color2, float color3);
    void dibujaCilindro(int modo, float escalaX, float escalaY, float escalaZ);
    void dibujaVaca(int modo);

    //Metodos de grados de libertad
    void setGradoLibertad(int pos, float valor);
    float getGradoLibertad(int pos);

    void setGradoLibertadLuz1(int pos, float valor);
    void setGradoLibertadLuz2(int pos, float valor);
    void setGradoLibertadLuz3(int pos, float valor);
    float getGradoLibertadLuz1(int pos);
    float getGradoLibertadLuz2(int pos);
    float getGradoLibertadLuz3(int pos);

    //Metodos de velocidad
    void setVelocidad(int pos, float valor);
    float getVelocidad(int pos);

    //Metodos de animacion
    void animacion();
    void setModoAnimacion(bool estado);
  	bool getModoAnimacion();
};
#endif
