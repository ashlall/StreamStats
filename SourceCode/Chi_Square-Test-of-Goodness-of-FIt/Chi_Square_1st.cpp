//One Sample Chi-Squared Test
#include<cassert>
#include "../Quantiles/GK.h"
#include <iostream>
#include <stdlib.h> 
#include<math.h>


double inverse_cmf(double x);
double NormalCDFInverse(double p);
double RationalApproximation(double t);

//double cdfNormal(double x,double mu,double sigma);
//double erf(double z);

void OneSample_GK(int N,int K)
{	
	GK Q(100);
	double chi_squared=0;	
	for (int i=1;i<=N;i++)
		Q.insert(i);
	
	double E=N/K;
	for (double i=1;i<=K;i++)
	{
		double l= inverse_cmf((i-1)/K);
		double u= inverse_cmf(i/K);
		cout<<l<<endl;
		double iA=Q.reverseQuantile(l,100);
		double iB=Q.reverseQuantile(u,100);
		double O=N*(iB-iA);
		double lambda= fabs(O-E);
		
		chi_squared=chi_squared+ ((lambda*lambda)/E);
	}		
	//cout<<chi_squared<<endl;
	
}
double inverse_cmf(double x)
{
	return NormalCDFInverse(x);
	
}

/* Adapted from John D.Cook, Singular value consulting */
double NormalCDFInverse(double p)
{
	 if (p <0.0 || p > 1.0)
	 {
	 	 cout<<"p is too large or small "<<p<<endl;
	 }
	 if (p < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -RationalApproximation( sqrt(-2.0*log(p)) );
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return RationalApproximation( sqrt(-2.0*log(1-p)) );
    }
}

double RationalApproximation(double t)
{
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) /
                (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
 
/*
Adapted from OneSampleKSTest.java.............

double cdfNormal(double x,double mu,double sigma)
{
	return 0.5 + 0.5 * erf((x - mu)/(sigma * sqrt(2.0)));
}
// erf function taken from:
    // http://introcs.cs.princeton.edu/java/21function/ErrorFunction.java.html
    // fractional error in math formula less than 1.2 * 10 ^ -7.
    // although subject to catastrophic cancellation when z in very close to 0
    // from Chebyshev fitting formula for erf(z) from Numerical Recipes, 6.2
double erf(double z)
{
	 double t = 1.0 / (1.0 + 0.5 * fabs(z));
        // use Horner's method
        double ans = 1 - t * exp( -z*z   -   1.26551223 +
				       t * ( 1.00002368 +
					     t * ( 0.37409196 + 
						   t * ( 0.09678418 + 
							 t * (-0.18628806 + 
							      t * ( 0.27886807 + 
								    t * (-1.13520398 + 
									 t * ( 1.48851587 + 
									       t * (-0.82215223 + 
										    t * ( 0.17087277))))))))));
        if (z >= 0) return  ans;
        else        return -ans;
	
}
*/

int main()
{	
	int N=10000,K=50;
	OneSample_GK(N,K);
	
	return 0;
}
