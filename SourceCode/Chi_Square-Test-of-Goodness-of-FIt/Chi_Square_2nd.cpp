//Two Sample Chi-Squared Test
#include<iomanip> // Parametric manipulators. Used to set precision. 

// CHECK THE LESS K LOOP IN THE STATISTIC


ChiSquare2::ChiSquare2(double m)
{
	Q=0;
	chi_squared=0;
	memory=m;
	quantile1=new GK(memory);
	quantile2=new GK((memory);
}

ChiSquare2::ChiSquare2(double m,int q)
{
	Q=q;
	switch(Q)
	{
	case 1: memory=m;
		quantile1=new GK((int)(memory));
		quantile2=new GK((int)(memory));
		break;
	case 2:/*memory=m;
		quantile1=new QDigestDouble(memory);
		quantile2=new QDigestDouble(memory);*/
		break;
	case 3: memory=m;
		quantile1=new ReservoirSampling((int)memory);
		quantile2=new ReservoirSampling((int)memory);
		break;
	case 4: /*memory=m;
		quantile1=new CMS((int)memory);
		quantile2=new CMS((int)memory);*/
		break;
	default:
		cout<<" Incorrect Case. Valid inputs lie between 1 and 4"<<endl;
		cout<<"Error Message"<<endl;
	}
	
}
ChiSquare2::~ChiSquare2()
{		
		delete quantile1;
		delete quantile2;
}
void ChiSquare2::insertStreamOne(double val)
{
	
		quantile1->insert(val);
}

void ChiSquare2::insertStreamTwo(double val)
{
		quantile2->insert(val);
}
double ChiSquare2::calculate_statistic(int k)
{	
	
	K=k;
	N=quantile1-> get_stream_size();
	M=quantile2-> get_stream_size();
	double S=N/K;
	for (double i=1;i<K;i++)
	{
		double l= quantile1->getQuantile((i-1)/K);
		double u= quantile1->getQuantile(i/K);
		double iA,iB;
		iA=(quantile2->reverseQuantile(l,memory))/memory;
		iB=(quantile2->reverseQuantile(u,memory))/memory;
		double R=M*(iB-iA);
		chi_squared=chi_squared+ ((((S*sqrt(M/N)-R*sqrt(N/M))*(S*sqrt(M/N)-R*sqrt(N/M)))/ (S+R)));
	}		
	return chi_squared;	
}

