CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare

all: VarySize

VarySize: VarySize.cpp DataGenerator.o ChiSquareContinuous.o
# Q-Digest.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

ChiSquareContinuous.o: ChiSquareContinuous.o
	$(CC)

clean:
	rm *.o

cleanest: clean
	rm VarySize
