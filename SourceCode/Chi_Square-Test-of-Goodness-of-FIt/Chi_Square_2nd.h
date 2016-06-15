// Chi_Squared_2nd.h

#ifndef CHI_SQUARED_2ND_H
#define CHI_SQUARED_2ND_H

#include "../Quantiles/GK.h"
//#include "../Quantiles/ReservoirSampling.h"
//#include "../Quantiles/QDigestDouble.h"
//#include "../Quantiles/CMSQuantile.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h>

//FIGURE OUR MEMORY MANAGMENT

class ChiSquare2
{
public:
	ChiSquare2();
	ChiSquare2(double m); //m is the amount of memory
	ChiSquare2(double m,int q);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Count Min Sketch
	   q=4 Reservoir Sampling
	*/E
	~ChiSquare2();
  	
	void insertStreamOne(double val);
	void insertStreamTwo(double val);
	double calculate_statistic(int k,double (*f)(double));
	
private:
	double chi_squared;
	double memory;
	int N;
	int M;
	int K;
	int Q;
	
	QuantileSketch* quantile1;
	QuantileSketch* quantile2;
	
	
};

#include"Chi_Square_2nd.cpp"
#endif
