//GK_test
#include<cassert>
#include "../SourceCode/Quantiles/GK.h"
#include <iostream>

/*
Complile with g++ -o gk.o -std=c++11 GK_test.cpp
*/

void test_GK()
{
  GK a(1000);
  GK b(1000);
  GK c(1000);
  int quantA,quantB,quantC;
  bool condA,condB,condC;
  double upper,lower;
  int n=100000;
  
  for (int i=n;i>=1;i--)
  {
  	a.insert(i); //inserting in desceding order
  }
  for (int i=0;i<=n;i++)
  {
  	int rand_num=rand()%n;
  	b.insert(i); //inserting in ascending order
  	c.insert(rand_num); //inserting random numbers of range 0-10 million
  	
  }
  
  for (float i=0;i<=100;i++)
  {
  	  float interval=i/100; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  quantC=c.getQuantile(interval);//getting quantile for each probability interval
  	  
  	  cout<<"QuantA "<<quantA<<endl;
  	  
  	  lower=(interval-0.003)*n;
  	  upper=(interval+0.003)*n;
  	  
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
  	  
}

int main()
{
 test_GK();
  return 0;
}
