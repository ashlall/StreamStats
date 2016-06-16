// Unit tests for One-Sample Chi-square & Two sample Chi-square.

#include<cassert>
#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_1st.h"
#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_2nd.h"
#include <iostream>
#include<iomanip> 
#include <random>

using namespace std;

void test_NormalCDFInverse()
{
    /*
	Test function NormalCDFInverse_pub(double p, double mean, double SD); PASSED
	
    double p[] =	// used for testing the accuracy of the function NormalCDFInverse_pub();
    {
        0.0000001,
        0.00001,
        0.001,
        0.05,
        0.15,
        0.25,
        0.35,
        0.45,
        0.55,
        0.65,
        0.75,
        0.85,
        0.95,
        0.999,
        0.99999,
        0.9999999
    };
    
    double exact[] = // used for testing the accuracy of the function NormalCDFInverse_pub();
    {
        -5.199337582187471,
        -4.264890793922602,
        -3.090232306167813,
        -1.6448536269514729,
        -1.0364333894937896,
        -0.6744897501960817,
        -0.38532046640756773,
        -0.12566134685507402,
        0.12566134685507402,
        0.38532046640756773,
        0.6744897501960817,
        1.0364333894937896,
        1.6448536269514729,
        3.090232306167813,
        4.264890793922602,
        5.199337582187471
    };

	ChiSquare a(3000);
	bool condA;
	double accurate, estimate;
	
	for (int i = 0; i <=15; i++)
	{
		for (int mean = 0; mean <= 5000; mean = mean + 5)
		{
			for (int SD = 1; SD <= 100; SD++)
			{
				cout << setprecision(3);
				accurate = exact[i]*SD+mean;
				estimate = a.NormalCDFInverse_pub(p[i], mean, SD);
				//cout << "accurate: " << accurate <<" estimate: " << estimate <<endl; 
				condA = ((estimate<= accurate+0.05) && (estimate >= accurate - 0.05));
  	  			assert(condA==true);
			}	
		}
	}
	
 */
 }
 
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
  	delete []items;
}


/*
void test_chi_square_2nd() //Two-sampwle test
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
	//test_NormalCDFInverse();
	return 0;
}