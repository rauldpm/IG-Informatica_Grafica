/*
  Alumno: Raul Del Pozo Moreno
  Asignatura: Informatica Grafica
  Practica 5 -- Interaccion
*/

#ifndef _CAMARA_H
#define _CAMARA_H

class Camara{
  private:
  	int Observer_distance,     Observer_angle_x,     Observer_angle_y,     zoom;
    int Observer_distance_ori, Observer_angle_x_ori, Observer_angle_y_ori, zoom_ori;
    int pos, pos_ori;
    bool examinar, examinar_ori;
  public:
    Camara();
    Camara(int Observer, int angleX, int angleY, int z, int p);

    void setObservador();
    void girar(int x, int y);
    void info();
    void restablecer();

    void setObserverAngleX(int x);
    void setObserverAngleY(int y);
    void setObserverDistance(int z);

    void aumentarObserverAngleX();
    void aumentarObserverAngleY();
    void aumentarObserverDistance();

    void disminuirObserverAngleX();
    void disminuirObserverAngleY();
    void disminuirObserverDistance();

    int getObserverAngleX();
    int getObserverAngleY();
    int getObserverDistance();

    void aumentarZoom();
    void disminuirZoom();
    int getZoom();

    void avanzar();
    void retroceder();
    void izquierda();
    void derecha();

    void setExaminar(bool exa);
    bool getExaminar();
};
#endif
