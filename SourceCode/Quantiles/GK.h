//GK.h

#ifndef GK_H
#define GK_H

#include "QuantileSketch.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
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
	int find_index(double val);
	void insert_tuple(Tuple* t,int index);
	void delete_merge();
	void delete_tuple(int index);
	int max;
	Tuple** summary;
	int num_tuples;
	long num_observations;
	long stream_size;	
};

#include "GK.cpp"
#endif 

