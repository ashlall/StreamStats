// Unit tests for origin QDigest class
// Where only the input is limited to integer, ranging from 0 to MAX_NUMBER

#include<cassert>
#include "../SourceCode/Quantiles/Q-Digest.h"
#include <iostream>

using namespace std;

void test_qdigest()
{
	int n = 100; 
	int k = 5000; //compress factor, make an arbitrarily large k for testing 
					// usually the choose of k ranges from 0.3*stream_length  to 0.5*stream_length  in order to get the best query results
	long quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
    double upper,lower;
    
    int random_fix1 = rand()% RAND_MAX;
    //cout << "random_fix1: " << random_fix1 <<endl;
    int random_fix2 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix2 <<endl;
    int random_fix3 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix3 <<endl;

    
	QDigest a(k);
	QDigest b(k);
	QDigest c(k);
	QDigest d(k);
    QDigest e(k);
	QDigest f(k);
	QDigest g(k);
	QDigest h(k);
	
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
