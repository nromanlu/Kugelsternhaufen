#
#	Makefile
#	OpenMP Sternkugelhaufen
#	Nicolás Román Lüthold & Flavio La Morea
#

CC=g++
CFLAGS=-Wall -fopenmp
 
all: openmp

openmp: main.o stern.o
	$(CC) $(CFLAGS) main.o stern.o -o KugStSim

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

stern.o:	stern.cpp
	$(CC) -c $(CFLAGS) stern.cpp

clean:
	${RM} *.o *.csv KugStSim
