// Unit tests for derived QDigest class
// Where the input of floating points are also allowed.

#include<cassert>
#include "../SourceCode/Quantiles/QDigestDouble.h"
#include <iostream>

using namespace std;

void test_qdigetDouble()
{
	int n = 1000;
	int k = 0.5 * n; //compress factor 
					// usually the choose of k ranges from 0.3n to 0.5n in order to get the best query results
					
	long quantA,quantB,quantC;
	bool condA,condB,condC;
    double upper,lower;
    
	QDigest a(k);
	QDigest b(k);
	//QDigest c(k);
	
	for (double i = 0; i <= n; i = i + 0.1)
    {	
  		a.insert(i); //inserting in increasing order
    }
    
	for (double j = n; j >= 0; j = j - 0.1)
    {	
  		b.insert(j); //inserting in increasing order
    }
  	
	//random floating number from MIN ~ MAX are needed. Use seed().. !!!!!

    for (float i=1;i<=100;i++)
    {
  	  double interval=i/100; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  //quantC=c.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  lower=(interval-0.02)*n;
  	  upper=(interval+0.02)*n;
  	  
  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  //checking if quantile is within error range
  	  
  	  condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range
  	  
  	 //condC= ((lower<=quantC) && (upper>=quantC));
  	  //checking if quantile is within error range
  	  
  	  assert(condA==true);
  	  assert(condB==true);
  	  //assert(condC==true);
  } 
 
	  /*
		QDigestDouble a(500);
		for(double i=1; i<=1000; i = i + 0.3)
		{
			cout << "i: " << i << endl;
			a.insert(i);
		}

		cout << "median:" << a.getQuantile(0.5) << endl;
		cout << "0.1: "<<a.getQuantile(0.1) << endl;
		cout << "0.3: "<<a.getQuantile(0.3) << endl;
		cout << "0.4: "<<a.getQuantile(0.4) << endl;
		cout << "0.8: "<<a.getQuantile(0.8) << endl;
		cout << "hi" <<endl; 
*/
}


int main()
{
  test_qdigetDouble();
  return 0;
}
