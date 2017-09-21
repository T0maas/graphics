all: main

main: main.o graphics.o
	g++ main.o graphics.o -o main

main.o: main.cc graphics.h
	g++ -c main.cc

graphics.o: graphics.cc graphics.h
	g++ -c graphics.cc -std=c++11
