//ChiSquareCategorical.cpp

#include "ChiSquareCategorical.h"

/*

*/
ChiSquareCatigorical::ChiSquareCatigorical()
{
	chi_squared=0;
	num_bins=50;
	count= new int[num_bins];
	std::fill_n(count,num_bins,0); // run a for loop if this doesnt work
	
}

/*


*/
void ChiSquareCatigorical::insert( double c)
{
	
	
	
}

/*

*/
double ChiSquareCatigorical::calculate_statistic(const ChiSquareCategorical& second_distribution)
{
	
	
}

