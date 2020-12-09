/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 2 -- Modelos PLY y Poligonales
*/

#define _USE_MATH_DEFINES


#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "file_ply_stl.h"
#include "math.h"
#include "revolucion.h"

//Revolucion::Revolucion();

Revolucion::Revolucion(vector<float> vPrueba){

  for(int i = 0; i < vPrueba.size() ; i++){
    Figura::vertices.push_back(vPrueba[i]);
    original.push_back(vPrueba[i]);
  }

  setEjeRotacion();

  //Si se da el vector al reves
  if(Figura::vertices[1] > vertices[4]){
    vector<float> temporal;
    //Rellenamos el vector auxiliar al reves
    for(int i = vertices.size()-1 ; i >= 0; i-=3){
        temporal.push_back(vertices[i-2]);
        temporal.push_back(vertices[i-1]);
        temporal.push_back(vertices[i]);
    }
    //Limpiamos el vector de vertices y el original
    Figura::vertices.resize(0);
    original.resize(0);
    //Rellenamos el vector de vertices de la figura y el original
    for(int i = 0 ; i < temporal.size() ; i++){
      Figura::vertices.push_back(temporal[i]);
      original.push_back(temporal[i]);
    }
  }

  //Se comprueba si hay un punto inferior definido en el ply
  hayPuntoBajo();
  //Se comprueba si hay un punto superior definido en el ply
  hayPuntoAlto();

}



Revolucion::Revolucion(char *fichero){
  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;

	//Lectura de fichero
	if (File_ply.open(fichero)){
		File_ply.read(Vertices,Triangles);
		std::cout << "File read correctly" << std::endl;
	}
	else std::cout << "File can't be opened" << std::endl;

  //Paso de vertices del perfil original
  for(int i = 0; i < Vertices.size() ; i++){
    //Este vector esta en Figura y es donde se van a almacenar el contorno generado
    Figura::vertices.push_back(Vertices[i].x);
    Figura::vertices.push_back(Vertices[i].y);
    Figura::vertices.push_back(Vertices[i].z);

    //Este vector esta en revolucion y se usa para guardar el vector original
    original.push_back(Vertices[i].x);
    original.push_back(Vertices[i].y);
    original.push_back(Vertices[i].z);
  }

  //Se le asigna a revolucion el eje sobre el que se va a rotar la figura
  setEjeRotacion();

  //Si se da el vector al reves
  if(Figura::vertices[1] > vertices[4]){
    vector<float> temporal;
    //Rellenamos el vector auxiliar al reves
    for(int i = vertices.size()-1 ; i >= 0; i-=3){
        temporal.push_back(vertices[i-2]);
        temporal.push_back(vertices[i-1]);
        temporal.push_back(vertices[i]);
    }
    //Limpiamos el vector de vertices y el original
    Figura::vertices.resize(0);
    original.resize(0);
    //Rellenamos el vector de vertices de la figura y el original
    for(int i = 0 ; i < temporal.size() ; i++){
      Figura::vertices.push_back(temporal[i]);
      original.push_back(temporal[i]);
    }
  }

  //Se comprueba si hay un punto inferior definido en el ply
  hayPuntoBajo();
  //Se comprueba si hay un punto superior definido en el ply
  hayPuntoAlto();
}

void Revolucion::leerVertTeclado(){
  //Se pide el numero de vertices a introducir
  int num_vert;
  std::cout << "Introduce el numero de vertices: ";
  std::cin >> num_vert;

  //Se leen los valores por teclado
  std::cout << "Introduce los tres valores del vertice separados por espacio" << std::endl;
  for(int i = 0 ; i < num_vert ; i++){
    float valor;
    std::cin >> valor;
    Figura::vertices.push_back(valor);
    original.push_back(valor);
    std::cin >> valor;
    Figura::vertices.push_back(valor);
    original.push_back(valor);
    std::cin >> valor;
    Figura::vertices.push_back(valor);
    original.push_back(valor);
  }

  //Se le asigna a revolucion el eje sobre el que se va a rotar la figura
  setEjeRotacion();

  //Se comprueba si hay un punto inferior definido en el ply
  hayPuntoBajo();
  //Se comprueba si hay un punto superior definido en el ply
  hayPuntoAlto();
}

