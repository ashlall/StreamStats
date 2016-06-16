// Chi_Squared_2nd.h

#ifndef CHI_SQUARED_2ND_H
#define CHI_SQUARED_2ND_H

#include "../Quantiles/GK.h"
#include "../Quantiles/ReservoirSampling.h"
//#include "../Quantiles/QDigestDouble.h"
//#include "../Quantiles/CMSQuantile.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h>


class ChiSquare2
{
public:
	ChiSquare2();
	ChiSquare2(double m);
	ChiSquare2(double m,int q);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Count Min Sketch
	   q=4 Reservoir Sampling
	*/
	~ChiSquare2();
  	
	void insertStreamOne(double val);
	void insertStreamTwo(double val);
	double calculate_statistic(int k);
	
private:
	double chi_squared;
	double memory;
	double N;
	double M;
	int K;
	int Q;
	
	QuantileSketch* quantile1;
	QuantileSketch* quantile2;
	
	
};

#include"Chi_Square_2nd.cpp"
#endif
