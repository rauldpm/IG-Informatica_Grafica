/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 4 -- Iluminacion y Texturas
*/

#include <GL/gl.h>
#include <GL/glut.h>

#include "jerarquico.h"

Jerarquico::Jerarquico(){
  for(int i = 0 ; i < 4 ; i++) velocidad[i] = 0.05;
  for(int i = 0 ; i < 4 ; i++) gradosLibertad[i] = 0;
}

void Jerarquico::dibujaCubo(float modo, float escalaX, float escalaY, float escalaZ, float color1, float color2, float color3){
  glPushMatrix();
    glScalef(escalaX,escalaY,escalaZ);
    cubo->rellenarColores(color1,color2,color3);
    cubo->dibujar(modo);
  glPopMatrix();
}

void Jerarquico::dibujaCilindro(int modo, float escalaX, float escalaY, float escalaZ){
  glPushMatrix();
    glScalef(escalaX,escalaY,escalaZ);
    cilindro->dibujar(modo);
  glPopMatrix();
}

void Jerarquico::dibujaVaca(int modo){
  glPushMatrix();
    vaca->dibujar(modo);
  glPopMatrix();
}

void Jerarquico::dibujarJ(int modo){

  /*glPushMatrix();
    glTranslatef(10,0,0);
    dibujaCilindro(modo,5,5,5);
  glPopMatrix();*/

  glPushMatrix();
    glTranslatef(luz3[0],luz3[1]+9,luz3[2]);
    glScalef(0.005,0.005,0.005);
    esfera->dibujar(modo);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(luz1[0],luz1[1]+15,luz1[2]);
    glScalef(0.005,0.005,0.005);
    esfera->dibujar(modo);
  glPopMatrix();

  /*glPushMatrix();
    glTranslatef(luz2[0]+6,luz2[1],luz2[2]);
    cubo->dibujar(modo);
  glPopMatrix();*/

  /*glPushMatrix();
    glTranslatef(-8,0,0);
    dibujaCubo(modo,5,1,5,1,0,0);                      //Se dibuja la Base

    glTranslatef(0,1,0);                               //Se translada a encima de la Base el Cuerpo
    dibujaCubo(modo,1,5,1,0,1,0);                      //Se dibuja el Cuerpo

    glRotatef(gradosLibertad[0],0,1,0);                //Se rotan los Brazos segun un angulo

    glTranslatef(0,5,0);                               //Se translada el CilindroRotacion
    dibujaCilindro(modo,2,0.5,2);                      //Se dibuja el CilindroRotacion

    glTranslatef(1,0.5,0);                             //Se translada el Brazo primario
    dibujaCubo(modo,6,1,1,0,0,1);                      //Se dibuja el Brazo

    glTranslatef(gradosLibertad[1],0,0);               //Se mueve el brazo extensible
    glTranslatef(2,1,0);                               //Se translada el Brazo extensible
    dibujaCubo(modo,4,0.5,1,0,1,1);                    //Se dibuja el Brazo extensible

    //PRUEBA 3
    glTranslatef(gradosLibertad[3],0,0);               //Se mueve el soporte
    glTranslatef(1.5,-0.5,0);                          //Se translada el soporte
    dibujaCubo(modo,1,0.5,1,0,0,0);                    //Se dibuja el soporte de la cuerda
    //FIN PRUEBA 3

    glTranslatef(0,gradosLibertad[2],0);               //Se mueve la cuerda
    glTranslatef(0,-2,0);                              //Se translada la Cuerda
    dibujaCilindro(modo,0.1,-gradosLibertad[2]+2,0.1); //Se dibuja la Cuerda del brazo extensible

    glTranslatef(0,-2,0);                              //Se translada la Vaca
    dibujaVaca(modo);                                  //Se dibuja la Vaca colgada de la cuerda
  glPopMatrix();*/
  glPushMatrix();
    glTranslatef(luz3[0],luz3[1]+1,luz3[2]);
    dibujaCubo(modo,5,1,5,1,0,0);                      //Se dibuja la Base

    glTranslatef(0,1,0);                               //Se translada a encima de la Base el Cuerpo
    dibujaCubo(modo,1,5,1,0,1,0);                      //Se dibuja el Cuerpo

    glRotatef(gradosLibertad[0],0,1,0);                //Se rotan los Brazos segun un angulo

    glTranslatef(0,5,0);                               //Se translada el CilindroRotacion
    dibujaCilindro(modo,2,0.5,2);                      //Se dibuja el CilindroRotacion

    glTranslatef(1,0.5,0);                             //Se translada el Brazo primario
    dibujaCubo(modo,6,1,1,0,0,1);                      //Se dibuja el Brazo

    glTranslatef(gradosLibertad[1],0,0);               //Se mueve el brazo extensible
    glTranslatef(2,1,0);                               //Se translada el Brazo extensible
    dibujaCubo(modo,4,0.5,1,0,1,1);                    //Se dibuja el Brazo extensible

    //PRUEBA 3
    glTranslatef(gradosLibertad[3],0,0);               //Se mueve el soporte
    glTranslatef(1.5,-0.5,0);                          //Se translada el soporte
    dibujaCubo(modo,1,0.5,1,0,0,0);                    //Se dibuja el soporte de la cuerda
    //FIN PRUEBA 3

    glTranslatef(0,gradosLibertad[2],0);               //Se mueve la cuerda
    glTranslatef(0,-2,0);                              //Se translada la Cuerda
    dibujaCilindro(modo,0.1,-gradosLibertad[2]+2,0.1); //Se dibuja la Cuerda del brazo extensible

    glTranslatef(0,-2,0);                              //Se translada la Vaca
    dibujaVaca(modo);                                  //Se dibuja la Vaca colgada de la cuerda
  glPopMatrix();

  glPushMatrix();
    glScalef(100,1,100);
    cubo->dibujar(modo);
  glPopMatrix();

}

