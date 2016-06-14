/*
Unit tests for Reservoir Sampling class.

It doesn't work well for the extrem case when n = 1 due to the implementation itself.
Modification might needed. 
*/

#include<cassert>
#include "../SourceCode/Quantiles/ReservoirSampling.h"
#include <iostream>

void test_reservoir()
{
	int k = 1000; // Reservoir sample size	
	long quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
	double upper,lower;
	int n=10000000; //StreamSize
	
	/*	Extrem case when n = 1
	
	int random_fix1 = rand()% RAND_MAX;
    cout << "random_fix1: " << random_fix1 <<endl;
    int random_fix2 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix2 <<endl;
    int random_fix3 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix3 <<endl;
    */
    
	ReservoirSampling a(k); 
	ReservoirSampling b(k);
	ReservoirSampling c(k);
	ReservoirSampling d(k);
	ReservoirSampling e(k);
	
	/*	Extrem case when n = 1
	
	ReservoirSampling f(k);
	ReservoirSampling g(k);
	ReservoirSampling h(k);
  	*/
  	
	for (int i=0;i <= n;i++) //inserting in increasing order
	{
		a.insert(i); 
		
	}
	
	for (int i = n; i >= 1; i--) //inserting in desceding order
    {
  		b.insert(i); 
    }
  
 	for (int m = 1; m <= 3; m++) //create 3 "random" sequences with certain patterned seed that holds their randomness every time runs the code
  	{
  		 if (m == 1)
  		 {
  		   	 //cout << "sequence 1: " << endl;
  			 for (int i = 0; i <= n; i++)
   			 {
   			 	srand(i);
  				long rand_num=rand()%n;
  				//cout << rand_num << " ";
  				c.insert(rand_num);  //inserting float number from 0 to n
  			 }
  			 //cout << ""<<endl;
  		}
  		
  		else if(m == 2)
  		{
  		 	  //cout << "sequence 2: " << endl;
  			  for (int i = 0; i <= n; i++)
   			 {
   			    srand(i^2);
  				long rand_num=rand()%n;
  				//cout << rand_num << " ";
  				d.insert(rand_num); //inserting float number from 0 to n
  			 }  
  			 //cout << ""<<endl;
  		}	
  		
  		else 
  		{	
  		  	 //cout << "sequence 3: " << endl;
  			  for (int i = 0; i <= n; i++)
   			 {
   			 	srand(n-i);
  				long rand_num=rand()%n;
  				//cout << rand_num << " ";
  				e.insert(rand_num); //inserting float number from 0 to n
  			 }  
  			 //cout <<""<<endl;
  		}
  	} 

	  /*	Extrem case when n = 1
	  	
  	  f.insert(random_fix1); 
  	  g.insert(random_fix2); 
  	  h.insert(random_fix3);  
  	  */ 
  	
	for (float i=1;i<=100;i++)
	{
  	  double interval=i/100; //getting each percentile probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  quantC=c.getQuantile(interval);//getting quantile for each probability interval
  	  quantD=d.getQuantile(interval);
  	  quantE=e.getQuantile(interval);
  	  
	  /*	Extrem case when n = 1
	  
  	  quantF=f.getQuantile(interval);
  	  quantG=g.getQuantile(interval);
  	  quantH=h.getQuantile(interval);
  	  */
  	  
  	  lower=(interval-0.05)*n;
  	  upper=(interval+0.05)*n;
  	  
  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  //checking if quantile is within error range

  	  condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range

  	  condC= ((lower<=quantC) && (upper>=quantC));
  	  condD= ((lower<=quantD) && (upper>=quantD));
  	  condE= ((lower<=quantE) && (upper>=quantE));
  	  //checking if quantile is within error range
  	  
  	  /*	Extrem case when n = 1
  	  
  	  condF= (random_fix1 = quantF);
  	  condG= (random_fix2 = quantG);
  	  condH= (random_fix3 = quantH);
	  */
  	  
  	  assert(condA==true);
  	  assert(condB==true);
  	  assert(condC==true);
  	  assert(condD==true);
  	  assert(condE==true);
  	  
  	  /*	Extrem case when n = 1
  	  assert(condF==true);
  	  assert(condG==true);
  	  assert(condH==true);
  	  */
  }   
}

void quicktest()
{
	ReservoirSampling a(1000);
	for(int i=1; i<=1000000; i++)
	{
		a.insert(i);
	}

	cout << "median:" << a.getQuantile(0.5) << endl;
	cout << "0.1: "<<a.getQuantile(0.1) << endl;
	cout << "0.3: "<<a.getQuantile(0.3) << endl;
	cout << "0.4: "<<a.getQuantile(0.4) << endl;
	cout << "0.8: "<<a.getQuantile(0.8) << endl;
}

int main()
{
  test_reservoir();
  quicktest();
  return 0;
}
