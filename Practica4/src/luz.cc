/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#define _USE_MATH_DEFINES

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "math.h"
#include "luz.h"

Luz::Luz(){
  //lmodel_ambient     //ambiental          //difuso
  setModelAmb(0,0.2f); setAmbiente(0,0.5f); setDifuso(0,0.8f);
  setModelAmb(1,0.2f); setAmbiente(1,0.5f); setDifuso(1,0.8f);
  setModelAmb(2,0.2f); setAmbiente(2,0.5f); setDifuso(2,0.8f);
  setModelAmb(3,1.0f); setAmbiente(3,1.0f); setDifuso(3,1.0f);
  //especular           //posicion
  setEspecular(0,1.0f); setPosicion(0,0.0f);
  setEspecular(1,1.0f); setPosicion(1,15.0f);
  setEspecular(2,1.0f); setPosicion(2,0.0f);
  setEspecular(3,1.0f); setPosicion(3,1.0f);
  //iluminacion
  setIluminacion(false);
}

Luz::Luz(float a0, float a1, float a2, float a3,
         float caf0, float caf1, float caf2, float caf3,
         float cdf0, float cdf1, float cdf2, float cdf3,
         float csf0, float csf1, float csf2, float csf3,
         float posf0, float posf1, float posf2, float posf3){

  //lmodel_ambient   //ambiental          //difuso           //especular
  setModelAmb(0,a0); setAmbiente(0,caf0); setDifuso(0,cdf0); setEspecular(0,csf0);
  setModelAmb(1,a1); setAmbiente(1,caf1); setDifuso(1,cdf1); setEspecular(1,csf1);
  setModelAmb(2,a2); setAmbiente(2,caf2); setDifuso(2,cdf2); setEspecular(2,csf2);
  setModelAmb(3,a3); setAmbiente(3,caf3); setDifuso(3,cdf3); setEspecular(3,csf3);
  //posicion
  setPosicion(0,posf0);
  setPosicion(1,posf1);
  setPosicion(2,posf2);
  setPosicion(3,posf3);
  //iluminacion
  setIluminacion(false);
}

void Luz::iluminar(int luz){
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  glLightfv( luz, GL_AMBIENT,  caf);
  glLightfv( luz, GL_DIFFUSE,  cdf);
  glLightfv( luz, GL_SPECULAR, csf);

  glLightfv(luz, GL_POSITION, posf);

  glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}

void Luz::cambiar(char eje){
  double angulo = M_PI/180;
  if(eje == 'z'){
    posf[0] = cos(angulo)*posf[0] - sin(angulo)*posf[1];
    posf[1] = sin(angulo)*posf[0] + cos(angulo)*posf[1];
    posf[2] = posf[2];
  }
  else if(eje == 'x'){
    posf[0] = (posf[0]);
    posf[1] = (cos((1)*angulo)*posf[1] - sin((1)*angulo)*posf[2]);
    posf[2] = (sin((1)*angulo)*posf[1] + cos((1)*angulo)*posf[2]);
  }
  else if(eje == 'y'){
    posf[0] = (cos(angulo)*posf[0] + sin(angulo)*posf[2]);
    posf[1] = (posf[1]);
    posf[2] = (-sin((1)*angulo)*posf[0] + cos((1)*angulo)*posf[2]);
  }
}

//Modificadores
void Luz::setModelAmb(int pos, float valor) { lmodel_ambient[pos] = valor; }
void Luz::setAmbiente(int pos, float valor) { caf[pos] = valor; }
void Luz::setDifuso(int pos, float valor)   { cdf[pos] = valor; }
void Luz::setEspecular(int pos, float valor){ csf[pos] = valor; }
void Luz::setPosicion(int pos, float valor) { posf[pos] = valor;}
void Luz::setIluminacion(bool ilu)          { iluminacion = ilu; }

//Consultores
float Luz::getModelAmbient(int pos){ return lmodel_ambient[pos]; }
float Luz::getAmbiente(int pos)    { return caf[pos]; }
float Luz::getDifuso(int pos)      { return cdf[pos]; }
float Luz::getEspecular(int pos)   { return csf[pos]; }
float Luz::getPosicion(int pos)    { return posf[pos]; }
bool  Luz::getIluminacion()        { return iluminacion; }
