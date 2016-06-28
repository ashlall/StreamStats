/*
Chi_Square_test.cpp

Unit tests for One-Sample Chi-square & Two sample Chi-square.
NOTE!!!: the get_frequencies way of calculating the chi^2 statistic doesn't work for negative values
*/

#include<cassert>
#include <iostream>
#include<iomanip> 
#include <random>
#include <sys/time.h>

#include "../SourceCode/ChiSquare/ChiSquareContinuous.cpp"
using namespace std;

int* get_frequencies(double *upper, double *lower, double *items, int num_buckets, int stream_size);

/*
void test_NormalCDFInverse()
{
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

	ChiSquareContinuous a(3000);
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
 }
 */
 
void test_chi_square_1st() //One-sample test
{
 	int sketch_method = 1;
	cout << "Enter the number 1-4 to choose sketch method that you want to use: "<<endl;
	cout << "1. Greenwald sketch/default." <<endl;
	cout << "2. Q-Digest sketch." <<endl;
	cout << "3. Reservoir Sampling sketch." <<endl;
	cout << "4. Count-Min Sketch." <<endl;
	cin >> sketch_method;

 	int stream_size;
 	cout << "Enter the stream size: "<<endl;
	cin >> stream_size;

	int sample_size;
	cout << "Enter the memory capacity for the sample size: "<<endl;
 	cin >> sample_size;
  
	int k;
 	cout << "Enter the number of bins you want to use: " <<endl;
 	cin >> k;

	int mean, SD;
	cout << "Enter the mean of the normal distribution you want to compare against: "<<endl;
	cin >> mean;
	cout << "Enter the standard deviation of the normal distribution you want to compare against: "<<endl;
	cin >> SD;

	ChiSquareContinuous b(sample_size, sketch_method); //ChiSquare b(memory, sketch method);
	ChiSquareContinuous b1(sample_size, sketch_method);
	ChiSquareContinuous b2(sample_size, sketch_method);

 	double item;
	double chiEstimated;
  
	double N=0;
	double *items=new double[stream_size];
	default_random_engine generator(5);
	normal_distribution<double> distribution(mean,SD);
	for (int i=0; i<stream_size; i++) 
	{
    		item = distribution(generator);
    		N++;
    		items[i]=item;
  		b.insert(item);
  		b1.insert(item);
  		b2.insert(item);
    	}
    	chiEstimated = b.calculate_statistic_ifNormal(k,mean,SD);
    
    
    	double *Upper=b.get_upper();
    	double *Lower=b.get_lower();
    	double E=N/k;
    	double chiActual=0, chiActual2 = 0;
    /*timeval timeBefore, timeAfter;
    long diffSeconds, diffUSeconds;
    gettimeofday(&timeBefore, NULL);*/
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

    /*gettimeofday(&timeAfter, NULL);
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
    cout << "1st way: " << diffSeconds + diffUSeconds/1000000.0 << endl;

    gettimeofday(&timeBefore, NULL);
    int *frequencies = get_frequencies(Upper, Lower, items, k, stream_size);
    for (int i = 1; i <= k; i++)
      { 
	chiActual2 += (frequencies[i] - E) * (frequencies[i] - E)/E;
	}*/
    /*gettimeofday(&timeAfter, NULL);
    diffSeconds= timeAfter.tv_sec - timeBefore.tv_sec;
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
    cout << "2nd way: "<< diffSeconds + diffUSeconds/1000000.0<<" seconds\n";*/

   	cout << "chiActual: "<< chiActual << endl;
   	
  	cout << "chiEstimated: " << chiEstimated << endl;
  	
  	cout << "Estimated p-value by calling calculate_pvalue(x,DF): "<< b.calculate_pvalue(chiEstimated, k-2) <<endl;

  	cout << "Estimated p-value by calling calculate_pvalue_ifNormal(num_bins, mean, SD): " << b1.calculate_pvalue_ifNormal(k, mean, SD) <<endl;

  	cout << "Estimated final decision by calling final_decision_ifNormal(num_bins, mean, SD, com_p): "<<b2.final_decision_ifNormal(k, mean, SD, 0.05) <<endl;

  	delete []items;
	//delete [] frequencies;
}

