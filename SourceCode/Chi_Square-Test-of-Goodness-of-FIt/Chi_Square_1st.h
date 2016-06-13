// Chi_Squared_1st.h

#ifndef CHI_SQUARED_1ST_H
#define CHI_SQUARED_1ST_H

#include "../Quantiles/GK.h"
//#include "../Quantiles/ReservoirSampling.h"
//#include "../Quantiles/QDigestDouble.h"
//#include "../Quantiles/CMSQuantile.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h>


class ChiSquare
{
public:
	ChiSquare();
	ChiSquare(double m); //m is the amount of memory
	ChiSquare(double m,int q);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Count Min Sketch
	   q=4 Reservoir Sampling
	*/
	
	~ChiSquare();
	void insert(double val);
	double calculate_statistic(int k);
	double calculate_statistic(int k,double (*f)(double));
	  
	
private:
	double chi_squared;
	double memory;
	int N;
	int K;
	int Q;
	
	GK* quantile_GK;
	//QDigestDouble* quantile_QD;
	//ReservoirSampling* quantile_RS;
	//CMS* quantile_CMS;
	
	double inverse_cmf(double x);
	double RationalApproximation(double t);
	double NormalCDFInverse(double p);
	
};

#include"Chi_Square_1st.cpp"
#endif
