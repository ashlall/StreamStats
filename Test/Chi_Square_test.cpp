// Unit tests for One-Sample Chi-square & Two sample Chi-square.

#include<cassert>
#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_1st.h"
#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_2nd.h"
#include <iostream>
#include<iomanip> 
#include <random>


using namespace std;


void test_chi_square_1st() //One-sample test
{

	ChiSquare b(3000,3); //ChiSquare b(memory, sketch method);
	int stream_size = 10000;
	double item;
	double chi;
	
	default_random_engine generator(5);
	normal_distribution<double> distribution(100,20);
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
  	c.insert(item);
    }

}
  	chi = b.calculate_statistic_ifNormal(100,100, 20);
  	cout << "chi: " << chi << endl;


/*
void Chi2TestOne() //Two-sample test
{
	ChiSquare2 c(500); 
	int stream_size = 10000;
	double item;
	double item2;
	long sizel;
	double chi;
	
	default_random_engine generator(5);
	normal_distribution<double> distribution(10000,200);
	//normal_distribution<double> distribution2(10000,200);
	
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
    	//item2=distribution2(generator);
    	cout<<item<<endl;
  	c.insertStreamOne(item);
  	c.insertStreamTwo(item);
    }
  	c.insertStreamTwo(item2);
   }
  	
  	chi = c.calculate_statistic(100);
  	cout << "chi: " << chi << endl;
	

}*/

int main()
{
	test_chi_square_1st();
	//Chi2TestOne();
	//Chi2TestTwo();
	return 0;
}