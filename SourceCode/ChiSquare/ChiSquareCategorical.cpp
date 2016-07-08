//ChiSquareCategorical.cpp
#include"ChiSquareCategorical.h"
/*
Pre-Condition: None.
Post-Condition:Initializes the variables used in the ChiSquareCategorical class.
*/
ChiSquareCategorical::ChiSquareCategorical(double p)
{
	chi_squared=0;
	stream_size=0;
	percent =p;
	range=pow(2,32);	
}
/*
Pre-Condition: Data from category c, where c lies betweeen categories 0 throuh C.
Post-Condition: c is passed into the hash function and its bucket frequency
is then incremented.
*/
void ChiSquareCategorical::insert(double c)
{
	stream_size++;
	HashTable HashA(71);
	
	long hash_value= HashA.hash(c);
	if(hash_value<((percent/100)*range))
	{	
		if(map.count(hash_value)<1)
		{	
			map.emplace(hash_value,1);
		}
		else
		{
			long cat_count=map.at(hash_value);
			cat_count++;
			map.at(hash_value)=cat_count;
		}
	}
	
}
/*
Pre-Condition: distribution_2 the second stream of data which has used the 
same number of buckets and hash function.
Post-Condition: Returns the Chi-Squared statistic for the categorical data.
*/
double ChiSquareCategorical::calculate_statistic(const ChiSquareCategorical& second_distribution,int &df)
{	
	//Getting the size of both streams
	int stream_size_1=stream_size;
	int stream_size_2=second_distribution.stream_size;
	
	
	double constant_1 = sqrt((double)stream_size_2/stream_size_1);
	double constant_2 = sqrt((double)stream_size_1/stream_size_2);
	df=map.size();
	for ( auto it = map.begin(); it != map.end(); ++it )
	{
		 // Getting the frequencies if the i'th bin from the two streams.
		 double frequency_1= it->second;
		 double frequency_2= second_distribution.map.at(it->first);
	 	
		 //Calculating the Chi-Squared Statistic
		 double value = frequency_1 * constant_1 - frequency_2 * constant_2;
		 chi_squared += (value * value) / (frequency_1 + frequency_2);
	}
	
	return chi_squared;
}
