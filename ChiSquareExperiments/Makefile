CC = g++
FLAGS = -std=c++11
VPATH = ../SourceCode/ChiSquare:../SourceCode/Quantiles

all: VarySizeOneSample MakePlot VarySizeTwoSampleConstant VarySizeTwoSampleBoth VaryBinsOneSample VaryBinsTwoSample VaryMemoryOneSample VaryMemoryTwoSample VaryMemoryReal VaryMemoryCategorical

VaryMemoryCategorical: VaryMemoryCategorical.cpp ChiSquareContinuous.o Chi_Square_Distribution.cpp
	$(CC) $(FLAGS) -o $@ $<

VaryMemoryReal: VaryMemoryReal.cpp ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VaryMemoryTwoSample: VaryMemoryTwoSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VaryMemoryOneSample: VaryMemoryOneSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VaryBinsTwoSample: VaryBinsTwoSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VaryBinsOneSample: VaryBinsOneSample.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VarySizeTwoSampleBoth: VarySizeTwoSampleBoth.cpp DataGenerator.o ChiSquareContinuous.o
	$(CC) $(FLAGS) -o $@ $<

VarySizeTwoSampleConstant: VarySizeTwoSampleConstant.cpp DataGenerator.o ChiSquareContinuous.o
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
	rm VarySizeOneSample MakePlot VarySizeTwoSampleConstant VarySizeTwoSampleBoth VaryBinsOneSample VaryBinsTwoSample VaryMemoryOneSample VaryMemoryTwoSample VaryMemoryReal VaryMemoryCategorical
