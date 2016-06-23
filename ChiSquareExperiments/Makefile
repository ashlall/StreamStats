CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare:../SourceCode/Quantiles

all: VarySize MakePlot

VarySize: VarySize.cpp DataGenerator.o ChiSquareContinuous.o
# Q-Digest.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

ChiSquareContinuous.o: ChiSquareContinuous.cpp ChiSquareContinuous.h ReservoirSampling.o GK.o Q-Digest.o QDigestDouble.h
	$(CC) $(FLAGS) -c $<

MakePlot: MakePlot.cpp
	$(CC) -o $@ $<

clean:
	rm *.o

cleanest: clean
	rm VarySize MakePlot
