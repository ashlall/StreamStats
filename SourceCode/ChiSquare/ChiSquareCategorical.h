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
	std::size_t hash(int x)
	{	
		 std::size_t h1 = std::hash<int>()(x);
		 std::size_t h2 = std::hash<int>()(x);
		 return h1 ^ (h2 << 1); // or use boost::hash_combine
		/*x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x);*/
	}
};

// Inserts Categorical data into a quantile sketch and computes the chi-squared statistic 
class ChiSquareCategorical
{
public:
	ChiSquareCategorical();
	ChiSquareCategorical(int buckets);
	~ChiSquareCategorical();
  	
	void insert(double val);
	double calculate_statistic(const ChiSquareCategorical& second_distribution,int &df);
	int get_stream_size(){ return stream_size;};
private:
	double chi_squared;
	int num_buckets;
	int *count;
	int stream_size;
	unordered_map<double,int> hash_table;
};

#endif
