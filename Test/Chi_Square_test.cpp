// Unit tests for One-Sample Chi-square & Two sample Chi-square.

#include<cassert>
//./cs.o#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_1st.h"
#include "../SourceCode/Chi_Square-Test-of-Goodness-of-FIt/Chi_Square_2nd.h"
#include <iostream>
#include<iomanip> 
#include <random>


using namespace std;
/*
void test_chi_square_1st() //One-sample test
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
	

	
	
	/*
	Test function calculate_statistic_ifNormal(number of bins, double mean, double SD);
	*/
	ChiSquare b(3000,3); //ChiSquare b(memory, sketch method);

	int stream_size = 10000;
	double item;
	double chi;
	
	default_random_engine generator;
    normal_distribution<double> distribution(88888,20);
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
    	//item = rand() % 100000 + 33333;
    	//cout << item << endl;
  	    b.insert(item);
  	}
  	
  	chi = b.calculate_statistic_ifNormal(100, 88888, 20);
  	cout << "chi: " << chi << endl;
}

*/

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
	normal_distribution<double> distribution2(10000,200);
	
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
    	item2=distribution2(generator);
    	
  	c.insertStreamOne(item);
  	c.insertStreamTwo(item2);
  }
  	
  	chi = c.calculate_statistic(50);
  	cout << "chi: " << chi << endl;
	

}


int main()
{
	//test_chi_square_1st();
	test_chi_square_2nd();
	return 0;
}