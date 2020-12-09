/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#define _USE_MATH_DEFINES

#include "file_ply_stl.h"
#include "math.h"
#include "revolucion.h"

//Revolucion::Revolucion();

Revolucion::Revolucion(vector<float> vPrueba, int num_rev){

  setRevoluciones(num_rev);

  for(unsigned int i = 0; i < vPrueba.size() ; i++){
    Figura::vertices.push_back(vPrueba[i]);
    original.push_back(vPrueba[i]);
  }

  eje_rotacion = 'y';

  if(Figura::vertices[1] > vertices[4]){
    vector<float> temporal;
    for(int i = vertices.size()-1 ; i >= 0; i-=3){
        temporal.push_back(vertices[i-2]);
        temporal.push_back(vertices[i-1]);
        temporal.push_back(vertices[i]);
    }
    Figura::vertices.resize(0);
    original.resize(0);
    for(unsigned int i = 0 ; i < temporal.size() ; i++){
      Figura::vertices.push_back(temporal[i]);
      original.push_back(temporal[i]);
    }
  }

  hayPuntoBajo();
  hayPuntoAlto();
}

Revolucion::Revolucion(const char *fichero, int num_rev){

  setRevoluciones(num_rev);

  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;

	if (File_ply.open(fichero)){
    File_ply.read(Vertices,Triangles);
    for(unsigned int i = 0; i < Vertices.size() ; i++){
      Figura::vertices.push_back(Vertices[i].x);
      Figura::vertices.push_back(Vertices[i].y);
      Figura::vertices.push_back(Vertices[i].z);

      original.push_back(Vertices[i].x);
      original.push_back(Vertices[i].y);
      original.push_back(Vertices[i].z);
    }

    setEjeRotacion();
    hayPuntoBajo();
    hayPuntoAlto();
  }
	else std::cout << "File can't be opened" << std::endl;
}

void Revolucion::leerVertTeclado(){
  int num_vert;
  std::cout << "Introduce el numero de vertices: ";
  std::cin >> num_vert;

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

  setEjeRotacion();
  hayPuntoBajo();
  hayPuntoAlto();
}

void Revolucion::nuevosVertInd(bool tapa){

    Figura::vertices.resize(0);
    Figura::carasPares.resize(0);
    Figura::carasImpares.resize(0);
    Figura::caras.resize(0);

    generarContorno(num_revoluciones);

    if(tapa){
      crearTapaInferior(num_revoluciones);
      crearTapaSuperior(num_revoluciones);
    }

    calculoNormales();
    rellenarCarasParesImpares();
    rellenarColores();
}

void Revolucion::crearFichero(){
  ofstream fs("data/fichero.ply");
    fs << "ply" << endl;
    fs << "format ascii 1.0" << endl;
    fs << "element vertex " << vertices.size()  << endl;
    fs << "property float x" << endl;
    fs << "property float y" << endl;
    fs << "property float z" << endl;
    fs << "element face " << caras.size() << endl;
    fs << "property list uchar uint vertex_indices" << endl;
    fs << "end_header" << endl;
    for(unsigned int i = 0 ; i < vertices.size() ; i++){
      fs << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;
    }
    for(unsigned int i = 0 ; i < caras.size() ; i++){
      fs << caras[i] << " " << caras[i+1] << " " << caras[i+2] << endl;
    }
  fs.close();
}

