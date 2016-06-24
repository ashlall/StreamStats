//GK_test
#include<cassert>
#include <iostream>
#include <random>
#include <math.h>    

#include "../SourceCode/Quantiles/GK.cpp"

//include -std=c++11 flag when compling


//Input: Stream size, sample size
//Output: It will test the function of insert, get_stream_size, and getQuantile.
//It will return nothing if it passes. It Will exist if the following test did not pass.
void test_GK(int stream_size, int sample_size)
{
	double epsilon = log(stream_size)/sample_size;
	
	double quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
	double upper,lower;
	
	int random_fix1 = rand()% RAND_MAX;
 	int random_fix2 = rand()% RAND_MAX;
 	int random_fix3 = rand()% RAND_MAX;
        
    	GK a(sample_size);
 	GK b(sample_size);
	GK c(sample_size);
	GK d(sample_size);
 	GK e(sample_size);
	GK f(sample_size);
	GK g(sample_size);
 	GK h(sample_size);

	
	for (double j = 0; j <= stream_size; j++) //inserting in decreasing order
   	{	
  		a.insert(j); 
    	}
    	bool condA1;
	int LA = a.get_stream_size(); //test the function get_stream_size()
	condA1= (LA == stream_size+1);
	assert(condA1 == true);

	for (double i = stream_size; i >= 0; i--) //inserting in desceding order
    	{
  		b.insert(i); 
    	}
    	bool condB1;
	int LB = b.get_stream_size(); //test the function get_stream_size()
	condB1= (LB == stream_size+1);
	assert(condB1 == true);

	/*
	Generate three uniform distribution with the following range. In order to have a "good" uniform distribution, recommend large stream size.
	*/
	int uni_lower_bound1 = 500;
	int uni_upper_bound1 = 1000;

	int uni_lower_bound2 = 1234;
	int uni_upper_bound2 = 5678;

	int uni_lower_bound3 = 0;
	int uni_upper_bound3 = 5000;
	for (int m = 1; m <= 3; m++) //create 3 "random" sequences that holds their randomness every time runs the code
  	{
		double data;
  		if (m == 1)
  		{	
			default_random_engine generator(5);
			uniform_real_distribution<double> distribution(uni_lower_bound1,uni_upper_bound1);
			for (int i = 0; i <= stream_size; i++)
			{
   				data = distribution(generator);
  				c.insert(data);
			} 
  		}
  		
  		else if(m == 2)
  		{
			default_random_engine generator(10);
			uniform_real_distribution<double> distribution(uni_lower_bound2,uni_upper_bound2);
			for (int i = 0; i <= stream_size; i++)
			{
   				data = distribution(generator);
  				d.insert(data);
			}
  		}	
  		
  		else 
  		{	
			default_random_engine generator(20);
			uniform_real_distribution<double> distribution(uni_lower_bound3,uni_upper_bound3);
			for (int i = 0; i <= stream_size; i++)
			{
   				data = distribution(generator);
  				e.insert(data);
			}
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
	  	
  for (float i=1;i<=stream_size;i++)
  {
  	  double interval=i/stream_size; //getting each probabilty interval
  	  
  	  quantA=a.getQuantile(interval); //getting quantile for each probability interval
  	  quantB=b.getQuantile(interval);
  	  quantC=c.getQuantile(interval);
  	  quantD=d.getQuantile(interval);
  	  quantE=e.getQuantile(interval);
  	  quantF=f.getQuantile(interval);
  	  quantG=g.getQuantile(interval);
  	  quantH=h.getQuantile(interval);
  	  
  	  lower=(interval-epsilon)*stream_size;//Used for first two cases.
  	  upper=(interval+epsilon)*stream_size;
  	  //cout << "l: " << lower << "  " << "u: " << upper <<endl;

  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range
  	  
	
	 // cout << "cao:" << quantD<<endl;
	  //cout << (uni_lower_bound2 + (uni_upper_bound2-uni_lower_bound2)*interval)+epsilon*stream_size << endl;
 	 //cout << (uni_lower_bound2 + (uni_upper_bound2 - uni_lower_bound2)*interval)-epsilon*stream_size << endl;
	 //cout << "" <<endl;

	 condC = (quantC >= (uni_lower_bound1+(uni_upper_bound1 - uni_lower_bound1)*interval)- epsilon*stream_size) && (quantC <= (uni_lower_bound1+(uni_upper_bound1 - uni_lower_bound1)*interval) + epsilon*stream_size);
	 condD = (quantD >= (uni_lower_bound2+(uni_upper_bound2 - uni_lower_bound2)*interval)- epsilon*stream_size) && (quantD <= (uni_lower_bound2+(uni_upper_bound2 - uni_lower_bound2)*interval) + epsilon*stream_size);
	 condE = (quantE >= (uni_lower_bound3+(uni_upper_bound3 - uni_lower_bound3)*interval)- epsilon*stream_size) && (quantE <= (uni_lower_bound3+(uni_upper_bound3 - uni_lower_bound3)*interval) + epsilon*stream_size);
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

//Input: Stream size, sample size
//Output: It will test the function of reverseQuantile.
//It will return nothing if it passes. It Will exist if the following test did not pass.
void test_reverseQuantile(double stream_size, double sample_size)
{
	GK m(sample_size);
	GK n(sample_size);
	double epsilon = log(stream_size)/sample_size;
	//cout << "e: " << error<<endl;
	bool check1, check2;
	double hold1, hold2;

	for(double i = 0; i<=stream_size; i++)
	{
		m.insert(i);
		n.insert(stream_size-i);
	}

	//If the sample_size is large enough, then the reverse quantile lookup should return the EXACT index. Here, we transformed into probability.
	if (sample_size >= stream_size*3)
	{
		for(double i = 0; i<=stream_size; i++)
		{ 
			hold1 = ((m.reverseQuantile(i, stream_size))/stream_size);
			check1 = (hold1 == i/stream_size);
			assert(check1==true);

			hold2 = ((n.reverseQuantile(i, stream_size))/stream_size);
			check2 = (hold2 == i/stream_size);
			assert(check2==true);
		}
	}

	//Theoratically, the reverse quantile lookup will generate 3epsilon.

	else
	{
		for(double i = 0; i<=stream_size; i++)
		{ 
			hold1 = ((m.reverseQuantile(i, stream_size))/stream_size);
			check1 = ((hold1 >= i/stream_size - 3*epsilon) &&  (hold1 <= i/stream_size + 3*epsilon));
			assert(check1==true);

			hold2 = ((n.reverseQuantile(i, stream_size))/stream_size);
			check2 = ((hold2 >= i/stream_size - 3*epsilon) &&  (hold2 <= i/stream_size + 3*epsilon));
			assert(check2==true);
		}			
	}		
}		


int main()
{	
	test_GK(50000, 8000);
	test_reverseQuantile(5000,5000); 
 	return 0;
}










