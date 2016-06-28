//Chi_Square_Categorical.cpp
#include <iostream>
#include <random>
#include<cassert>

#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
using namespace std;
void categorical_test1()
{
	ChiSquareCategorical c1(100);
	ChiSquareCategorical c2(100);
	for(int j=0;j<10;j++)
	{ 
	for(int i=0;i<100000;i++)
	{
		c1.insert(i);
	}
	for(int i=99999;i>=0;i--)
	{
		c2.insert(i);
	}
	
	}
	assert(c1.calculate_statistic(c2)==0);
}

void categorical_test2()
{
	ChiSquareCategorical c1(100);
	ChiSquareCategorical c2(100);
	
	default_random_engine generator(5);
	normal_distribution<double> distribution(10000,1000);
	
	for(int i=0; i<1000000;i++)
	{
		double data=distribution(generator);
		c1.insert(i);
		c2.insert(i);
		
	}
	assert(c1.calculate_statistic(c2)==0);
}


int main()
{	
	categorical_test1();
	categorical_test2();
	return 0;		
}
