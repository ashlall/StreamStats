# Makefile for all the tests

all: BasicStats_test GK_test QDigest_test QDigest_test_Double Reservoir_test Chi_Square_test

CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare:../SourceCode/BasicStats:../SourceCode/Quantiles

BasicStats_test: BasicStats_test.cpp BasicStats.o
	$(CC) -o $@ $<

GK_test: GK_test.cpp GK.o
	$(CC) $(FLAGS) -o $@ $<

QDigest_test: QDigest_test.cpp Q-Digest.o
	$(CC) $(FLAGS) -o $@ $<

QDigest_test_Double: QDigest_test_Double.cpp Q-Digest.o QDigestDouble.h
	$(CC) $(FLAGS) -o $@ $<

Reservoir_test: Reservoir_test.cpp ReservoirSampling.o
	$(CC) $(FLAGS) -o $@ $<

Chi_Square_test: Chi_Square_test.cpp ChiSquareContinuous.o Q-Digest.o
	$(CC) $(FLAGS) -o $@ $<
	
Chi_Square_Categorical: Chi_Square_Categorical_test.cpp ChiSquareCategorical.o
	$(CC) $(FLAGS) -o $@ $<
	
clean: 
	rm -f *.o

cleanest: clean
	rm BasicStats_test GK_test QDigest_test QDigest_test_Double Reservoir_test Chi_Square_test
