all: ChiSquareContinuous.o ChiSquareCategorical.o

VPATH = ../Quantiles
CC = g++
FLAGS = -std=c++11

ChiSquareContinuous.o: ChiSquareContinuous.cpp ChiSquareContinuous.h ReservoirSampling.o  QDigestDouble.h GK.o Q-Digest.o
	$(CC) $(FLAGS) -c $<
	
ChiSquareCategorical.o: ChiSquareCategorical.cpp ChiSquareCategorical.h
	$(CC) $(FLAGS) -c $<
