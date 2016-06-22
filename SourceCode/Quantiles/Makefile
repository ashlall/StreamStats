all: Q-Digest.o ReservoirSampling.o

CC = g++
FLAGS = -std=c++11

Q-Digest.o: Q-Digest.cpp Q-Digest.h QuantileSketch.h
	$(CC) $(FLAGS) -c $<

ReservoirSampling.o: ReservoirSampling.cpp QuantileSketch.h ReservoirSampling.h
	$(CC) -c $<