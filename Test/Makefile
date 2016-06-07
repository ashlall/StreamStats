# Makefile for all the tests

all: BasicStats_test GK_test QDigest_test Reservoir_test

VPATH = ../SourceCode/Quantiles:../SourceCode/BasicStats

BasicStats_test: BasicStats.h BasicStats.cpp BasicStats_test.cpp
	g++ -o BasicStats_test BasicStats_test.cpp

GK_test: QuantileSketch.h GK.h GK.cpp GK_test.cpp
	g++ -o GK_test GK_test.cpp

QDigest_test: QuantileSketch.h Q-Digest.h Q-Digest.cpp QDigest_test.cpp
	g++ -o QDigest_test QDigest_test.cpp

Reservoir_test: QuantileSketch.h ReservoirSampling.h ReservoirSampling.cpp Reservoir_test.cpp
	g++ -o Reservoir_test Reservoir_test.cpp

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean: tidy
	rm -f *.o