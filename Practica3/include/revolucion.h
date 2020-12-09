/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#ifndef _REVOLUCION_H
#define _REVOLUCION_H

#include "figura.h"

class Revolucion : public Figura {
  private:
    //Vector para almacenar los vertices sin punto mas alto ni mas bajo
    std::vector<float> originalSinEje;
    //Vector para almacenar los vertices originales
    std::vector<float> original;
    //Variables para el punto alto y bajo
    float punto_mas_bajo, punto_mas_alto;
    bool hay_punto_bajo = false, hay_punto_alto = false;
    //Variable donde se almacena el numero de revoluciones a pintar
    int num_revoluciones = 30;
    //Variable donde se almacena el eje sobre el que se va a rotar la figura
    char eje_rotacion;
    //Estados de las tapas
    bool tapa = false;
  public:
    //Constructor por defecto
    Revolucion(){};
    //Constructor para la prueba2
    Revolucion(vector<float> vPrueba, int num_rev);
    //Constructor con parametros
    Revolucion(const char *fichero, int num_rev);
    //Metodo que busca en el vector si hay un vertice inferior en el eje o no
    void hayPuntoBajo();
    //Metodo que busca en el vector si hay un vertice superior en el eje o no
    void hayPuntoAlto();
    //Metodo que lee desde el teclado una secuencia de vertices
    void leerVertTeclado();
    //Metodo que a partir de un numero de revoluciones dadas genera el contorno de una figura
    void generarContorno(int rev);
    //Metodo que a partir de un numero de revoluciones dadas genera una tapa inferior
    void crearTapaInferior(int rev);
    //Metodo que a partir de un numero de revoluciones dadas genera una tapa superior
    void crearTapaSuperior(int rev);
    //Metodo que a partir de un modo rehace la figura revolucion
    void nuevosVertInd(bool tapa);
    //Metodo que  aumenta las revoluciones de la figura
    void aumentarRevoluciones();
    //Metodo que reduce las revoluciones de la figura
    void reducirRevoluciones();
    //mMetodo que devuelve las revoluciones de la figura
    int getNumRevoluciones();
    //Metodo que guarda el eje sobre el que se va a rotar
    void setEjeRotacion();
    //Establecer numero de revoluciones
    void setRevoluciones(int r);
    //Establecer estado de tapa
    void setEstadoTapa(bool estado);
    bool getEstadoTapa();
};
#endif