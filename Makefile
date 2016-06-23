# Makefile for StreamStats
# TODO: add makefiles for rest of folders

all:
	cd SourceCode/Quantiles; make
	cd SourceCode/ChiSquare; make
	cd Test; make
	cd Example; make
	cd ChiSquareExperiments; make 
