/*
Calculate the p-value of chi-square goodness-of-fit test/

Modified from the Github https://github.com/polyactis/repos/blob/7b402496aae81665e6a915b5021b94d56e034c9d/variation/trunk/src/CLASS2_v3.cpp

But we noticed that the code below is really similar to the textbook Numerical Recipe, the art of scientific computing. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

int numind;
/*
routines :
  pnormal
	input : double Z
	output : double p-value
  ipnormal
	input : double p-value
	output : double Z
  pchisq
	input : double x, int df
	output : double p-value
*/

/************************************************************************
	
	pnormal( Z ) = p-value :
	  compute p_value s.t. integral [-oo, Z] of normal pdf
				                 / Z
                        1       |       -x*x/2
          p-value = ----------- |      e       dx
                    sqrt(2 pi)  |
                               /-oo
	ipnormal( p-value ) = Z :
								 / Z
                        1       |       -x*x/2
          p-value = ----------- |      e       dx
                    sqrt(2 pi)  |
                               /-oo
  
	include math.h
	include dist.h
************************************************************************/

double gammp( double, double );
void gser( double, double );
void gcf( double, double );
double gammln( double );
double pchisq( double, int );
// variable for pvalue
static double gamser, gammcf, gln;

void gser(  double a, double x )
{
	int n, ITMAX=100;
	double sum, del, ap, eps = 3.0e-7;
	gln = gammln( a );
	if( x <= 0.0 )
	{
		if( x < 0.0 )
		{
			printf( "x less than 0 in routine gser" );
			exit( 1 );
		}
		gamser = 0.0;
		return;
	}
	else
	{
		ap = a;
		del = sum = 1.0 / a;

		for( n = 1; n <= ITMAX; n++ )
		{
			++ap;
			del *= x / ap;
			sum += del;
			if( fabs( del ) < fabs( sum ) * eps)
			{
				gamser = sum * exp( -x + a * log( x ) - gln );
				return;
			}
		}
		printf( "Error:a too large, ITMAX too small in routine gser" );
		exit( 1 );
	}
	return;
//	returns the incomplete gamma function P(a,x) evaluated by its series reprentation
//  as gamser, also returns ln(gamma(a) as gln;
//  the incomplete gamma function P(a,x) is efined:
//		P(a,x) = 1/gamma(a)* integral(0,x) exp(-t)t^(a-1) dt (a>0);
//	it has the limiting values P(a,0)=0 and P(a,infinity)=1;
//  it relates many cumulative probability functions, such as chi-square;
}

double gammp( double a, double x )
{

	// x = chisquare, a = df/2
	if( x < 0.0 || a <= 0.0 )
	{
		printf( "error: invalid arguments in routine gammp" );
		exit( 1 );
	}
	if( x < ( a + 1.0 ) )
	{
		gser( a, x );
		return( gamser );
	}
	else
	{
		gcf( a, x );
		return( 1.0 - gammcf );
	}
//	returns the incomplete gamma function P(a,x);
}



void gcf(  double a, double x )
{
	int i, ITMAX=100;
	double an, b, c, d, del, h, eps = 3.0e-7, fpmin = 1.0e-30;
	gln = gammln( a );
	b = x + 1.0 - a;
	c = 1.0 / fpmin;
	d = 1.0 / b;
	h = d;
	for( i = 1; i < ITMAX; i++ )
	{
		
		an = -i * ( i-a );
		b += 2.0;
		d = an * d + b;
		if( fabs( d ) < fpmin )
			d = fpmin;
		c = b + an / c;
		if( fabs( c ) < fpmin )
			c = fpmin;
		d = 1.0 / d;
		del = d * c;
		h *= del;
		if( fabs( del-1.0 ) < eps )
			break;
	}
	if( i > ITMAX )
	{
		printf( "Error:a too large, ITMAX too small in routine gser" );
		exit( 1 );
	}
	gammcf = exp( -x + a * log( x ) - gln ) * h;
//	returns the incomplete gamma function P(a,x) evaluated by its continued fraction
//	reprentation as gammcf, also returns ln(gamma(a) as gln;
//  the definition of incomplete function P(a,x) can see routine gser();
}


double gammln( double xx )
{
	double x, y, tmp, ser;
	static double cof[6]={76.18009172947146,-86.50532032941677,24.01409824083091,
		-1.231739572450155,0.1208650973866179e-2,-0.5395239384953e-5};
	int j;
	
	y = x = xx;
	tmp = x + 5.5;
	tmp -= ( x + 0.5 ) * log( tmp );
	ser = 1.000000000190015;
	for( j = 0; j < 6; j++ )
		ser += cof[ j ] / ++y;
	return( -tmp + log( 2.5066282746310005 * ser / x ) );
//	Returns the logarithmic value of gamma function of xx for xx>0;
//  the gamma function is defined by the intergral:
// 		gamma(z)=inter(0,infinity) t^(z-1)epx(-t)dt;
//  n!=gamma(n+1);
}

double pchisq( double x, int df )
{
	// df = degrees of freedom
	// x = chi square value
	return( gammp( df/2.0, x/2.0 ) );
//	return the culmulative function of chi-square distribuition
//  with df freedom;
}