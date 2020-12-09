/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include "material.h"

Material::Material(){};

Material::Material(float colorE0, float colorE1, float colorE2, float colorE3,
                   float colorA0, float colorA1, float colorA2, float colorA3,
                   float colorD0, float colorD1, float colorD2, float colorD3,
                   float colorS0, float colorS1, float colorS2, float colorS3,
                   float shine){
  //emision             //ambiental
  setColorE(0,colorE0); setColorA(0,colorA0);
  setColorE(1,colorE1); setColorA(1,colorA1);
  setColorE(2,colorE2); setColorA(2,colorA2);
  setColorE(3,colorE3); setColorA(3,colorA3);
  //difuso              //especular
  setColorD(0,colorD0); setColorS(0,colorS0);
  setColorD(1,colorD1); setColorS(1,colorS1);
  setColorD(2,colorD2); setColorS(2,colorS2);
  setColorD(3,colorD3); setColorS(3,colorS3);
  //Brillo
  setShine(shine);
}

void Material::setMaterial1(){
  //emision             //ambiental
  setColorE(0,0.0f);    setColorA(0,0.2125f);
  setColorE(1,0.0f);    setColorA(1,0.1275f);
  setColorE(2,0.0f);    setColorA(2,0.0540f);
  setColorE(3,1.0f);    setColorA(3,1.0f);
  //difuso              //especular
  setColorD(0,0.7140f); setColorS(0,0.3935f);
  setColorD(1,0.4284f); setColorS(1,0.2719f);
  setColorD(2,0.1812f); setColorS(2,0.1667f);
  setColorD(3,1.0f);    setColorS(3,1.0f);
  //Brillo
  setShine(25.6f);
}
void Material::setMaterial2(){
  //emision             //ambiental
  setColorE(0,0.0f);    setColorA(0,0.3294f);
  setColorE(1,0.0f);    setColorA(1,0.2235f);
  setColorE(2,0.0f);    setColorA(2,0.0274f);
  setColorE(3,1.0f);    setColorA(3,1.0f);
  //difuso              //especular
  setColorD(0,0.7803f); setColorS(0,0.9921f);
  setColorD(1,0.5686f); setColorS(1,0.9411f);
  setColorD(2,0.1137f); setColorS(2,0.8078f);
  setColorD(3,1.0f);    setColorS(3,1.0f);
  //Brillo
  setShine(25.6f);
}
void Material::setMaterial3(){
  //emision             //ambiental
  setColorE(0,0.0f);    setColorA(0,0.05f);
  setColorE(1,0.0f);    setColorA(1,0.0f);
  setColorE(2,0.0f);    setColorA(2,0.0f);
  setColorE(3,1.0f);    setColorA(3,1.0f);
  //difuso              //especular
  setColorD(0,0.5f);    setColorS(0,0.7f);
  setColorD(1,0.4f);    setColorS(1,0.4f);
  setColorD(2,0.4f);    setColorS(2,0.4f);
  setColorD(3,1.0f);    setColorS(3,1.0f);
  //Brillo
  setShine(10.0f);
}
void Material::setMaterial4(){
  //emision             //ambiental
  setColorE(0,0.0f);    setColorA(0,0.25f);
  setColorE(1,0.0f);    setColorA(1,0.25f);
  setColorE(2,0.0f);    setColorA(2,0.25f);
  setColorE(3,1.0f);    setColorA(3,1.25f);
  //difuso              //especular
  setColorD(0,0.4f);    setColorS(0,0.7745f);
  setColorD(1,0.4f);    setColorS(1,0.7745f);
  setColorD(2,0.4f);    setColorS(2,0.7745f);
  setColorD(3,1.0f);    setColorS(3,1.0f);
  //Brillo
  setShine(10.0f);
}

//Acciones del material
void Material::asignarMaterial(){

  glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, colorE ) ;
  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,  colorA ) ;
  glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,  colorD ) ;
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, colorS ) ;
  glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, shine ) ;

  glColorMaterial( GL_BACK, GL_EMISSION ) ;
  glColorMaterial( GL_BACK, GL_AMBIENT ) ;
  glColorMaterial( GL_BACK, GL_DIFFUSE ) ;
  glColorMaterial( GL_BACK, GL_SPECULAR ) ;
}

//Modificadores
void Material::setColorE(int pos, float valor){ colorE[pos] = valor; }
void Material::setColorA(int pos, float valor){ colorA[pos] = valor; }
void Material::setColorD(int pos, float valor){ colorD[pos] = valor; }
void Material::setColorS(int pos, float valor){ colorS[pos] = valor; }
void Material::setShine(float valor)          { shine = valor; }

//Consultores
float Material::getColorE(int pos){ return colorE[pos]; }
float Material::getColorA(int pos){ return colorA[pos]; }
float Material::getColorD(int pos){ return colorD[pos]; }
float Material::getColorS(int pos){ return colorS[pos]; }
float Material::getShine()        { return shine; }
