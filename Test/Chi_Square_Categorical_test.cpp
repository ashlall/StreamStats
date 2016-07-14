//Chi_Square_Categorical.cpp

#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
#include "../SourceCode/ChiSquare/Chi_Square_Distribution.cpp"

#include <iostream>
#include <random>
#include<cassert>
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>

 
using namespace std;
/*
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
	double num_bins=50000;
	double num_cat=500000;
	
	double stream_size1=10000000;
	double stream_size2=10000000;
	
	ChiSquareCategorical c1(num_bins);
	ChiSquareCategorical c2(num_bins);
	double actual_chi=0;
	int count_1[(int)num_cat];int count_2[(int)num_cat];
	std::fill_n(count_1,num_cat,0);
	std::fill_n(count_2,num_cat,0);
	
	//srand(30);
	
	for(int i=0;i<stream_size1;i++)
	{
		int v1= (int)(rand() % (int)num_cat);
		int v2=	(int)(rand() % (int)num_cat);
		count_1[v1]++;
		count_2[v2]++;
		c1.insert(v1);
		c2.insert(v2);
	}
		
	double constant_1 = sqrt((double)stream_size2/stream_size1);
 	double constant_2 = sqrt((double)stream_size1/stream_size2);
 	for(int i=0;i<num_cat;i++)
	{
		double frequency_1=count_1[i];
		double frequency_2=count_2[i];
		double value = frequency_1 * constant_1 - frequency_2 * constant_2;
		actual_chi += (value * value) / (frequency_1 + frequency_2);
	}
	double chi= c1.calculate_statistic(c2);
	cout<<actual_chi<<endl;
	cout<<chi<<endl;
	cout<<pochisq(actual_chi,num_cat-1)<<endl;
	cout<<pochisq(chi,num_bins-1)<<endl;
	
}*/
void categorical_test4()
{	int seed=0;
	double memory_percent=20;	
	for(int js=0;js<20;js++)
	{
		double num_cat=1000000;
		int df1=num_cat;
		int df2=0;
		int N,M;
		double actual_chi;
		ChiSquareCategorical c1(memory_percent);
		ChiSquareCategorical c2(memory_percent);
		
		double p_value=0;
		int max_dif;
		int count_1[(int)num_cat];int count_2[(int)num_cat];
			
		actual_chi=0;
		N=0;
		M=0;
		std::fill_n(count_1,num_cat,0);
		std::fill_n(count_2,num_cat,0);
		double stream_size1=0; 
		double stream_size2=0; 
		srand(seed);
			
		for(int i=0;i<num_cat;i++)
		{
			int v1= (int)(rand() % 250+50); // See between %35-40 with +100
			max_dif= 28;// see with 28
			int v2= v1-max_dif+rand()%(2*max_dif+1);
				
			count_1[i]=v1;
			count_2[i]=v2;
				
			stream_size1=stream_size1+v1;
			stream_size2=stream_size2+v2;
		}
		double constant_1 = sqrt((double)stream_size2/stream_size1);
		double constant_2 = sqrt((double)stream_size1/stream_size2);
			
			
		for(int i=0;i<num_cat;i++)
		{
			double frequency_1=count_1[i];
			double frequency_2=count_2[i];
			double value = frequency_1 * constant_1 - frequency_2 * constant_2;
			actual_chi += (value * value) / (frequency_1 + frequency_2);
		}
			
		p_value=1-pochisq(actual_chi,df1--);
		seed=seed+1;
			
		for(int i=0;i<num_cat;i++)
		{
			for(int j=0;j<count_1[i];j++)
				c1.insert(i);
				
			for(int k=0;k<count_2[i];k++)
				c2.insert(i);
		}
		double chi=c1.calculate_statistic(c2,df2);
		cout<<"Actual: "<<p_value<<endl;
		cout<<"Calculated: "<<1-pochisq(chi,df2--)<<endl;
	}
}

void categorical_test5()
{
		
	ChiSquareCategorical c1(10);
	ChiSquareCategorical c2(10);
	int num_cat=10000;
	int df=0;
	for(int i=0;i<num_cat;i++)
	{
		int v1= (int)(rand() % 250+50);
		int max_dif= 28;
		int v2= v1-max_dif+rand()%(2*max_dif+1);
	
		for(int j=0;j<v1;j++)
			c1.insert(i);
				
		for(int k=0;k<v2;k++)
			c2.insert(i);
	}
	
	
	double chi=c1.calculate_statistic(c2,df);
	cout<<chi<<endl;
	cout<<1-pochisq(chi,df--);
	
}


int main()  
{	
	//categorical_test1(); // When the streams are identical       
	//categorical_test2(); // When the steams are identical       
	//categorical_test3(); // When the two streams are different from one another.  
	categorical_test4();
	//categorical_test5();
	
	 
	return 0;		
}
