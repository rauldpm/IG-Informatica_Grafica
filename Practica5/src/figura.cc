/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#include <GL/gl.h>
#include <GL/glut.h>


#include "luz.h"
#include "figura.h"

Figura::Figura(){
  verticesTextura.push_back(0); verticesTextura.push_back(0);
  verticesTextura.push_back(1); verticesTextura.push_back(0);
  verticesTextura.push_back(0); verticesTextura.push_back(1);
  verticesTextura.push_back(1); verticesTextura.push_back(1);
}

void Figura::dibujar(int modo){

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
  glEnableClientState(GL_COLOR_ARRAY);
  glPointSize(5);

  //Modo puntos, arista/alambre, solido
  if(modo >= 1 && modo < 4){
    if(modo == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    else if (modo == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (modo == 3) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorPointer(3,GL_FLOAT,0,&color4[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);
  }
  //Modo ajedrez
  else if(modo == 4){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColorPointer(3,GL_FLOAT,0,&color3[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,carasPares.size(),GL_UNSIGNED_INT,&carasPares[0]);

    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,carasImpares.size(),GL_UNSIGNED_INT,&carasImpares[0]);
  }
  //Modo PRUEBA PRACTICA 1 -> mostrar puntos, arista/alambre y solido a la vez con colores diferentes
  else if(modo == 5){
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColorPointer(3,GL_FLOAT,0,&color1[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColorPointer(3,GL_FLOAT,0,&color2[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorPointer(3,GL_FLOAT,0,&color3[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &verticesTextura[0]);
    glDrawElements(GL_TRIANGLES,caras.size(),GL_UNSIGNED_INT,&caras[0]);
  }

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

void Figura::calculoNormales(){

    normalesVertices.resize(vertices.size());

    for(unsigned int i = 0 ; i < caras.size() ; i += 3){

        float px = vertices[3*caras[i+1]]  -vertices[3*caras[i]];
        float py = vertices[3*caras[i+1]+1]-vertices[3*caras[i]+1];
        float pz = vertices[3*caras[i+1]+2]-vertices[3*caras[i]+2];

        float qx = vertices[3*caras[i+2]]  -vertices[3*caras[i]];
        float qy = vertices[3*caras[i+2]+1]-vertices[3*caras[i]+1];
        float qz = vertices[3*caras[i+2]+2]-vertices[3*caras[i]+2];

        float nx = py*qz-pz*qy;
        float ny = -(px*qz-pz*qx);
        float nz = px*qy-py*qx;

        normalesVertices[3*caras[i]]   += nx;
        normalesVertices[3*caras[i]+1] += ny;
        normalesVertices[3*caras[i]+2] += nz;

        normalesVertices[3*caras[i+1]]   += nx;
        normalesVertices[3*caras[i+1]+1] += ny;
        normalesVertices[3*caras[i+1]+2] += nz;

        normalesVertices[3*caras[i+2]]   += nx;
        normalesVertices[3*caras[i+2]+1] += ny;
        normalesVertices[3*caras[i+2]+2] += nz;
    }

    for(unsigned int i = 0; i < normalesVertices.size(); i += 3){
        float mx = normalesVertices[i];
        float my = normalesVertices[i+1];
        float mz = normalesVertices[i+2];

        float modulo = sqrt(pow(mx,2) + pow(my,2) + pow(mz,2));

        normalesVertices[i] = (mx / modulo);
        normalesVertices[i+1] = (my / modulo);
        normalesVertices[i+2] = (mz / modulo);
    }
}

void Figura::escribirCarasTerminal(){
  for(unsigned int i = 0 ; i < caras.size() ; i+=3)
    std::cout << caras[i] << " " << caras[i+1] << " " << caras[i+2] << std::endl;
  std::cout << std::endl;
}

void Figura::escribirVerticesTerminal(){
  for(unsigned int i = 0 ; i < vertices.size() ; i+=3)
    std::cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << std::endl;
  std::cout << std::endl;
}

void Figura::rellenarColores(){
  for(unsigned int i = 0 ; i < vertices.size()/2 ; i++){
    color1.push_back(0.0f); color1.push_back(1.0f); color1.push_back(0.0f);
    color2.push_back(0.0f); color2.push_back(0.0f); color2.push_back(1.0f);
    color3.push_back(1.0f); color3.push_back(0.0f); color3.push_back(0.0f);
    color4.push_back(1.0f); color4.push_back(0.0f); color4.push_back(1.0f);
  }
}

void Figura::rellenarCarasParesImpares(){
  for(unsigned int i = 0 ; i < caras.size() ; i+=6){
    carasPares.push_back(caras[i]);
    carasPares.push_back(caras[i+1]);
    carasPares.push_back(caras[i+2]);
    carasImpares.push_back(caras[i+3]);
    carasImpares.push_back(caras[i+4]);
    carasImpares.push_back(caras[i+5]);
  }
}

void Figura::rellenarColores(float r1, float r2, float r3){
  color1.resize(0);
  color2.resize(0);
  color3.resize(0);
  color4.resize(0);
  for(unsigned int i = 0 ; i < vertices.size()/2 ; i++){
    color4.push_back(r1); color4.push_back(r2); color4.push_back(r3);
    color4.push_back(r1); color4.push_back(r2); color4.push_back(r3);
    color4.push_back(r1); color4.push_back(r2); color4.push_back(r3);
    color4.push_back(r1); color4.push_back(r2); color4.push_back(r3);
  }
}