void Jerarquico::animacion(){
    if(gradosLibertad[0] <= 50){
      velocidad[0] = 1;
      gradosLibertad[0] += 1.0;
    }
    else if(gradosLibertad[0] > 50 && gradosLibertad[0] < 2000){
      velocidad[0] += 0.2;
      gradosLibertad[0] += velocidad[0];
      if(gradosLibertad[2] > -3) gradosLibertad[2] -= velocidad[2];
      if(gradosLibertad[1] < 2) gradosLibertad[1] += velocidad[1];
    }
    else if(gradosLibertad[0] >= 2000){
      velocidad[0] -= 0.5;
      gradosLibertad[0] += velocidad[0];
      if(gradosLibertad[2] < 0) gradosLibertad[2] += velocidad[2];
      if(gradosLibertad[1] > 0) gradosLibertad[1] -= velocidad[1];
    }
}

void Jerarquico::setGradoLibertadLuz1(int pos, float valor){ luz1[pos] = valor; }
void Jerarquico::setGradoLibertadLuz2(int pos, float valor){ luz2[pos] = valor; }
void Jerarquico::setGradoLibertadLuz3(int pos, float valor){ luz3[pos] = valor; }
float Jerarquico::getGradoLibertadLuz1(int pos){ return luz1[pos]; }
float Jerarquico::getGradoLibertadLuz2(int pos){ return luz2[pos]; }
float Jerarquico::getGradoLibertadLuz3(int pos){ return luz3[pos]; }

void Jerarquico::setGradoLibertad(int pos, float valor){ gradosLibertad[pos] = valor; }
void Jerarquico::setVelocidad(int pos, float valor){ velocidad[pos] = valor; }
void Jerarquico::setModoAnimacion(bool estado){ esta_animado = estado; }

float Jerarquico::getGradoLibertad(int pos){ return gradosLibertad[pos]; }
float Jerarquico::getVelocidad(int pos){ return velocidad[pos]; }
bool Jerarquico::getModoAnimacion(){ return esta_animado; }
