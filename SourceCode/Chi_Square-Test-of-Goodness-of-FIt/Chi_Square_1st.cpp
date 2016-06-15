//One Sample Chi-Squared Test
#include<cassert>
//#include "../Quantiles/ReservoirSampling.h"
#include "../Quantiles/GK.h"
//#include "../Quantiles/Q-Digest.h"
//#include "../Quantiles/QDigestDouble.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h> 
#include<iomanip> // Parametric manipulators. Used to set precision. 

ChiSquare::ChiSquare(double m)
{
	Q=0;
	chi_squared=0;
	quantile_GK=new GK((int)(m/3));
}

ChiSquare::ChiSquare(double m,int q)
{
	Q=q;
	chi_squared=0;
	memory= m;
	switch(Q)
	{
	case 1: quantile_GK=new GK((int)(memory/3));
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
ChiSquare::~ChiSquare()
{	
	switch(Q)
	{
	case 1: delete quantile_GK;
		break;
	case 2:// delete quantile_QD
		break;
	case 3: //delete quantile_RS;
		break;
	case 4:// delete quantile_CMS;
		break;
	default:
		delete quantile_GK;
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


double ChiSquare::calculate_statistic_ifNormal(int k, double mean, double SD)
{	
	
	K=k;
	N= quantile_GK -> get_stream_size();
	cout << "N: " <<endl;
	double E=N/K;
	for (double i=1;i<=K;i++)
	{
		double l= NormalCDFInverse_pub((i-1)/K, mean, SD);
		double u= NormalCDFInverse_pub(i/K, mean, SD);
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
	return chi_squared;
}

double ChiSquare::calculate_statistic(int k,double(*f)(double))
{	
	
	K=k;
	N= quantile_GK -> get_stream_size();
	double E=N/K;
	for (double i=1;i<=K;i++)
	{
		double l= (*f)((i-1)/K);
		double u= (*f)(i/K);
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
	return chi_squared;	
}


double ChiSquare :: NormalCDFInverse_pub(double p, double mean, double SD)
{
	return NormalCDFInverse(p, mean, SD);
}


/*
Adapted from John D.Cook.

input: p(probability 0-1), mean, standard deviation
output: corresponding x value
*/
double ChiSquare::NormalCDFInverse(double p, double mean, double SD)
{
    if (p <= 0.0 || p >= 1.0)
    {
       //throw an exception
    }
    
    if (p < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -RationalApproximation( sqrt(-2.0*log(p)))*SD + mean;
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return RationalApproximation( sqrt(-2.0*log(1-p)))*SD + mean;
    }
}

double ChiSquare::RationalApproximation(double t)
{
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) /
                (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
