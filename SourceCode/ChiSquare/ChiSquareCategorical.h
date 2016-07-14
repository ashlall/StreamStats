//ChiSquareCategorical.h

#ifndef CHI_SQUARED_CATEGORICAL_H
#define CHI_SQUARED_CATEGORICAL_H

#include <algorithm> 
#include <iostream>
#include <string>
#include <unordered_map>
#include <stdlib.h> 
#include <unordered_set>
#include <cstddef>
#include <functional>
#include<stdio.h>
#include<math.h>
using namespace std;

class HashTable
{
public:
	int rand_num;
	HashTable();
	HashTable(int n)
	{
		rand_num=n;
	}
	uint32_t hash(uint32_t a)
	{	
		a = (a+0x479ab41d) + (a<<8); //http://burtleburtle.net/bob/hash/integer.html
		a = (a^0xe4aa10ce) ^ (a>>5);
		a = (a+0x9942f0a6) - (a<<14);
		a = (a^0x5aedd67d) ^ (a>>3);
		a = (a+0x17bea992) + (a<<7);
		return a;

	}
		
		
		 
	/*{	a = (a+0x7ed55d16) + (a<<12);
		a = (a^0xc761c23c) ^ (a>>19);
		a = (a+0x165667b1) + (a<<5);
		a = (a+0xd3a2646c) ^ (a<<9);
		a = (a+0xfd7046c5) + (a<<3);
		a = (a^0xb55a4f09) ^ (a>>16);
		return a;
	}
		
	{	int h1 = std::hash<int>()(x);
		 int h2 = std::hash<int>()(x);
		 return h1 ^ (h2 << 1);
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		 x = ((x >> 16) ^ x) * 0x45d9f3b;
		 x = ((x >> 16) ^ x);
		 return x;
	}*/
};

// Inserts Categorical data into a quantile sketch and computes the chi-squared statistic 
class ChiSquareCategorical
{
public:
	ChiSquareCategorical();
	ChiSquareCategorical(double p);
  	
	void insert(double val);
	double calculate_statistic(const ChiSquareCategorical& second_distribution, int seed = 0);
	int get_stream_size(){ return stream_size;};
private:
	double chi_squared;
	int num_buckets;
	double percent;
	int *count;
	int stream_size;
	long range=0;
	unordered_map<long,int> map;
};

#endif
