//GK_test
#include<cassert>
#include <iostream>
#include <random>

#include "../SourceCode/Quantiles/GK.cpp"

//include -std=c++11 flag when compling


//Input: Stream size, sample size
//Output: Nothing. Will exist if the following test did not pass.
void test_GK(int stream_size, int sample_size)
{
	int k = sample_size; 
	long quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
	double upper,lower;
	int n=stream_size; 
	
	int random_fix1 = rand()% RAND_MAX;
 	int random_fix2 = rand()% RAND_MAX;
 	int random_fix3 = rand()% RAND_MAX;
        
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
  			  for (int i = 0; i <= n; i++)
   			 {
   			 	srand(n-i);
  				long rand_num=rand()%n;
  				e.insert(rand_num); //inserting float number from 0 to n
  			 }  
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

//Input: Stream size, sample size
//Output: Nothing. Will exist if the following test did not pass.
void test_reverseQuantile(double stream_size, double sample_size)
{
	//If the sample_size is large enough, then the reverse quantile lookup should return the EXACT index. Here, we transformed into probability.
	if (sample_size >= stream_size*3)
	{
		GK m(sample_size);
		GK n(sample_size);
		bool check;
		double hold;

		for(double i = 0; i<=stream_size; i++)
		{
			m.insert(i);
			n.insert(stream_size-i);
		}
	
		for(double i = 0; i<=stream_size; i++)
		{ 
			hold = ((m.reverseQuantile(i, stream_size))/stream_size);
			check = (hold == i/stream_size);
			assert(check==true);

			hold = ((n.reverseQuantile(i, stream_size))/stream_size);
			check = (hold == i/stream_size);
			assert(check==true);
		}
	}

	//Theoratically, the reverse quantile lookup will generate 3epsilon.
	else
	{
		GK m(sample_size);
		GK n(sample_size);
		bool check1, check2;
		double hold1, hold2;

		for(double i = 0; i<=stream_size; i++)
		{
			m.insert(i);
			n.insert(stream_size-i);
		}
	
		for(double i = 0; i<=stream_size; i++)
		{ 
			hold1 = ((m.reverseQuantile(i, stream_size))/stream_size);
			check1 = ((hold1 >= i/stream_size - (1/stream_size)*3) &&  (hold1 <= i/stream_size + (1/stream_size)*3));
			assert(check1==true);

			hold2 = ((n.reverseQuantile(i, stream_size))/stream_size);
			check2 = ((hold2 >= i/stream_size - (1/stream_size)*3) &&  (hold2 <= i/stream_size + (1/stream_size)*3));
			assert(check2==true);
		}			
	}		
}		


int main()
{	
	//test_GK(10000, 20000);
	test_reverseQuantile(5000,15000); 
 	return 0;
}


