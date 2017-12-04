CC=g++
CFLAGS=-lm -Wall -std=c++11
SRC = src
LIB = lib

all: terrarium

terrarium:
	$(CC) $(CFLAGS) ./$(SRC)/terrarium.cpp ./$(LIB)/cartesian_coord.cpp ./$(LIB)/spherical_coord.cpp ./$(LIB)/protoplanetary_object.cpp ./$(LIB)/constants.cpp ./$(LIB)/gravity.cpp -o terrarium.exe

clean:
	rm terrarium.exe
