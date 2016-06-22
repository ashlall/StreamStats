CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare

all: VarySize

VarySize: VarySize.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o

cleanest: clean
	rm VarySize