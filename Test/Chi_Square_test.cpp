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
	ChiSquare b(100000); //ChiSquare b(memory, sketch method);
	int stream_size = 10000000;
	double item;
	double chi;
	int k=50;
	double N=0;
	double *items=new double[stream_size];
	default_random_engine generator(5);
	normal_distribution<double> distribution(10000,2000);
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
    	N++;
    	items[i]=item;
  	b.insert(item);
    }
    chi = b.calculate_statistic_ifNormal(k,10000,2000);
    
    
    double *Upper=b.GetUpper();
    double *Lower=b.GetLower();
    double E=N/k;
    double chiActual=0;
    for (int i=1;i<=k;i++)
    {		
    	    double O=0;
    	    for(int j=0;j<stream_size;j++)
    	    {
    	    	    if(( items[j]<=Upper[i]) && (items[j]>=Lower[i]))
    	    	    O++;
    	    }
    	    double lambda= fabs(O-E);
    	    chiActual=chiActual+((lambda*lambda)/E);
    	    
    }
    cout<<chiActual<<" actual"<<endl;
  	cout << "chi: " << chi << endl;
  	delete items;
}


/*
void test_chi_square_2nd() //Two-sample test
{
	ChiSquare2 c(100); 
	int stream_size = 1000;
	double item;
	double item2;
	long sizel;
	double chi;
	
	default_random_engine generator;
	normal_distribution<double> distribution(10000,200);
	//normal_distribution<double> distribution2(10000,200);
	
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
  	c.insertStreamOne(item);
  	c.insertStreamTwo(item);
   }
  	
  	chi = c.calculate_statistic(50);
  	cout << "chi: " << chi << endl;
	

}
*/

int main()
{
	test_chi_square_1st();
	//test_chi_square_2nd();
	return 0;
}