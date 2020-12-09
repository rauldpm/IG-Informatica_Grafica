/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#ifndef _LUZ_H
#define _LUZ_H

class Luz {
  private:
    float lmodel_ambient[4];
    float caf[4];  // color ambiental de la fuente
    float cdf[4];  // color difuso de la fuente
    float csf[4];  // color especular de la fuente
    float posf[4]; // (x,y,z,w)

    bool iluminacion; //estado de la iluminacion

  public:
    Luz();
    Luz(float a0, float a1, float a2, float a3,
        float caf0, float caf1, float caf2, float caf3,
        float cdf0, float cdf1, float cdf2, float cdf3,
        float csf0, float csf1, float csf2, float csf3,
        float posf0, float posf1, float posf2, float posf3);

    //Acciones de la luz
    void iluminar(int luz);
    void cambiar(char eje);

    //Modificadores
    void setModelAmb(int pos, float valor);
    void setAmbiente(int pos, float valor);
    void setDifuso(int pos, float valor);
    void setEspecular(int pos, float valor);
    void setPosicion(int pos, float valor);
    void setIluminacion(bool ilu);
    //Consultores
    bool getIluminacion();
    float getModelAmbient(int pos);
    float getAmbiente(int pos);
    float getDifuso(int pos);
    float getEspecular(int pos);
    float getPosicion(int pos);

};
#endif
