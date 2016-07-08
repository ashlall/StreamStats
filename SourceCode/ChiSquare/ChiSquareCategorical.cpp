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
	range=2^32;
	count= new int[num_buckets];
	std::fill_n(count,num_buckets,0); // run a for loop if this doesnt work 
	
	
}
/*
Pre-Condition:None.
Post-Condition: Deallocates any allocated memory.
*/
ChiSquareCategorical::~ChiSquareCategorical()
{	
	// deallocating the dynamically allocates array count. 
	delete []count; 	
}
/*
Pre-Condition: Data from category c, where c lies betweeen categories 0 throuh C.
Post-Condition: c is passed into the hash function and its bucket frequency
is then incremented.
*/
void ChiSquareCategorical::insert(double c)
{
	stream_size++;
	
	// Passing c into the hash function and increases the count of
	// whichever bucket it falls into. 
	HashTable HashA(71);
	/*int bucket= int((HashA.hash(c))%num_buckets);	
	count[bucket]++;*/
	
	long hash_value= HashA.hash(c);;
	if(hash_value<(percent*range))
	{	
		if(map.count(hash_value)<=1)
			map.emplace(hash_value,1);
		else
		{
			long cat_count=map.at(hash_value);
			map.at(hash_value)=cat_count++;
		}
	}
		
	
	
	
}
/*
Pre-Condition: distribution_2 the second stream of data which has used the 
same number of buckets and hash function.
Post-Condition: Returns the Chi-Squared statistic for the categorical data.
*/
double ChiSquareCategorical::calculate_statistic(const ChiSquareCategorical& second_distribution)
{	
	//Getting the size of both streams
	int stream_size_1=stream_size;
	int stream_size_2=second_distribution.stream_size;
	
	
	double constant_1 = sqrt((double)stream_size_2/stream_size_1);
	double constant_2 = sqrt((double)stream_size_1/stream_size_2);
	
	int df=map.size();
	
	for ( auto it = map.begin(); it != map.end(); ++it )
	{
		 // Getting the frequencies if the i'th bin from the two streams.
		 double frequency_1= 
		 double frequency_2= 
		 
		 if((frequency_1==0) && (frequency_2==0))
		 df--;
	 	else
	 	{
		 //Calculating the Chi-Squared Statistic
		 double value = frequency_1 * constant_1 - frequency_2 * constant_2;
		 chi_squared += (value * value) / (frequency_1 + frequency_2);
		}
	}
	
	return chi_squared;
}
