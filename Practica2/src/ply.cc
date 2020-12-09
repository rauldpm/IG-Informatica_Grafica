/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "file_ply_stl.h"
#include "ply.h"

Ply::Ply(){};

//Constructor con parametros
Ply::Ply(char *fichero){
  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;

	//Lectura de fichero
	if(File_ply.open(fichero)){
		File_ply.read(Vertices,Triangles);
		std::cout << "File read correctly" << std::endl;
	}
	else std::cout << "File can't be opened" << std::endl;

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
