// Unit tests for derived QDigest class
// Where the input of floating points are also allowed.

#include<cassert>
#include "../SourceCode/Quantiles/QDigestDouble.h"
#include <iostream>

using namespace std;

void test_qdigetDouble()
{
	int n = 50;
	int k = 5000; //make an arbitrarily large k for testing 	
				//Compress factor: usually the choice of k ranges from 0.3*stream_length to 0.5stream_length  in order to get the best query results

					
	double quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
    double upper,lower;
    
    double random_fix1 = rand()% RAND_MAX + 0.12345; //used to test corner case where n = 1
    double random_fix2 = rand()% RAND_MAX + 0.12345;
    double random_fix3 = rand()% RAND_MAX + 0.12345;

	QDigestDouble a(k);
	QDigestDouble b(k);
	QDigestDouble c(k);
	QDigestDouble d(k);
    QDigestDouble e(k);
	QDigestDouble f(k);
	QDigestDouble g(k);
	QDigestDouble h(k);
		
	for (double i = 0; i <= n; i = i + 0.1) //inserting in increasing order
    {	
  		a.insert(i); 
    }
	bool condA1;
	long LA = a.get_stream_size(); //test the function get_stream_size()
	condA1= (LA == n/0.1);
	assert(condA1 == true);
	   
	   
	for (double j = n; j >= 0; j = j - 0.1) //inserting in decreasing order
    {	
  		b.insert(j); 
    }
    bool condB1;
	long LB = b.get_stream_size(); //test the function get_stream_size()
	condB1= (LB == n/0.1);
	assert(condB1 == true); 	
  	
  	
  	for (int m = 1; m <= 3; m++) //create 3 "random" sequences that holds their randomness every time runs the code
  	{
  		 if (m == 1)
  		 {
  		 	//cout << "sequence 1: " << endl;
  			 for (int i = 0; i <= n; i++)
   			 {
   			 	srand(i);
  				double rand_num=rand()%n + 0.5;
  				//cout << rand_num << " ";
  				c.insert(rand_num); //inserting float number from 0 to n
  			 }
  			 //cout << ""<<endl;
  			 bool condC1;
			 long LC = c.get_stream_size(); //test the function get_stream_size()
			 condC1= (LC == n+1);
			 assert(condC1 == true); 			 
  		}
  		
  		else if(m == 2)
  		{
  			 //cout << "sequence 2: " << endl;
  			  for (int i = 0; i <= n; i++)
   			 {
   			    srand(i^2);
  				double rand_num=rand()%n + 0.5;
  				//cout << rand_num << " ";
  				d.insert(rand_num); //inserting float number from 0 to n
  			 }  
  			 //cout << ""<<endl;
  			 bool condD1;
			 long LD = d.get_stream_size(); //test the function get_stream_size()
			 condD1= (LD == n+1);
			 assert(condD1 == true);  
  		}	
  		
  		else 
  		{	
  			//cout << "sequence 3: " << endl;
  			  for (int i = 0; i <= n; i++)
   			 {
   			 	srand(n-i);
  				double rand_num=rand()%n + 0.5;
  				//cout << rand_num << " ";
  				e.insert(rand_num); //inserting float number from 0 to n
  			 }  
  			 //cout <<""<<endl;
  			 bool condE1;
			 long LE = e.get_stream_size(); //test the function get_stream_size()
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
	//random floating number from MIN ~ MAX are needed !!!!!
	

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
  	  
  	  lower=(interval-0.06)*n;
  	  upper=(interval+0.06)*n;
  	  
  	  condA= ((lower<=quantA) && (upper>=quantA));
  	  //checking if quantile is within error range
  	  
  	  condB= ((lower<=quantB) && (upper >=quantB));
  	  //checking if quantile is within error range
  	  
  	  condC= ((lower<=quantC) && (upper>=quantC));
  	  condD= ((lower<=quantD) && (upper>=quantD));
  	  condE= ((lower<=quantE) && (upper>=quantE));
  	  //checking if quantile is within error range
  	  

  	  condF= ((quantF <= 1.0001*random_fix1) && (quantF >= 0.9999*random_fix1));
  	  condG= ((quantG <= 1.0001*random_fix2) && (quantG >= 0.9999*random_fix2));
  	  condH= ((quantH <= 1.0001*random_fix3) && (quantH >= 0.9999*random_fix3));
  	  
  	  
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
		QDigestDouble a(500);
		for(double i=1; i<=1000; i = i + 0.5)
		{
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
