//One Sample Chi-Squared Test
#include<cassert>
#include "../Quantiles/GK.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h> 

ChiSquare::ChiSquare(int n,int k,double m)
{
	N=n;
	K=k;
	Q=0;
	chi_squared=0;
	memory= (m/100)*N;
	quantile_GK=new GK((int)memory);
	
}

ChiSquare::ChiSquare(int q,int n,int k,double m)
{
	N=n;
	K=k;
	Q=q;
	chi_squared=0;
	memory= (m/100)*N;
	switch(Q)
	{
	case 1: quantile_GK=new GK((int)memory);
		break;
	case 2:// quantile_QD=new QDigestDouble(memory);
		break;
	case 3: //quantile_RS=new ReservoirSampling((int)memory);
		break;
	case 4:// quantile_CMS=new CMS((int)memory);
		break;
	default:
		cout<<" Incorrect Case. Valid inputs lie between 1 and 4"<<endl;
		cout<<"Error Message"<<endl;
		
	}
	
}

void ChiSquare::insert(double val)
{
	switch(Q)
	{
	case 1: quantile_GK->insert(val);
		break;
	case 2: //quantile_QD->insert(val);
		break;
	case 3: //quantile_CMS.insert(val);
		break;
	case 4: //quantile_RS->insert(val);
		break;
	default:
		quantile_GK->insert(val);
		
	}
}

double ChiSquare::calculate_statistic()
{	
	
	
	double E=N/K;
	for (double i=1;i<=K;i++)
	{
		double l= inverse_cmf((i-1)/K);
		double u= inverse_cmf(i/K);
		double iA,iB;
		switch(Q)
		{
		case 1:  iA=quantile_GK->reverseQuantile(l,100);
			 iB=quantile_GK->reverseQuantile(u,100);
			break;
		case 2: //iA=quantile_QD->reverseQuantile(l,100);
			//iB=quantile_QD->reverseQuantile(u,100);
			break;
		case 3: //iA=quantile_CMS->reverseQuantile(l,100);
			//iB=quantile_CMS->reverseQuantile(u,100);
			break;
		case 4: //iA=quantile_RS->reverseQuantile(l,100);
			//iB=quantile_RS->reverseQuantile(u,100);
			break;
		default:
			iA=quantile_GK->reverseQuantile(l,100);
			iB=quantile_GK->reverseQuantile(u,100);
		}
		double O=N*(iB-iA);
		double lambda= fabs(O-E);
		
		chi_squared=chi_squared+ ((lambda*lambda)/E);
	}		
}
double ChiSquare::inverse_cmf(double x)
{
	return 0;
}
