# Makefile for all the tests

all: BasicStats_test GK_test QDigest_test QDigest_test_Double Reservoir_test Chi_Square_test

VPATH = ../SourceCode/Quantiles:../SourceCode/BasicStats:../SourceCode/Chi_Square-Test-of-Goodness-of-FIt

BasicStats_test: BasicStats.h BasicStats.cpp BasicStats_test.cpp
	g++ -o BasicStats_test BasicStats_test.cpp

GK_test: QuantileSketch.h GK.h GK.cpp GK_test.cpp
	g++ -o GK_test GK_test.cpp

QDigest_test: QuantileSketch.h Q-Digest.h Q-Digest.cpp QDigest_test.cpp
	g++ -o QDigest_test QDigest_test.cpp

QDigest_test_Double: QuantileSketch.h Q-Digest.h Q-Digest.cpp QDigestDouble.h QDigest_test_Double.cpp
	g++ -o QDigest_test_Double QDigest_test_Double.cpp

Reservoir_test: QuantileSketch.h ReservoirSampling.h ReservoirSampling.cpp Reservoir_test.cpp
	g++ -o Reservoir_test Reservoir_test.cpp	

Chi_Square_test: Chi_Square_1st.h Chi_Square_1st.cpp Chi_Square_test.cpp
	g++ -o Chi_Square_test Chi_Square_test.cpp

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean: tidy
	rm -f *.o