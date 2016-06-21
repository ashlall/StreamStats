all: QDigest.o  ReservoirSampling.o

QDigest.o: Q-Digest.cpp Q-Digest.h QuantileSketch.h
	g++ -std=c++11 -c Q-Digest.cpp

QDigestDouble.o: QDigest.o QDigestDouble.h
	g++ -std=c++11 -c QDigestDouble.h

ReservoirSampling.o: QuantileSketch.h ReservoirSampling.h ReservoirSampling.cpp
	g++ -c ReservoirSampling.cpp