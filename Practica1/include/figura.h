/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
*/

#ifndef _FIGURA_H
#define _FIGURA_H

#include <vector>
using namespace std;

class Figura {
  protected:
    vector<GLint> indices;
    vector<GLint> indicesPares;
    vector<GLint> indicesImpares;
    vector<GLfloat> vertices;
    vector<GLfloat> color1; //Puntos
    vector<GLfloat> color2; //Aristas
    vector<GLfloat> color3; //Solido
    int num_indices;
    int num_vertices;

  public:
    Figura();
    int getNIndices(){return num_indices;}
    int getNVertices(){return num_vertices;}
    void setNIndices(int indices){ num_indices = indices;}
    void setNVertices(int vertices){num_vertices = vertices;}
    void dibujar(int modo);
};

#endif
