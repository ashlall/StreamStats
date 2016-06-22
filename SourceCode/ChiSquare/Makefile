all: ChiSquareContinuous.o

VPATH = ../Quantiles
CC = g++
FLAGS = -std=c++11

ChiSquareContinuous.o: ChiSquareContinuous.cpp ChiSquareContinuous.h ReservoirSampling.o Q-Digest.o QDigestDouble.h 
	$(CC) $(FLAGS) -c $<
