//ChiSquareCategorical.h

#ifndef CHI_SQUARED_CATIGORICAL_H
#define CHI_SQUARED_CATIGORICAL_H

#include <iostream>
#include <stdlib.h> 
#include<math.h>

// Inserts continuous data into a quantile sketch and computes the chi-squared statistic 
class ChiSquareCatigorical
{
public:
	ChiSquareCatigorical();
	ChiSquareCatigorical(double m);
	~ChiSquareCatigorical();
  	
	void insert(double val);
	double calculate_statistic(const ChiSquareCategorical& second_distribution)
private:
	double chi_squared;

class IndexError {};
#endif

