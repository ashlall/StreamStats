# Makefile for all the tests

all: BasicStats_test GK_test QDigest_test QDigest_test_Double Reservoir_test Chi_Square_test

VPATH = ../SourceCode/Quantiles:../SourceCode/BasicStats:../SourceCode/ChiSquare

BasicStats_test: BasicStats.o BasicStats_test.cpp
	g++ -o BasicStats_test BasicStats_test.cpp

GK_test: QuantileSketch.h GK.h GK.cpp GK_test.cpp
	g++ -o GK_test GK_test.cpp

QDigest_test: Q-Digest.o QDigest_test.cpp
	g++ -o QDigest_test QDigest_test.cpp

QDigest_test_Double: QDigestDouble.h Q-Digest.o QDigest_test_Double.cpp
	g++ -o QDigest_test_Double QDigest_test_Double.cpp

Reservoir_test: ReservoirSampling.o Reservoir_test.cpp
	g++ -o Reservoir_test Reservoir_test.cpp	

Chi_Square_test: ChiSquareContinuous.o ReservoirSampling.o Chi_Square_test.cpp
	g++ -o Chi_Square_test Chi_Square_test.cpp

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean: tidy
	rm -f *.o