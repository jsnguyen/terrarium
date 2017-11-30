CC=g++
CFLAGS=-lm -Wall -std=c++11
SRC = src
LIB = lib

all: terrarium

terrarium:
	$(CC) $(CFLAGS) ./$(SRC)/terrarium.cpp ./$(LIB)/cartesian_coord.cpp ./$(LIB)/spherical_coord.cpp ./$(LIB)/particle.cpp ./$(LIB)/protoplanetary_object.cpp ./$(LIB)/constants.cpp -o terrarium.exe

clean:
	rm pair_search.exe reduced_halo_pair_finder.exe
