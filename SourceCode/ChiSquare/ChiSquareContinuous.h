// Chi_Squared_1st.h
// Inserts a stream of data into a quantile-epsilon sketch chosen by the user and calculates the Chi-Squared statistic related to the normal distribution, a given distribution, or another stream of data

#ifndef CHI_SQUARED_CONTINUOUS_H
#define CHI_SQUARED_CONTINUOUS_H

#include "../Quantiles/GK.cpp"
#include "../Quantiles/ReservoirSampling.cpp"
#include "../Quantiles/QDigestDouble.h"
#include "Chi_Square_Distribution.cpp" // Used for calculating the p-value by given DF and chi-square statistic
#include <iostream>
#include <stdlib.h> 
#include<math.h>
#include<iomanip> // Parametric manipulators. Used to set precision. 

// Inserts continuous data into a quantile sketch and computes the chi-squared statistic 
class ChiSquareContinuous
{
public:
	ChiSquareContinuous();
	ChiSquareContinuous(double m,int q=1);
	/* q=1: GreenWaldKhanna Sketch
	   q=2: Q-Digest Sketch
	   q=3: Reservoir Sampling
	*/	
	~ChiSquareContinuous();
  	
	void insert(double val);
	
	double calculate_statistic_ifNormal(int num_buckets, double mean, double SD);
	double calculate_pvalue_ifNormal(int num_buckets, double mean, double SD);
	bool   final_decision_ifNormal(int num_buckets, double mean, double SD, double sig_level);
	
	double calculate_statistic_ifUniform(int num_buckets, double a, double b);
	double calculate_pvalue_ifUniform(int num_buckets, double a, double b);
	bool   final_decision_ifUniform(int num_buckets, double a, double b, double sig_level);

	double calculate_statistic_ifPareto(int num_buckets, double location, double scale);
	double calculate_pvalue_ifPareto(int num_buckets, double location, double scale);
	bool   final_decision_ifPareto(int num_buckets, double location, double scale, double sig_level);

	double calculate_statistic_ifExponential(int num_buckets, double location, double scale);
	double calculate_pvalue_ifExponential(int num_buckets, double location, double scale);
	bool   final_decision_ifExponential(int num_buckets, double location, double scale, double sig_level);

	double calculate_statistic(int num_buckets, double (ChiSquareContinuous::*distribution)(double, double, double), double location, double scale);
	double two_sample_statistic(const ChiSquareContinuous& second_distribution, int num_buckets);
	double* get_upper();
	double* get_lower();
	
private:
	double chi_squared;
	double memory;
	double *upper_bins;
	double *lower_bins;
	
	QuantileSketch* quantile_sketch;
	
	double rational_approximation(double t);
	double normal_cdf_inverse(double p, double mean, double SD);	
	double uniform_cdf_inverse(double percent, double a, double b);
	double pareto_cdf_inverse(double percent, double location,double scale);
	double exponential_cdf_inverse(double percent, double location, double scale);
};

class IndexError {};

#endif