void test_chi_square_2nd() //Two-sample test
{
 	int sketch_method = 1;
  	cout << "Enter the number 1-3 to choose sketch method that you want to use: "<<endl;
  	cout << "1. Greenwald sketch/default." <<endl;
  	cout << "2. Q-Digest sketch." <<endl;
  	cout << "3. Reservoir Sampling sketch." <<endl;
  	cin >> sketch_method;

	int stream_size1;
	int stream_size2;
  	cout << "Enter the first stream's size: "<<endl;
  	cin >> stream_size1;
	cout << "Enter the second stream's size: "<<endl;
	cin >> stream_size2;

  	int sample_size1;
	int sample_size2;
  	cout << "Enter the memory capacity for the first sample size: "<<endl;
 	cin >> sample_size1;
  	cout << "Enter the memory capacity for the second sample size: "<<endl;
 	cin >> sample_size2;
  
	int k;
 	cout << "Enter the number of bins you want to use: " <<endl;
 	cin >> k;

	int mean1, SD1;
	int mean2, SD2;
	cout << "Enter the mean of the first normal distribution: "<<endl;
	cin >> mean1;
	cout << "Enter the mean of the second normal distribution: "<<endl;
	cin >> mean2;
 	cout << "Enter the standard deviation of the first normal distribution: "<<endl;
	cin >> SD1;
 	cout << "Enter the standard deviation of the second normal distribution: "<<endl;
	cin >> SD2;

	ChiSquareContinuous c1(sample_size1, sketch_method), c2(sample_size2, sketch_method); 

	double *items1=new double[stream_size1]; //used for storing all the generated data for calculating the actual chi^2.
	double *items2=new double[stream_size2];
	double data1;
	double data2;
	default_random_engine generator(5);
	normal_distribution<double> distribution(mean1,SD1);

	for (int i=0; i<stream_size1; i++) 
  	{
   		data1 = distribution(generator);
		items1[i] = data1;
  		c1.insert(data1);
 	}

	default_random_engine generator2(5);
	normal_distribution<double> distribution2(mean2,SD2);
 	for (int i = 0; i < stream_size2; i++)
  	{
		data2 = distribution2(generator2);
		items2[i] = data2;
		c2.insert(data2);
 	}

	double chiEestimated;
        chiEestimated = c1.two_sample_statistic(c2, k);
   	double chiActual=0;

   	double *Upper=c1.get_upper();
   	double *Lower=c1.get_lower();
	double constant_1 = sqrt((double)stream_size2/stream_size1);
 	double constant_2 = sqrt((double)stream_size1/stream_size2);

   	/*timeval timeBefore, timeAfter;
   	long diffSeconds, diffUSeconds;
   	gettimeofday(&timeBefore, NULL);*/
   	for (int i=1;i<=k;i++)
   	{	
    		double E=0;
        	for(int j=0;j<stream_size1;j++)
    	    	{
    	    		if(( items1[j]<=Upper[i]) && (items1[j]>=Lower[i]))
		        	E++;
    	    	}
	
    		double O=0;
        	for(int j=0;j<stream_size2;j++)
    	    	{
    	    		if(( items2[j]<=Upper[i]) && (items2[j]>=Lower[i]))
		        	O++;
    	    	}
                //cout <<"actual S_i and R_i: " << E << " " << O<< endl;
	
      	    	double lambda= E*constant_1 - O*constant_2;
	 
	    	//cout<<"i: "<< i << " Expected: "<<E << " "<<"actual:" << O <<endl;

    	   	chiActual=chiActual+((lambda*lambda)/(E+O)); 	    
    	}	
    /*gettimeofday(&timeAfter, NULL);
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
    cout << "1st way: " << diffSeconds + diffUSeconds/1000000.0 << endl;

    gettimeofday(&timeBefore, NULL);
    int *frequencies = get_frequencies(Upper, Lower, items, k, stream_size);
    for (int i = 1; i <= k; i++)
      { 
	chiActual2 += (frequencies[i] - E) * (frequencies[i] - E)/E;
	}*/
    /*gettimeofday(&timeAfter, NULL);
    diffSeconds= timeAfter.tv_sec - timeBefore.tv_sec;
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
    cout << "2nd way: "<< diffSeconds + diffUSeconds/1000000.0<<" seconds\n";*/
  	cout << "chiEestimated: " << chiEestimated << endl;
	cout << "chiActual: " << chiActual << endl;
}





int* get_frequencies(double *upper, double *lower, double *items, int num_buckets, int stream_size)
{
  int *frequencies = new int[num_buckets];
  for (int i = 0; i < num_buckets; i++)
    frequencies[i] = 0;
  for (int i = 0; i < stream_size; i++)
  {
    //cout << "item: " << items[i] << " ***" << endl;
    int lo = 0, hi = num_buckets;
    while (lo <= hi)
    {
      int mid = (lo + hi) / 2;
      //cout << "mid: " << endl;
      if (items[i] <= upper[mid] && items[i] >= lower[mid])
      {
	frequencies[mid]++;
	break;
      }
      /*else if (items[i] < upper[0])
      {
	cout << "hello" << endl;
	frequencies[0]++;
	break;
      }
      else if (items[i] > lower[num_buckets-1])
      {
	cout << "hi" << endl;
	frequencies[num_buckets-1]++;
	break;
	}*/
      else if (items[i] < lower[mid])
	{
	  //	  cout << "lower, " << endl;
	hi = mid;
	}
      else
	lo = mid + 1;
    }
  }
  return frequencies;
}


int main()
{
  //test_chi_square_1st(1);
  //test_chi_square_1st(2);

  //test_chi_square_1st();
	test_chi_square_2nd();
	//test_NormalCDFInverse();
	return 0;
}

