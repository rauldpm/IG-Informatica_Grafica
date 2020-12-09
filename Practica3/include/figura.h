/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 3 -- Modelos Jerarquicos
*/

#ifndef _FIGURA_H
#define _FIGURA_H

#include <vector>
#include <vertex.h>

class Figura {
  protected:
    //Vector donde se almacenan los vertices de la figura
    std::vector<float> vertices;
    //Vector donde se almacenan las caras de la figura
    std::vector<int> caras;
    //Vector donde se almacenan las caras pares del modo Ajedrez
    std::vector<int> carasPares;
    //Vector donde se almacenan las caras impares del modo Ajedrez
    std::vector<int> carasImpares;
    //Vectores de colores
    std::vector<float> color1; //puntos
    std::vector<float> color2; //Aristas
    std::vector<float> color3; //solido
    std::vector<float> color4; //extra Magenta
  public:
    //Constructor por defecto
    Figura();
    //Metodo que dibuja la figura dado un modo
    void dibujar(int modo);
    //Metodo que muestra los vertices por el terminal
    void escribirVerticesTerminal();
    //Metodo que muestra las caras por el terminal
    void escribirCarasTerminal();
    //Metodo que rellena los vectores de colores
    void rellenarColores();
    //Metodo que rellena los vectores de colores dado dos colores
    void rellenarColores(float r1, float r2, float r3);
    //Metodo que rellena las caras pares e impares a partir del vector de caras
    void rellenarCarasParesImpares();
};

#endif
