/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#include "file_ply_stl.h"
#include "ply.h"

Ply::Ply(){};

//Constructor con parametros
Ply::Ply(const char *fichero){

  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;

	//Si se consigue abrir el fichero
	if(File_ply.open(fichero)){
    //Se lee el fichero
    File_ply.read(Vertices,Triangles);

    //Paso de vertices del perfil original
    for(int i = 0; i < Vertices.size() ; i++){
      Figura::vertices.push_back(Vertices[i].x);
      Figura::vertices.push_back(Vertices[i].y);
      Figura::vertices.push_back(Vertices[i].z);
    }
    //Paso de caras del perfil original
    for(int i = 0; i < Triangles.size() ; i++){
      Figura::caras.push_back(Triangles[i].x);
      Figura::caras.push_back(Triangles[i].y);
      Figura::caras.push_back(Triangles[i].z);
    }
    //Se rellenan las caras para el modo Ajedrez
    rellenarCarasParesImpares();
    //Colores
    rellenarColores();
  }
  else std::cout << "File can't be opened" << std::endl;
}
