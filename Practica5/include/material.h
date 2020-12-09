/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#ifndef _MATERIAL_H
#define _MATERIAL_H

class Material {
  private:
    float colorE[4];
    float colorA[4];
    float colorD[4];
    float colorS[4];
    float shine;

  public:
    Material();
    //Material Personalizado
    Material(float colorE0, float colorE1, float colorE2, float colorE3,
             float colorA0, float colorA1, float colorA2, float colorA3,
             float colorD0, float colorD1, float colorD2, float colorD3,
             float colorS0, float colorS1, float colorS2, float colorS3,
             float shine);

    //Asignar valores material
    void setMaterial1(); //Bronze
    void setMaterial2(); //Laton
    void setMaterial3(); //Caucho rojo
    void setMaterial4(); //Chroma

    //Acciones del material
    void asignarMaterial();

    //Modificadores
    void setColorE(int pos, float valor);
    void setColorA(int pos, float valor);
    void setColorD(int pos, float valor);
    void setColorS(int pos, float valor);
    void setShine(float valor);

    //Consultores
    float getColorE(int pos);
    float getColorA(int pos);
    float getColorD(int pos);
    float getColorS(int pos);
    float getShine();
};
#endif
