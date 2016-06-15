//GK.h

#ifndef GK_H
#define GK_H

#include "QuantileSketch.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<array>
#include <climits>
#include <math.h> 

class Tuple
{
public:
	double v;
	double g;
	double delta;
	Tuple();
	Tuple(double v_,double g_, double delta_)
	{
		v=v_;
		g=g_;
		delta=delta_;
		
	}
	Tuple(double v_)
	{
		v=v_;
		g=1;
		delta=0;
	}
};

	
class GK: public QuantileSketch
{
public:
	GK(int maxTuples);
	~GK();
	void insert(double val);
	double getQuantile(double quant);
	long get_stream_size(){return stream_size;};

private:
	int findIndex(double val);
	void insertTuple(Tuple* t,int index);
	void deleteMerge();
	void deleteTuple(int index);
	int max;
	Tuple** summary;
	int numTuples;
	long numObservations;
	long stream_size;	
};

#include "GK.cpp"
#endif 

