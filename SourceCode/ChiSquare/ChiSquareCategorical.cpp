//ChiSquareCategorical.cpp

#include "ChiSquareCategorical.h"

/*
Pre-Condition:
Post-Condition:
*/
ChiSquareCatigorical::ChiSquareCatigorical()
{
	chi_squared=0;
	num_bins=50;
	stream_size=0;
	count= new int[num_bins];
	std::fill_n(count,num_bins,0); // run a for loop if this doesnt work
	
}
/*
Pre-Condition:
Post-Condition:
*/
ChiSquareCatigorical::~ChiSquareCatigorical()
{
	delete []count; 	
}

/*
Pre-Condition:
Post-Condition:
*/
void ChiSquareCatigorical::insert(double c)
{
	
	int bin= hash_table[c];
	count[bin]++;
	
}
/*
Pre-Condition:
Post-Condition:
*/
double ChiSquareCatigorical::calculate_statistic(const ChiSquareCategorical& second_distribution)
{
	
	
	
}
