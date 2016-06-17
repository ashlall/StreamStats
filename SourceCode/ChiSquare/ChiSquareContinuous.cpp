//One Sample Chi-Squared Test
#include<iomanip> // Parametric manipulators. Used to set precision. 

ChiSquare::ChiSquare(double m,int q)
{
	Q=q;
	chi_squared=0;

	//UpperBins= new double[1];
	//LowerBins=new double[1];

	switch(Q)
	{
	case 1: memory=m;
		quantile=new GK(memory);
		break;
	case 2: //memory=m;
		//quantile=new QDigestDouble(memory);
		break;
	case 3: memory=m;
		quantile=new ReservoirSampling((int)memory);
		break;
	case 4:// memory=m;
		// quantile_CMS=new CMS((int)memory);
		break;
	default:
		cout<<" Incorrect Case. Valid inputs lie between 1 and 4"<<endl;
		cout<<"Error Message"<<endl;
	}
	
}
ChiSquare::~ChiSquare()
{	
	delete quantile;
	delete UpperBins;
	delete LowerBins;
}
void ChiSquare::insert(double val)
{
	quantile->insert(val);
}

double ChiSquare::calculate_statistic_ifNormal(int k, double mean, double SD)
{	
	K=k;
	N= quantile -> get_stream_size();
	double E=N/K;

	UpperBins= new double[k];
	LowerBins=new double[k];
	for (double i=1;i<=K;i++)
	{
		double l= NormalCDFInverse_pub((i-1)/K, mean, SD);
		double u= NormalCDFInverse_pub(i/K, mean, SD);
		
		double iA,iB;
		UpperBins[(int)i]= u;
		LowerBins[(int)i]= l;

		 iA= (quantile->reverseQuantile(l,memory))/memory;
		 iB= (quantile->reverseQuantile(u,memory))/memory;
		double O=N*(iB-iA);
		double lambda= fabs(O-E);

	    chi_squared=chi_squared+ ((lambda*lambda)/E);
	}		
	return chi_squared;
}

double ChiSquare::calculate_statistic(int k,double(*f)(double))
{	
	
	K=k;
	N= quantile-> get_stream_size();
	double E=N/K;
	UpperBins= new double[k];
	LowerBins=new double[k];
	for (double i=1;i<=K;i++)//fix this
	{
		double l= (*f)((i-1)/K);
		double u= (*f)(i/K);
		UpperBins[(int)i]= u;
		LowerBins[(int)i]= l;
		double iA,iB;
		iA=(quantile->reverseQuantile(l,memory))/memory;
		iB=(quantile->reverseQuantile(u,memory))/memory;
		
		double O=N*(iB-iA);
		double lambda= fabs(O-E);
		
		chi_squared=chi_squared+ ((lambda*lambda)/E);
	}		
	return chi_squared;	
}

double* ChiSquare::GetLower()
{
	return LowerBins;
}

double* ChiSquare::GetUpper()
{
	return UpperBins;
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
    if (p < 0.0 || p > 1.0)
    {
       //throw an exception
    }
    
    if(p==0)
    	    return 0;
    
    if(p==1)
    	    return 99999999;
    
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