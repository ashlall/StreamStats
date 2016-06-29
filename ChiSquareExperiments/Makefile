CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare:../SourceCode/Quantiles

all: VarySizeOneSample MakePlot test VarySizeTwoSample

VarySizeTwoSample: VarySizeTwoSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

test: test.cpp ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VarySizeOneSample: VarySizeOneSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	$(CC) $(FLAGS) -c $<

MakePlot: MakePlot.cpp
	$(CC) -o $@ $<

clean:
	rm *.o

cleanest: clean
	rm VarySizeOneSample MakePlot test VarySizeTwoSample
