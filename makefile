#Jessica Bao 1001124828
#makefile for C++ program
SRC = Code5_1001124828.cpp
SRC1 = CokeMachine.cpp
SRC2 = CokeLib.cpp
SRC3 = VendingMachine.cpp
OBJ = $(SRC:.cpp=.o)
OBJ1 = $(SRC1:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)
OBJ3 = $(SRC3:.cpp=.o)
EXE = $(SRC:.cpp=.e)



HFILES1 = CokeMachine.h
HFILES2 = CokeLib.h
HFILES3 = VendingMachine.h

GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
CFLAGS = -g -std=c++11

all : $(EXE)
 
$(EXE): $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3)
	g++ $(CFLAGS) $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) -o $(EXE) $(GTKFLAGS) 


$(OBJ) : $(SRC) $(HFILES1) $(HFILES2) $(HFILES3)
	g++ -c $(CFLAGS) $(SRC) -o $(OBJ)	$(GTKFLAGS)
$(OBJ1) : $(SRC1) $(HFILES1) $(HFILES2) $(HFILES3)
	g++ -c $(CFLAGS) $(SRC1) -o $(OBJ1) $(GTKFLAGS) 
$(OBJ2) : $(SRC2) $(HFILES1) $(HFILES2) $(HFILES3)
	g++ -c $(CFLAGS) $(SRC2) -o $(OBJ2) $(GTKFLAGS)
$(OBJ3) : $(SRC3) $(HFILES1) $(HFILES2) $(HFILES3)
	g++ -c $(CFLAGS) $(SRC3) -o $(OBJ3) $(GTKFLAGS)

