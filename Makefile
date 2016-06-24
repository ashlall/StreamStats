# Makefile for StreamStats
# TODO: add makefiles for rest of folders

all:
	cd SourceCode; make
	cd Test; make
	cd Example; make
	cd ChiSquareExperiments; make 

