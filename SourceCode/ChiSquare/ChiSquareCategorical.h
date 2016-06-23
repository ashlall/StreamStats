//ChiSquareCategorical.h

#ifndef CHI_SQUARED_CATIGORICAL_H
#define CHI_SQUARED_CATIGORICAL_H
#include <algorithm> 
#include <iostream>
#include <string>
#include <unordered_map>
#include <stdlib.h> 
#include<math.h>
using namespace std;

// Inserts categorical data into a quantile sketch and computes the chi-squared statistic 
class ChiSquareCatigorical
{
public:
	ChiSquareCatigorical();
	ChiSquareCatigorical(double m);
	~ChiSquareCatigorical();
  	
	void insert(double val);
	double calculate_statistic(const ChiSquareCategorical& second_distribution)
	int get_stream_size(){ return stream_size;};
private:
	double chi_squared;
	int num_buckets;
	int *count;
	int stream_size;
	unordered_map<double,double> hash_table;

class IndexError {};
#endif

