//GK_test
#include<cassert>
#include "../SourceCode/Quantiles/GK.h"
#include <iostream>
#include <random>
/*
Complile with g++ -o gk.o -std=c++11 GK_test.cpp
*/

void test_GK()
{
	int k = 1000; 
	long quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
	double upper,lower;
	int n=10000; 
	
    int random_fix1 = rand()% RAND_MAX;
    //cout << "random_fix1: " << random_fix1 <<endl;
    int random_fix2 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix2 <<endl;
    int random_fix3 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix3 <<endl;
    
    GK a(k);
 	GK b(k);
	GK c(k);
	GK d(k);
 	GK e(k);
	GK f(k);
	GK g(k);
 	GK h(k);

	
	for (double j = 0; j <= n; j++) //inserting in decreasing order
    {	
  		a.insert(j); 
    }
    bool condA1;
	int LA = a.get_stream_size(); //test the function get_stream_size()
	condA1= (LA == n+1);
	assert(condA1 == true);
	
	for (int i = n; i >= 0; i--) //inserting in desceding order
    {
  		b.insert(i); 
    }
    bool condB1;
	int LB = b.get_stream_size(); //test the function get_stream_size()
	condB1= (LB == n+1);
	assert(condB1 == true);
	    
	for (int m = 1; m <= 3; m++) //create 3 "random" sequences that holds their randomness every time runs the code
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
  			 bool condC1;
			 int LC = c.get_stream_size(); //test the function get_stream_size()
			 condC1= (LC == n+1);
			 assert(condC1 == true);
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
  			 bool condD1;
			 int LD = d.get_stream_size(); //test the function get_stream_size()
			 condD1= (LD == n+1);
			 assert(condD1 == true);  
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
  			 bool condE1;
			 int LE = e.get_stream_size(); //test the function get_stream_size()
			 condE1= (LE == n+1);
			 assert(condE1 == true);
  		}
  	}
  	
  	  f.insert(random_fix1); //test corner case where n = 1
  	  g.insert(random_fix2); 
  	  h.insert(random_fix3);   	
  	  bool condF1,condG1,condH1;
	  long LF = f.get_stream_size(); //test the function get_stream_size()
	  long LG = g.get_stream_size();
 	  long LH = h.get_stream_size();
      condF1 = (LF == 1);
      condG1 = (LG == 1);
	  condH1 = (LH == 1);
	  assert(condF1 == true);
	  assert(condG1 == true);
	  assert(condH1 == true);  
	  	
  for (float i=1;i<=100;i++)
  {
  	  double interval=i/100; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);//getting quantile for each probability interval
  	  quantC=c.getQuantile(interval);//getting quantile for each probability interval
  	  quantD=d.getQuantile(interval);
  	  quantE=e.getQuantile(interval);
  	  quantF=f.getQuantile(interval);
  	  quantG=g.getQuantile(interval);
  	  quantH=h.getQuantile(interval);
  	  
  	  lower=(interval-0.04)*n;
  	  upper=(interval+0.04)*n;
  	  
  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  //checking if quantile is within error range
  	  
  	  condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range
  	  
  	  condC= ((lower<=quantC) && (upper>=quantC));
  	  condD= ((lower<=quantD) && (upper>=quantD));
  	  condE= ((lower<=quantE) && (upper>=quantE));
  	  //checking if quantile is within error range
  	  
  	  
  	  condF= (random_fix1 == quantF);
  	  condG= (random_fix2 == quantG);
  	  condH= (random_fix3 == quantH);
  	  //checking if the condition holds in the corner case where stream size = 1

  	  
  	  assert(condA==true);
  	  assert(condB==true);
  	  assert(condC==true);
  	  assert(condD==true);
  	  assert(condE==true);
  	  assert(condF==true);
  	  assert(condG==true);
  	  assert(condH==true);
  } 
  	  
}

void quicktest()
{
	GK a(1000);
	for(int i=1; i<=1000000; i++)
	{
		a.insert(i + 0.13416435);
	}

	cout << "0.1: "<<a.getQuantile(0.1) << endl;
	cout << "0.2: "<<a.getQuantile(0.2) << endl;
	cout << "0.3: "<<a.getQuantile(0.3) << endl;
	cout << "0.4: "<<a.getQuantile(0.4) << endl;
	cout << "median:" << a.getQuantile(0.5) << endl;
	cout << "0.6: "<<a.getQuantile(0.6) << endl;
	cout << "0.7: "<<a.getQuantile(0.7) << endl;
	cout << "0.8: "<<a.getQuantile(0.8) << endl;
	cout << "0.9: "<<a.getQuantile(0.9) << endl;
	cout << "1: "<<a.getQuantile(1) << endl;
}

void test_reverse()
{
	GK larry(3000);
	int stream_size =88888;
	double item;
	
	default_random_engine generator;
    normal_distribution<double> distribution(3000,50);
    
    for (int i=0; i<stream_size; i++) 
    {
    	item = distribution(generator);
    	//item = i;
  	    larry.insert(item);
  	}
  	
  	double median;
  	median = larry.getQuantile(0.5);
  	cout << median << endl;
  	double median_index;
  	median_index = larry.reverseQuantile(3000, stream_size);
  	cout << median_index << endl;
}

int main()
{
  //test_GK();
  //quicktest();
  test_reverse();
  return 0;
}
