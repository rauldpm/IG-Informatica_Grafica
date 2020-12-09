/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/
 
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "camara.h"

Camara::Camara(int Observer, int angleX, int angleY, int z, int p){
  Observer_distance_ori = Observer_distance = Observer;
  Observer_angle_y_ori = Observer_angle_y = angleX;
  Observer_angle_x_ori = Observer_angle_x = angleY;
  zoom_ori = zoom = z;
  pos_ori = pos = p;
  examinar_ori = examinar = false;
} 

Camara::Camara(){
  Observer_distance_ori = Observer_distance = 200;
  Observer_angle_x_ori = Observer_angle_x = 0;
  Observer_angle_y_ori = Observer_angle_y = 0;
  zoom_ori = zoom = 10;
  pos_ori = pos = 0;
  examinar_ori = examinar = false;
} 

void Camara::setObservador(){
  glTranslatef(pos,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

void Camara::girar(int x, int y){
  if(examinar){
    
  }
  else{
    Observer_angle_x += x;
    Observer_angle_y += y;
  }
}

void Camara::info(){
  std::cout << "Observador en: 0 - 0 - " << Observer_distance << std::endl; 
  std::cout << "Angulo x: " << Observer_angle_x << " Angulo y: " << Observer_angle_y << std::endl;
  std::cout << "Zoom: " << zoom << std::endl << std::endl;
}

void Camara::restablecer(){
  Observer_distance = Observer_distance_ori;
  Observer_angle_x = Observer_angle_x_ori;
  Observer_angle_y = Observer_angle_y_ori;
  zoom = zoom_ori;
  pos = pos_ori;
  examinar = examinar_ori;
}

//Modificadores de la camara
void Camara::setObserverAngleX(int x){ Observer_angle_x   = x;  }
void Camara::setObserverAngleY(int y){ Observer_angle_y   = y;  }
void Camara::setObserverDistance(int z){ Observer_distance  = z;  }

void Camara::aumentarObserverAngleX(){ Observer_angle_x   += 1;  }
void Camara::aumentarObserverAngleY(){ Observer_angle_y   += 1;  }
void Camara::aumentarObserverDistance(){ Observer_distance  += 1;  }

void Camara::disminuirObserverAngleX(){ Observer_angle_x  -= 1;  }
void Camara::disminuirObserverAngleY(){ Observer_angle_y  -= 1;  }
void Camara::disminuirObserverDistance(){ Observer_distance -= 1;  }

int Camara::getObserverAngleX(){ return Observer_angle_x;  }
int Camara::getObserverAngleY(){ return Observer_angle_y;  }
int Camara::getObserverDistance(){ return Observer_distance; }

void Camara::aumentarZoom(){  zoom++;  }
void Camara::disminuirZoom(){ zoom--; }
int Camara::getZoom(){ return zoom;   }

//Movimiento de la camara 
void Camara::avanzar(){ Observer_distance--; }
void Camara::retroceder(){ Observer_distance++; }
void Camara::izquierda(){ pos++; }
void Camara::derecha(){ pos--; }

//Modo seleccion
void Camara::setExaminar(bool exa){ examinar = exa; }
bool Camara::getExaminar(){ return examinar; }


