CPPFLAGS=-g -O0 -Wall -Werror
SRC=src
BLD=build
NECESSARY= main.o vector3d.o

default: main

main: ${NECESSARY}
	g++ $^ -o $@ ${CPPFLAGS}

main.o: vector3d.hpp

vector3d.o: vector3d.hpp

%.o: %.cpp
	g++ -c $< -o $@ ${CPPFLAGS}

clean:
	rm -rf main *.o