void Revolucion::nuevosVertInd(int modo){
    /*
      Este metodo haria la funcion de un Constructor
      Se recurre a el debido a la necesidad de dibujar el tiempo
      real de forma dinamica un objeto cambiante

      Por lo tanto, el metodo se encarga de redimensionar el vector
      de vertices y de caras existentes con nuevos valores
    */

    //Se resetea los vertices
    Figura::vertices.resize(0);
    Figura::carasPares.resize(0);
    Figura::carasImpares.resize(0);
    Figura::caras.resize(0);

    //Se genera el contorno
    generarContorno(num_revoluciones);

    //Se comprueba si se pinta con o sin tapas
    if(modo != 1){
      //Se crea la tapa inferior
      crearTapaInferior(num_revoluciones);
      //Se crea la tapa superior
      crearTapaSuperior(num_revoluciones);
    }
    //Se rellenan las caras para el modo Ajedrez
    rellenarCarasParesImpares();
    //Colores
    rellenarColores();
}

void Revolucion::hayPuntoBajo(){
  /*
    Se comprueba el eje sobre el que se rota
    Se guarda el punto mas bajo
    Si hay punto bajo en el eje, se guarda el vector sin ese vertice
    Sino guardamos todo el vector
  */
  if(eje_rotacion == 'y'){
    punto_mas_bajo = original[1];
    if(original[0] == 0.0 && original[2] == 0.0){
      hay_punto_bajo = true;
      for(int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
  else if(eje_rotacion == 'x'){
    punto_mas_bajo = original[0];
    if(original[1] == 0.0 && original[2] == 0.0){
      hay_punto_bajo = true;
      for(int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
  else{
    punto_mas_bajo = original[2];
    if(original[0] == 0.0 && original[1] == 0.0){
      hay_punto_bajo = true;
      for(int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
}

void Revolucion::hayPuntoAlto(){
  /*
    Se comprueba el eje sobre el que se rota
    Se guarda el punto mas alto
    Si hay punto alto en el eje, se guarda el vector sin ese vertice
  */

  if(eje_rotacion == 'y'){
    punto_mas_alto = original[original.size()-2];
    if(original[original.size()-3] == 0.0 && original[original.size()-1] == 0.0){
      hay_punto_alto = true;
      for(int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
  else if(eje_rotacion == 'x'){
    punto_mas_alto = original[original.size()-3];
    if(original[original.size()-2] == 0.0 && original[original.size()-1] == 0.0){
      hay_punto_alto = true;
      for(int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
  else{
    punto_mas_alto = original[original.size()-1];
    if(original[original.size()-3] == 0.0 && original[original.size()-2] == 0.0){
      hay_punto_alto = true;
      for(int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
}

void Revolucion::generarContorno(int num_revoluciones){
  //Inicializamos el vector a pintar con los valores del perfil
  for(int i = 0 ; i < originalSinEje.size() ; i++) Figura::vertices.push_back(originalSinEje[i]);

  //Angulo en el que se van a pintar los vertices
  double angulo = 2*M_PI/num_revoluciones;
  //Para cada revolucion a pintar
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    //Se recorre todo el perfil
    for(int j = 0 ; j < originalSinEje.size() ; j+=3){
      //Si es el eje y, se rota en ese eje
      if(eje_rotacion == 'y'){
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j] + sin((i+1)*angulo)*originalSinEje[j+2]);
        Figura::vertices.push_back(originalSinEje[j+1]);
        Figura::vertices.push_back(-sin((i+1)*angulo)*originalSinEje[j] + cos((i+1)*angulo)*originalSinEje[j+2]);
      }
      //Si es el eje x, se rota en ese eje
      else if(eje_rotacion == 'x'){
        Figura::vertices.push_back(originalSinEje[j]);
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j+1] - sin((i+1)*angulo)*originalSinEje[j+2]);
        Figura::vertices.push_back(sin((i+1)*angulo)*originalSinEje[j+1] + cos((i+1)*angulo)*originalSinEje[j+2]);
      }
      //Sino, es el eje z, se rota en ese eje
      else{
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j] - sin((i+1)*angulo)*originalSinEje[j+1]);
        Figura::vertices.push_back(sin((i+1)*angulo)*originalSinEje[j] + cos((i+1)*angulo)*originalSinEje[j+1]);
        Figura::vertices.push_back(originalSinEje[j+2]);
      }
    }
  }
  //Se generan las caras para cara revolucion
  for(int i =  0 ; i < num_revoluciones-1 ; i++){
    //Se recorre todo el perfil
    for(int j = 0 ; j < originalSinEje.size()/3-1 ; j++){
      Figura::caras.push_back(j+i*originalSinEje.size()/3);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+1);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3);

      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3);
      Figura::caras.push_back((j+1)+i*originalSinEje.size()/3);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3+1);
    }
  }
  //Se generan la ultima cara que une los vertices iniciales con los vertices finales
  for(int j = 0 ; j < originalSinEje.size()/3-1 ; j++){
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+1);
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+2);
    Figura::caras.push_back(j);

    Figura::caras.push_back(j);
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+2);
    Figura::caras.push_back(j+1);
  }
}

void Revolucion::crearTapaInferior(int num_revoluciones){
  //Se coloca el punto mas bajo en funcion del eje a rotar
  if(eje_rotacion == 'y'){
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(punto_mas_bajo);
    Figura::vertices.push_back(0.0);
  }
  else if(eje_rotacion == 'x'){
    Figura::vertices.push_back(punto_mas_bajo);
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(0.0);
  }
  else{
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(punto_mas_bajo);
  }
  //Se añaden las caras de la tapa inferior
  int tam = originalSinEje.size()/3;
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    Figura::caras.push_back(tam*num_revoluciones);
    Figura::caras.push_back(tam*i);
    Figura::caras.push_back(tam*i+tam);
  }
  //Se añade la ultima cara
  Figura::caras.push_back(tam*num_revoluciones);
  Figura::caras.push_back(tam*num_revoluciones-tam);
  Figura::caras.push_back(0);
}

void Revolucion::crearTapaSuperior(int num_revoluciones){
  //Se coloca el punto mas alto en funcion del eje a rotar
  if(eje_rotacion == 'y'){
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(punto_mas_alto);
    Figura::vertices.push_back(0.0);
  }
  else if(eje_rotacion == 'x'){
    Figura::vertices.push_back(punto_mas_alto);
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(0.0);
  }
  else{
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(0.0);
    Figura::vertices.push_back(punto_mas_alto);
  }
  //Se añaden las caras de la tapa superior
  int tam = originalSinEje.size()/3;
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    Figura::caras.push_back(tam*i+tam-1);
    Figura::caras.push_back(tam*num_revoluciones+1);
    Figura::caras.push_back(tam*(i+1)+tam-1);
  }
  //Se añade la ultima cara
  Figura::caras.push_back(tam*num_revoluciones-1);
  Figura::caras.push_back(tam*num_revoluciones+1);
  Figura::caras.push_back(tam-1);
}

void Revolucion::aumentarRevoluciones(){
  num_revoluciones++;
}

void Revolucion::reducirRevoluciones(){
  if(num_revoluciones>0) num_revoluciones--;
}

int Revolucion::getNumRevoluciones(){
  return num_revoluciones;
}

void Revolucion::setEjeRotacion(){
  do{
    std::cout << "Introduce el eje de rotacion sobre el que rotara la figura ('x' o 'y' o 'z'): ";
    std::cin >> eje_rotacion;
  }
  while(eje_rotacion != 'x' && eje_rotacion != 'y' && eje_rotacion != 'z');
}
