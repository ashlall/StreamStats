CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare:../SourceCode/Quantiles

all: VarySizeOneSample MakePlot

VarySizeOneSample: VarySizeOneSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

MakePlot: MakePlot.cpp
	$(CC) -o $@ $<

clean:
	rm *.o

cleanest: clean
	rm VarySize MakePlot
