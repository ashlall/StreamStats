// Unit tests for origin QDigest class
// Where only the input is limited to integer, ranging from 0 to MAX_NUMBER

#include<cassert>
#include "../SourceCode/Quantiles/Q-Digest.h"
#include <iostream>

using namespace std;

void test_qdigest()
{
	int n = 100000; //stream size;
	int k = 0.5 * n; //compress factor 
					// usually the choose of k ranges from 0.3n to 0.5n in order to get the best query results
	long quantA,quantB,quantC;
	bool condA,condB,condC;
    double upper,lower;
    
	QDigest a(k);
	QDigest b(k);
	QDigest c(k);
	
	for (int i = n; i >= 1; i--)
    {
  		a.insert(i); //inserting in desceding order
    }
    for (int i = 0; i <= n; i++)
   {
  		int rand_num=rand()%n;
  		b.insert(i); //inserting in ascending order
  		c.insert(rand_num); //inserting random numbers of range 0-10 million
  	}  
  	
  	
  for (float i=1;i<=100;i++)
  {
  	  double interval=i/100; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  quantC=c.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  lower=(interval-0.004)*n;
  	  upper=(interval+0.004)*n;
  	  
  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  //checking if quantile is within error range
  	  
  	 condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range
  	  
  	  condC= ((lower<=quantC) && (upper>=quantC));
  	  //checking if quantile is within error range
  	  
  	  assert(condA==true);
  	  assert(condB==true);
  	  assert(condC==true);
  } 
    
  
	/*
	QDigest a(35000);
	for(int i=1; i<=100000; i++)
	{
		a.insert(i);
	}

	cout << "median:" << a.getQuantile(0.5) << endl;
	cout << "0.1: "<<a.getQuantile(0.1) << endl;
	cout << "0.3: "<<a.getQuantile(0.3) << endl;
	cout << "0.4: "<<a.getQuantile(0.4) << endl;
	cout << "0.8: "<<a.getQuantile(0.8) << endl;
	*/
}


int main()
{
  test_qdigest();
  return 0;
}
