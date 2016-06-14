/*
Need to fix !!!  Not complete yet

After fixing, dont forget to put the compile command into makefile !!!
*/

#include<cassert>
#include "../SourceCode/Quantiles/CMS.h"
#include <iostream>

void test_CMS()
{
	int width = 1000;
	int depth = 1000;
	
	int diff = 10;
	
	long quantA,quantB,quantC,quantD,quantE,quantF,quantG,quantH;
	bool condA,condB,condC,condD,condE,condF,condG,condH;
	double upper,lower;
	int n=10000;
	
	/*	Extrem case when n = 1
	
	int random_fix1 = rand()% RAND_MAX;
    cout << "random_fix1: " << random_fix1 <<endl;
    int random_fix2 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix2 <<endl;
    int random_fix3 = rand()% RAND_MAX;
    //cout << "random_fix2: " << random_fix3 <<endl;
    */
    
	CMS a(width,depth); 
	CMS b(width,depth);
	CMS c(width,depth);
	CMS d(width,depth);
	CMS e(width,depth);
	
	/*	Extrem case when n = 1
	
	CMS f(width,depth);
	CMS g(width,depth);
	CMS h(width,depth);
  	*/
  	
	for (int i=0;i <= n;i++) //inserting in increasing order
	{
		a.update(i,diff); 
	}
	
	for (int i = n; i >= 1; i--) //inserting in desceding order
    {
  		b.update(i,diff); 
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
  				c.update(rand_num,diff);  //inserting float number from 0 to n
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
  				d.update(rand_num,diff); //inserting float number from 0 to n
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
  				e.update(rand_num,diff); //inserting float number from 0 to n
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
  	  
  	  quantA=a.pointEstimate(interval); //getting quantile for each probability interval
  	  quantB=b.pointEstimate(interval);//getting quantile for each probability interval
  	  quantC=c.pointEstimate(interval);//getting quantile for each probability interval
  	  quantD=d.pointEstimate(interval);
  	  quantE=e.pointEstimate(interval);
  	  
	  /*	Extrem case when n = 1
	  
  	  quantF=f.getQuantile(interval);
  	  quantG=g.getQuantile(interval);
  	  quantH=h.getQuantile(interval);
  	  */
  	  
  	  lower=(interval-0.08)*n;
  	  upper=(interval+0.08)*n;
  	  
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
	CMS a(1000,1000);
	for(int i=1; i<=10000000; i++)
	{
		a.update(i + 0.13416435, 10);
	}
	/*
	cout << "0.1: "<<a.pointEstimate(0.1) << endl;
	cout << "0.1: "<<a.pointEstimate(0.2) << endl;
	cout << "0.3: "<<a.pointEstimate(0.3) << endl;
	cout << "0.4: "<<a.pointEstimate(0.4) << endl;
	cout << "median:" << a.pointEstimate(0.5) << endl;
	cout << "0.6: "<<a.pointEstimate(0.6) << endl;
	cout << "0.7: "<<a.pointEstimate(0.7) << endl;
	cout << "0.8: "<<a.pointEstimate(0.8) << endl;
	cout << "0.9: "<<a.pointEstimate(0.9) << endl;
	cout << "1: "<<a.pointEstimate(1) << endl;
	*/
}

int main()
{
  test_CMS();
  quicktest();
  return 0;
}
