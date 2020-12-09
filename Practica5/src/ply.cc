/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#include "file_ply_stl.h"
#include "ply.h"

Ply::Ply(){};

Ply::Ply(const char *fichero){

  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;

	if(File_ply.open(fichero)){

    File_ply.read(Vertices,Triangles);

    for(unsigned int i = 0; i < Vertices.size() ; i++){
      Figura::vertices.push_back(Vertices[i].x);
      Figura::vertices.push_back(Vertices[i].y);
      Figura::vertices.push_back(Vertices[i].z);
    }

    for(unsigned int i = 0; i < Triangles.size() ; i++){
      Figura::caras.push_back(Triangles[i].x);
      Figura::caras.push_back(Triangles[i].y);
      Figura::caras.push_back(Triangles[i].z);
    }
    calculoNormales();
    rellenarCarasParesImpares();
    rellenarColores();
  }
  else std::cout << "File can't be opened" << std::endl;
}
