CC = g++
FLAGS = -std=c++11

all: VarySize

VarySize: VarySize.cpp DataGenerator.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o

cleanest: clean
	rm VarySize