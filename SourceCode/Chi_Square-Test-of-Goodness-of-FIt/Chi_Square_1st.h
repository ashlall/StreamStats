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
	ChiSquare(int n,int k,double m); //m is the percent of memory
	ChiSquare(int q,int n,int k,double m);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Count Min Sketch
	   q=4 Reservoir Sampling
	*/
	
	~ChiSquare();
	void insert(double val);
	double calculate_statistic();
	  
	
private:
	double chi_squared;
	double memory;
	int N;
	int K;
	int Q;
	
	GK* quantile_GK;
	//QDigestDouble* quantile_QD;
	ReservoirSampling* quantile_RS;
	//CMS* quantile_CMS;
	
	double inverse_cmf(double x);
	
	
};

#include"Chi_Square_1st.cpp"
#endif
