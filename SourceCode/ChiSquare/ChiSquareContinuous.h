// Chi_Squared_1st.h

#ifndef CHI_SQUARED_1ST_H
#define CHI_SQUARED_1ST_H

#include "../Quantiles/GK.h"
#include "../Quantiles/ReservoirSampling.h"
//#include "../Quantiles/QDigestDouble.h"
//#include "../Quantiles/CMSQuantile.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h>


class ChiSquare
{
public:
	ChiSquare();
	ChiSquare(double m,int q=1);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Count Min Sketch
	   q=4 Reservoir Sampling
	*/
	
	~ChiSquare();
  	
	void insert(double val);
	double calculate_statistic_ifNormal(int k, double mean, double SD);
	double calculate_statistic(int k,double (*f)(double));
	double NormalCDFInverse_pub(double p, double mean, double SD);
	double* GetUpper();
	double* GetLower();
	
private:
	double chi_squared;
	double memory;
	double *UpperBins;
	double *LowerBins;
	int N;
	double K;
	int Q;
	
	QuantileSketch* quantile;
	
	double RationalApproximation(double t);
	double NormalCDFInverse(double p, double mean, double SD);
	
};

#include"Chi_Square_One_Sample.cpp"
#endif
