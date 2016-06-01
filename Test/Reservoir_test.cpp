// unit tests for Reservoir Sampling class

#include<cassert>
#include "../SourceCode/Quantiles/ReservoirSampling.h"
#include <iostream>

void test_reservoir1()
{
  ReservoirSampling a(1000);
  ReservoirSampling b(1000);
  int quantA,quantB;bool condA,condB;
  int n=10000000;
  
  for (int i=n;i>=1;i--)
  {
  	a.insert(i); //inserting in desceding order
  }
  for (int i=0;i<=n;i++)
  {
  	b.insert(i); //inserting in ascending order
  }
  
  for (float i=0;i<=100;i++)
  {
  	  float interval=i/100; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  condA= ((interval-0.04)*n <=quantA) && ((interval+0.04)*n>=quantA);
  	  //checking if quantile is within error range
  	  
  	  condB= ((interval-0.04)*n <=quantB) && ((interval+0.04)*n>=quantB);
  	  //checking if quantile is within error range
  	  
  	  assert(condA==true);
  	  assert(condB==true);
  }
  
  	  
}
void test_reservoir2()
{
  ReservoirSampling a(1000);
  int quant;bool cond;
  int n=10000000;
  
  for (int i=1;i<=n;i++)
  {	
  	int rand_num=rand()%10000000;
  	a.insert(rand_num); //inserting random numbers of range 0-10 million
  }
  for (float i=0;i<=100;i++)
  {
  	  float interval=i/100;//getting each probabilty interval
  	  quant=a.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  cond= ((interval-0.04)*n <=quant) && ((interval+0.04)*n>=quant);
  	  //checking if quantile is within error range
  	  
  	  assert(cond==true);
  }
	
}


int main()
{
 test_reservoir1(); //tests for data in ascending and descending order. 
 test_reservoir2(); //tests for data inserted in random order
  return 0;
}
