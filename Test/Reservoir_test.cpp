// unit tests for Reservoir Sampling class

#include<cassert>
#include "../SourceCode/Quantiles/ReservoirSampling.h"
#include <iostream>
//this stage 
void test_reservoir1()
{
  ReservoirSampling a(1000);
  ReservoirSampling b(1000);
  int quantA,quantB;bool condA,condB, condM, condN;
  int n=100000000;
  
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
  	  
  	  condA= (a.getQuantile(interval*1000- 0.001*n)<=quantA) && (a.getQuantile(interval*1000 + 0.001*n)>=quantA);
  	  //checking if quantile is within error range (j is in {i-en, i+en})
  	  
  	  condB= (b.getQuantile(interval*1000- 0.001*n)<=quantB) && (b.getQuantile(interval*1000 + 0.001*n)>=quantB);
  	  //checking if quantile is within error range (j is in {i-en, i+en})
  	  
  	  assert(condA==true);
  	  assert(condB==true);
  }
  
  /*
  Test of reverseQuantile() is still needed.
  */
  	  
}
void test_reservoir2()
{
  ReservoirSampling c(1000);
  int quant;bool cond;
  int n=10000000;
  
  for (int i=1;i<=n;i++)
  {	
  	int rand_num=rand()%10000000;
  	c.insert(rand_num); //inserting random numbers of range 0-10 million
  }
  for (float i=0;i<=100;i++)
  {
  	  float interval=i/100;//getting each probabilty interval
  	  quant=c.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  //cond= ((interval-0.04)*n <=quant) && ((interval+0.04)*n>=quant);
  	  cond= (c.getQuantile(interval*1000- 0.001*n)<=quant) && (c.getQuantile(interval*1000 + 0.001*n)>=quant);
  	  //checking if quantile is within error range (j is in {i-en, i+en})
  	  
  	  assert(cond==true);
  }
	
}


int main()
{
 test_reservoir1(); //tests for data in ascending and descending order. 
 test_reservoir2(); //tests for data inserted in random order
  return 0;
}
