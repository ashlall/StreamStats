all: Q-Digest.o ReservoirSampling.o GK.o

CC = g++
FLAGS = -std=c++11

Q-Digest.o: Q-Digest.cpp Q-Digest.h QuantileSketch.h
	$(CC) $(FLAGS) -c $<

ReservoirSampling.o: ReservoirSampling.cpp QuantileSketch.h ReservoirSampling.h
	$(CC) $(FLAGS) -c $<

GK.o: GK.cpp GK.h QuantileSketch.h
	$(CC) $(FLAGS) -c $<
