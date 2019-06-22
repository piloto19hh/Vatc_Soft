all: main airport vuelo
	g++ -o vatc.x main.o airport.o vuelo.o

main: main.cpp
	g++ -c main.cpp

airport: airport.h airport.cpp
	g++ -c airport.cpp

vuelo: vuelo.cpp
	g++ -c vuelo.cpp

clean:
	rm -f *.o
