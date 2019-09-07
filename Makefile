CPPFLAGS=-g -std=c++11 -O0 -Wall -Werror
SRC=src
BLD=build
NECESSARY= vector3d.o particle.o world.o

TEST=test_vector3d test_particle

default: main

test: ${TEST}

main: main.o ${NECESSARY}
	g++ $^ -o $@ ${CPPFLAGS}

test_vector3d: test_vector3d.o vector3d.o
	g++ $^ -o $@ ${CPPFLAGS}

test_particle: test_particle.o vector3d.o particle.o
	g++ $^ -o $@ ${CPPFLAGS}

main.o: vector3d.hpp particle.hpp
vector3d.o: vector3d.hpp
particle.o: particle.hpp

test_vector3d.o:vector3d.hpp
test_particle.o:vector3d.hpp particle.hpp

%.o: %.cpp
	g++ -c $< -o $@ ${CPPFLAGS}

clean:
	rm -rf main *.o ${TEST}
