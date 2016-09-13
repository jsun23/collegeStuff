#this is the makefile for HW1


ARGS=
PGM=	Driver
#SRC=	$(PGM).c
SRC=	$(PGM).cpp
#FLAGS=	-pg
FLAGS=	-O2
#CC=	gcc
CC=	g++
$(PGM):	$(SRC)
	$(CC) -o $(PGM) $(SRC) $(FLAGS)
#	$(CC) -o $(PGM) $(SRC) Driver.o $(FLAGS)
someLibrary.o:	Driver.c
	$(CC) -c Driver.c $(FLAGS)
test:	$(PGM)
	./$(PGM) $(ARGS)
clean:
	rm -f Driver.o $(PGM)
