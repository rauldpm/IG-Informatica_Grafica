#  Alumno: Raul Del Pozo Moreno
#  Asignatura: Informatica Grafica

SRC = src
INC = include
OBJ = obj
BIN = bin

CXX = g++
CXXFLAGS= -g -I$(INC) -std=c++11
LDFLAGS= -lGLU -lGL -lglut


all: directories $(BIN)/practica1

$(BIN)/practica1: $(OBJ)/practica1.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/figura.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o
	$(CXX) -o $@ $(CXXFLAGS) $(OBJ)/practica1.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/figura.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(LDFLAGS)

$(OBJ)/practica1.o: $(SRC)/practica1.cc $(INC)/escena.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/practica1.cc

$(OBJ)/escena.o: $(SRC)/escena.cc $(INC)/escena.h $(INC)/tetraedro.h $(INC)/cubo.h $(INC)/figura.h $(INC)/ejes.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/escena.cc

$(OBJ)/ejes.o: $(SRC)/ejes.cc $(INC)/ejes.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/ejes.cc

$(OBJ)/figura.o: $(SRC)/figura.cc $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/figura.cc

$(OBJ)/cubo.o: $(SRC)/cubo.cc $(INC)/cubo.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/cubo.cc

$(OBJ)/tetraedro.o: $(SRC)/tetraedro.cc $(INC)/tetraedro.h $(INC)/figura.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/tetraedro.cc

directories: 
	mkdir -p obj bin

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*

superclean:
	rm -f $(OBJ)/*.o
	rm $(SRC)/*~ $(INC)/*~
	rm -f $(BIN)/*
