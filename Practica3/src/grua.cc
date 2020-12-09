/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#include <GL/gl.h>
#include <GL/glut.h>

#include "grua.h"

Grua::Grua(){
  //Inicializacion de las velocidades y de los grados de libertad
  for(int i = 0 ; i < 4 ; i++) velocidad[i] = 0.05;
  for(int i = 0 ; i < 4 ; i++) gradosLibertad[i] = 0;
}

//Metodo que dibuja un objeto cubo segun un modo de dibujado, una escala y un color
void Grua::dibujaCubo(float modo, float escalaX, float escalaY, float escalaZ, float color1, float color2, float color3){
  glPushMatrix();
    glScalef(escalaX,escalaY,escalaZ);
    cubo->rellenarColores(color1,color2,color3);
    cubo->dibujar(modo);
  glPopMatrix();
}

//Metodo que dibuja un cilindro segun un modo de dibujado y una escala
void Grua::dibujaCilindro(int modo, float escalaX, float escalaY, float escalaZ){
  glPushMatrix();
    glScalef(escalaX,escalaY,escalaZ);
    cilindro->dibujar(modo);
  glPopMatrix();
}

//Metodo que dibuja una vaca segun un modo de dibujado
void Grua::dibujaVaca(int modo){
  glPushMatrix();
    vaca->dibujar(modo);
  glPopMatrix();
}

//Metodo que dibuja la grua
void Grua::dibujarJ(int modo){
  glPushMatrix();
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
}

//Metodo anima la grua modificando los grados de libertad en funcion de la velocidad
void Grua::animacion(){
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

//Metodo que establece un grado de libertad
void Grua::setGradoLibertad(int pos, float valor){
  gradosLibertad[pos] = valor;
}

//Metodo que consulta un grado de libertad
float Grua::getGradoLibertad(int pos){
  return gradosLibertad[pos];
}

//Metodo que establece una velocidad
void Grua::setVelocidad(int pos, float valor){
  velocidad[pos] = valor;
}

//Metodo que consulta una velocidad
float Grua::getVelocidad(int pos){
  return velocidad[pos];
}

//Metodo que establece el modo de animacion
void Grua::setModoAnimacion(bool estado){
  esta_animado = estado;
}

//Metodo que consulta el modo de animacion
bool Grua::getModoAnimacion(){
  return esta_animado;
}