void Revolucion::hayPuntoBajo(){
  if(eje_rotacion == 'y'){
    punto_mas_bajo = original[1];
    if(original[0] == 0.0 && original[2] == 0.0){
      hay_punto_bajo = true;
      for(unsigned int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(unsigned int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
  else if(eje_rotacion == 'x'){
    punto_mas_bajo = original[0];
    if(original[1] == 0.0 && original[2] == 0.0){
      hay_punto_bajo = true;
      for(unsigned int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(unsigned int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
  else{
    punto_mas_bajo = original[2];
    if(original[0] == 0.0 && original[1] == 0.0){
      hay_punto_bajo = true;
      for(unsigned int i = 3 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
    }
    else for(unsigned int i = 0 ; i < original.size() ; i++) originalSinEje.push_back(original[i]);
  }
}

void Revolucion::hayPuntoAlto(){
  if(eje_rotacion == 'y'){
    punto_mas_alto = original[original.size()-2];
    if(original[original.size()-3] == 0.0 && original[original.size()-1] == 0.0){
      hay_punto_alto = true;
      for(unsigned int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
  else if(eje_rotacion == 'x'){
    punto_mas_alto = original[original.size()-3];
    if(original[original.size()-2] == 0.0 && original[original.size()-1] == 0.0){
      hay_punto_alto = true;
      for(unsigned int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
  else{
    punto_mas_alto = original[original.size()-1];
    if(original[original.size()-3] == 0.0 && original[original.size()-2] == 0.0){
      hay_punto_alto = true;
      for(unsigned int i = 0 ; i < 3 ; i++) originalSinEje.pop_back();
    }
  }
}

void Revolucion::generarContorno(int num_revoluciones){
  for(unsigned int i = 0 ; i < originalSinEje.size() ; i++) Figura::vertices.push_back(originalSinEje[i]);

  double angulo = 2*M_PI/num_revoluciones;
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    for(unsigned int j = 0 ; j < originalSinEje.size() ; j+=3){
      if(eje_rotacion == 'y'){
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j] + sin((i+1)*angulo)*originalSinEje[j+2]);
        Figura::vertices.push_back(originalSinEje[j+1]);
        Figura::vertices.push_back(-sin((i+1)*angulo)*originalSinEje[j] + cos((i+1)*angulo)*originalSinEje[j+2]);
      }
      else if(eje_rotacion == 'x'){
        Figura::vertices.push_back(originalSinEje[j]);
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j+1] - sin((i+1)*angulo)*originalSinEje[j+2]);
        Figura::vertices.push_back(sin((i+1)*angulo)*originalSinEje[j+1] + cos((i+1)*angulo)*originalSinEje[j+2]);
      }
      else{
        Figura::vertices.push_back(cos((i+1)*angulo)*originalSinEje[j] - sin((i+1)*angulo)*originalSinEje[j+1]);
        Figura::vertices.push_back(sin((i+1)*angulo)*originalSinEje[j] + cos((i+1)*angulo)*originalSinEje[j+1]);
        Figura::vertices.push_back(originalSinEje[j+2]);
      }
    }
  }
  for(int i =  0 ; i < num_revoluciones-1 ; i++){
    for(unsigned int j = 0 ; j < originalSinEje.size()/3-1 ; j++){
      Figura::caras.push_back(j+i*originalSinEje.size()/3);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+1);

      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3);
      Figura::caras.push_back((j+i*originalSinEje.size()/3)+originalSinEje.size()/3+1);
      Figura::caras.push_back((j+1)+i*originalSinEje.size()/3);
    }
  }
  for(unsigned int j = 0 ; j < originalSinEje.size()/3-1 ; j++){
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+1);
    Figura::caras.push_back(j);
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+2);

    Figura::caras.push_back(j);
    Figura::caras.push_back(j+1);
    Figura::caras.push_back(Figura::vertices.size()/3-1-originalSinEje.size()/3+j+2);
  }
}

void Revolucion::crearTapaInferior(int num_revoluciones){
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
  int tam = originalSinEje.size()/3;
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    Figura::caras.push_back(tam*num_revoluciones);
    Figura::caras.push_back(tam*i+tam);
    Figura::caras.push_back(tam*i);
  }
  Figura::caras.push_back(tam*num_revoluciones);
  Figura::caras.push_back(0);
  Figura::caras.push_back(tam*num_revoluciones-tam);

}

void Revolucion::crearTapaSuperior(int num_revoluciones){
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
  int tam = originalSinEje.size()/3;
  for(int i = 0 ; i < num_revoluciones-1 ; i++){
    Figura::caras.push_back(tam*i+tam-1);
    Figura::caras.push_back(tam*(i+1)+tam-1);
    Figura::caras.push_back(tam*num_revoluciones+1);
  }
  Figura::caras.push_back(tam*num_revoluciones-1);
  Figura::caras.push_back(tam-1);
  Figura::caras.push_back(tam*num_revoluciones+1);
}

void Revolucion::aumentarRevoluciones(){ num_revoluciones++; }
void Revolucion::reducirRevoluciones(){ if(num_revoluciones>0) num_revoluciones--; }

void Revolucion::setEstadoTapa(bool estado){ tapa = estado; }
void Revolucion::setRevoluciones(int r){ num_revoluciones = r; }
void Revolucion::setEjeRotacion(){
  do{
    std::cout << "Introduce el eje de rotacion valido ('x' o 'y' o 'z'): ";
    std::cin >> eje_rotacion;
  }
  while(eje_rotacion != 'x' && eje_rotacion != 'y' && eje_rotacion != 'z');
}

int Revolucion::getNumRevoluciones(){ return num_revoluciones; }
bool Revolucion::getEstadoTapa(){ return tapa; }
