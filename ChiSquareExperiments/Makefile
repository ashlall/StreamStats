CC = g++
FLAGS = -std=c++11

all: Data_test

Data_test: Data_test.cpp DataGenerator.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o

cleanest: clean
	rm Data_test