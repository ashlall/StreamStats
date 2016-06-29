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

 double LOG_SQRT_PI = log(sqrt(M_PI));
 double I_SQRT_PI = 1 / sqrt(M_PI);
 int MAX_X = 20; // max value to represent exp(x)

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
double ex(double);
double poz(double);
double pochisq(double, int);

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

/* POCHISQ -- probability of chi-square value
        Adapted from:
        Hill, I. D. and Pike, M. C. Algorithm 299
        Collected Algorithms for the CACM 1967 p. 243
        Updated for rounding errors based on remark in
        ACM TOMS June 1985, page 185
    */
double pochisq(double x, int df)
   {
        double a, s;
        double e, c, z;
 
        if (x <= 0.0 || df < 1) {
            return 1.0;
        }
        a = 0.5 * x;
        bool even = (df & 1) == 0;
        double y = 0;
        if (df > 1) {
            y = ex(-a);
        }
        s = (even ? y : (2.0 * poz(-sqrt(x))));
        if (df > 2) {
            x = 0.5 * (df - 1.0);
            z = (even ? 1.0 : 0.5);
            if (a > MAX_X) {
                e = (even ? 0.0 : LOG_SQRT_PI);
                c = log(a);
                while (z <= x) {
                    e = log(z) + e;
                    s += ex(c * z - a - e);
                    z += 1.0;
                }
                return s;
            } else {
                e = (even ? 1.0 : (I_SQRT_PI / sqrt(a)));
                c = 0.0;
                while (z <= x) {
                    e = e * (a / z);
                    c = c + e;
                    z += 1.0;
                }
                return c * y + s;
            }
        } else {
            return s;
        }
    }
 
double poz(double z)
{
        double y, x, w;
        double Z_MAX = 6.0; // Maximum meaningful z value 
        if (z == 0.0) {
            x = 0.0;
        } else {
            y = 0.5 * abs(z);
            if (y >= (Z_MAX * 0.5)) {
                x = 1.0;
            } else if (y < 1.0) {
                w = y * y;
                x = ((((((((0.000124818987 * w
                        - 0.001075204047) * w + 0.005198775019) * w
                        - 0.019198292004) * w + 0.059054035642) * w
                        - 0.151968751364) * w + 0.319152932694) * w
                        - 0.531923007300) * w + 0.797884560593) * y * 2.0;
            } else {
                y -= 2.0;
                x = (((((((((((((-0.000045255659 * y
                        + 0.000152529290) * y - 0.000019538132) * y
                        - 0.000676904986) * y + 0.001390604284) * y
                        - 0.000794620820) * y - 0.002034254874) * y
                        + 0.006549791214) * y - 0.010557625006) * y
                        + 0.011630447319) * y - 0.009279453341) * y
                        + 0.005353579108) * y - 0.002141268741) * y
                        + 0.000535310849) * y + 0.999936657524;
            }
        }
        return z > 0.0 ? ((x + 1.0) * 0.5) : ((1.0 - x) * 0.5);
   }
 
double ex(double x) {
        return (x < -MAX_X) ? 0.0 : exp(x);
    }


