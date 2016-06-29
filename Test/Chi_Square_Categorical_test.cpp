//Chi_Square_Categorical.cpp
#include <iostream>
#include <random>
#include<cassert>
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>

#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
#include "../SourceCode/ChiSquare/Chi_Square_Distribution.cpp"
using namespace std;
void categorical_test1()
{
	ChiSquareCategorical c1(500);
	ChiSquareCategorical c2(500);
	ChiSquareCategorical c3(100);
	ChiSquareCategorical c4(100);
	ChiSquareCategorical c5(50);
	ChiSquareCategorical c6(50);
	
	for(int j=0;j<100;j++)
	{ 
		for(int i=0;i<100000;i++)
		{
			c1.insert(i);
			c3.insert(i);
			c5.insert(i);
		}
		for(int i=99999;i>=0;i--)
		{
			c2.insert(i);
			c4.insert(i);
			c6.insert(i);
		}
	}
	assert(c1.calculate_statistic(c2)==0);
	assert(c3.calculate_statistic(c4)==0);
	assert(c5.calculate_statistic(c6)==0);
}

void categorical_test2()
{
	ChiSquareCategorical c1(500);
	ChiSquareCategorical c2(500);
	ChiSquareCategorical c3(100);
	ChiSquareCategorical c4(100);
	ChiSquareCategorical c5(50);
	ChiSquareCategorical c6(50);
	
	default_random_engine generator(5);
	normal_distribution<double> distribution(10000,1000);
	
	for(int i=0; i<1000000;i++)
	{
		double data=distribution(generator);
		c1.insert(data);
		c2.insert(data);
		
		c3.insert(data);
		c4.insert(data);
		
		c5.insert(data);  
		c6.insert(data);
		
		
	}
	assert(c1.calculate_statistic(c2)==0);
	assert(c3.calculate_statistic(c4)==0);
	assert(c5.calculate_statistic(c6)==0);  
}

void categorical_test3()
{
	ChiSquareCategorical c1(1000);
	ChiSquareCategorical c2(1000);
	double actual_chi=0;
	int count_1[100000];int count_2[100000];
	std::fill_n(count_1,100000,0);
	std::fill_n(count_2,100000,0);
	
	for(int i=0;i<=10000000;i++)
	{
		int v1= (int)(rand() % 100001);
		int v2=	(int)(rand() % 100001);
		count_1[v1]++;
		count_2[v2]++;
		c1.insert(v1);
		c2.insert(v2);
	}
	double stream_size1=10000000;
	double stream_size2=10000000;
	double constant_1 = sqrt((double)stream_size2/stream_size1);
 	double constant_2 = sqrt((double)stream_size1/stream_size2);
 	for(int i=0;i<100000;i++)
	{
		double frequency_1=count_1[i];
		double frequency_2=count_2[i];
		double value = frequency_1 * constant_1 - frequency_2 * constant_2;
		actual_chi += (value * value) / (frequency_1 + frequency_2);
	}
	cout<<pchisq(actual_chi,100000-1)<<endl;
	cout<<pchisq(c1.calculate_statistic(c2),1000-1)<<endl;
	
}
void categorical_test4()
{
	ChiSquareCategorical c1(20);
	ChiSquareCategorical c2(20);
	double actual_chi=0;
	int N=0;
	int M=0;
	int count_1[200];int count_2[200];
	std::fill_n(count_1,200,0);
	std::fill_n(count_2,200,0);
	double stream_size1=0;
	double stream_size2=0;
	for(int i=0;i<200;i++)
	{
		int v1= (int)(rand() % 10 +90 );
		int v2= (int)(rand() % 10 +90 );
		count_1[i]=v1;
		count_2[i]=v2;
		for(int j=0;j<v1;j++)
			c1.insert(i);
		
		for(int k=0;k<v2;k++)
			c2.insert(i);
		
		stream_size1=stream_size1+v1;
		stream_size2=stream_size2+v2;
	}
	double constant_1 = sqrt((double)stream_size2/stream_size1);
 	double constant_2 = sqrt((double)stream_size1/stream_size2);
 	
	
	for(int i=0;i<200;i++)
	{
		double frequency_1=count_1[i];
		double frequency_2=count_2[i];
		double value = frequency_1 * constant_1 - frequency_2 * constant_2;
		actual_chi += (value * value) / (frequency_1 + frequency_2);
	}
	cout<<actual_chi<<endl;
	double chi=c1.calculate_statistic(c2);
	cout<<chi<<endl;
	
	//cout<<pchisq(actual_chi,200-1)<<endl;
	cout<<1-pchisq(9900,10000)<<endl;
	
}


int main()  
{	
	//categorical_test1(); // When the streams are identical       
	//categorical_test2(); // When the steams are identical       
	//categorical_test3(); // When the two streams are different from one another.  
	categorical_test4();
	 
	return 0;		
}
