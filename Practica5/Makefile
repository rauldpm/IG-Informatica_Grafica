#Alumno: Raul Del Pozo Moreno
#Asignatura: Informatica Grafica
#Practica 5 -- Interaccion


SRC = src
INC = include
OBJ = obj
BIN = bin

CXX = g++
CXXFLAGS= -g -Wall -I$(INC) -std=c++11
LDFLAGS= -lGLU -lGL -lglut -L/usr/X11R6/lib/ -lGL -lGLU -lglut -lm -lX11 -lpthread

all: directories $(BIN)/practica5

OBJECTS = $(OBJ)/practica5.o $(OBJ)/camara.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/file_ply_stl.o $(OBJ)/textura.o $(OBJ)/luz.o $(OBJ)/material.o $(OBJ)/jerarquico.o $(OBJ)/figura.o $(OBJ)/revolucion.o $(OBJ)/ply.o $(OBJ)/octaedro.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/cuadro.o

$(BIN)/practica5: $(OBJECTS)
	$(CXX) -o $(BIN)/practica5 $(CXXFLAGS) $(OBJECTS) $(LDFLAGS)

$(OBJ)/practica5.o: $(SRC)/practica5.cc $(INC)/escena.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/practica5.cc

$(OBJ)/escena.o: $(SRC)/escena.cc $(INC)/escena.h $(INC)/camara.h $(INC)/tetraedro.h $(INC)/cubo.h $(INC)/octaedro.h $(INC)/ply.h $(INC)/revolucion.h $(INC)/figura.h $(INC)/ejes.h $(INC)/luz.h $(INC)/material.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/escena.cc

$(OBJ)/ejes.o: $(SRC)/ejes.cc $(INC)/ejes.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/ejes.cc

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(INC)/file_ply_stl.h $(INC)/vertex.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/file_ply_stl.cc

$(OBJ)/camara.o: $(SRC)/camara.cc $(INC)/camara.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/camara.cc

$(OBJ)/jerarquico.o: $(SRC)/jerarquico.cc $(INC)/jerarquico.h $(INC)/ply.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/jerarquico.cc

$(OBJ)/luz.o: $(SRC)/luz.cc $(INC)/luz.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/luz.cc

$(OBJ)/material.o: $(SRC)/material.cc $(INC)/material.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/material.cc

$(OBJ)/textura.o: $(SRC)/textura.cc $(INC)/textura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/textura.cc

$(OBJ)/figura.o: $(SRC)/figura.cc $(INC)/figura.h $(INC)/vertex.h $(INC)/luz.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/figura.cc

$(OBJ)/revolucion.o: $(SRC)/revolucion.cc $(INC)/revolucion.h $(INC)/file_ply_stl.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/revolucion.cc

$(OBJ)/ply.o: $(SRC)/ply.cc $(INC)/ply.h $(INC)/file_ply_stl.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/ply.cc

$(OBJ)/octaedro.o: $(SRC)/octaedro.cc $(INC)/octaedro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/octaedro.cc

$(OBJ)/cubo.o: $(SRC)/cubo.cc $(INC)/cubo.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/cubo.cc

$(OBJ)/tetraedro.o: $(SRC)/tetraedro.cc $(INC)/tetraedro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/tetraedro.cc

$(OBJ)/cuadro.o: $(SRC)/cuadro.cc $(INC)/cuadro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/cuadro.cc

directories: 
	mkdir -p obj bin

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*

superclean:
	rm -f $(OBJ)/*.o
	rm $(SRC)/*~ $(INC)/*~
	rm -f $(BIN)/*
