// Continuous Chi Squared test

// Initializes the variables used in the ChiSquareContinuous class.
// Input: m is a double and the amount of memory the sketch will use, q is an 
// integer and between 1 and 4, where if the user does not give q it will by 
// default be 1.
// Output: this is initialized as a ChiSquareContinuous, throws IndexError if 
// q is not between 1 and 4.
ChiSquareContinuous::ChiSquareContinuous(double m,int q)
{
	chi_squared = 0;
	upper_bins = new double;
	lower_bins = new double;
	switch(q)
	{
	case 1: memory = m/3;
		quantile_sketch = new GK(memory);
		break;
	case 2: //memory = m;
		//quantile_sketch = new QDigestDouble(memory);
		break;
	case 3: memory = m;
		quantile_sketch = new ReservoirSampling((int)memory);
		break;
	case 4:// memory = m;
		// quantile_sketch = new CMS((int)memory);
		break;
	default:
		throw IndexError();
	}	
}

// Deallocates the memory.
ChiSquareContinuous::~ChiSquareContinuous()
{	
	delete quantile_sketch;
	delete upper_bins;
	delete lower_bins;
}

// Inserts val into the quantile_sketch.
void ChiSquareContinuous::insert(double val)
{
	quantile_sketch->insert(val);
}

// Calculates the chi-squared statistic for a normal distribution.
// Input: 
double ChiSquareContinuous::calculate_statistic_ifNormal(int num_buckets, double mean, double SD)
{	
        int stream_size = quantile_sketch->get_stream_size();
	double expected_frequency = stream_size/num_buckets;
	delete upper_bins;
	delete lower_bins;
      	upper_bins = new double[num_buckets];
	lower_bins = new double[num_buckets];
	for (int i = 1; i <= num_buckets; i++)
	{
	        double lower_interval = normal_cdf_inverse(((double)i-1)/num_buckets, mean, SD);
	        double upper_interval = normal_cdf_inverse((double)i/num_buckets, mean, SD);
		
		double lower_value, upper_value;
		upper_bins[i] = upper_interval;
		lower_bins[i] = lower_interval;

		lower_value = (quantile_sketch->reverseQuantile(lower_interval, memory))/memory;
		upper_value = (quantile_sketch->reverseQuantile(upper_interval, memory))/memory;
		double observed_frequency = stream_size * (upper_value - lower_value);
		double lambda = fabs(observed_frequency - expected_frequency);
	        chi_squared = chi_squared + ((lambda*lambda)/expected_frequency);
	}		
	return chi_squared;
}

double ChiSquareContinuous::calculate_statistic(int num_buckets, double(*f)(double))
{		
	int stream_size = quantile_sketch->get_stream_size();
	double expected_frequency = stream_size/num_buckets;
	delete upper_bins;
	delete lower_bins;
	upper_bins = new double[num_buckets];
	lower_bins = new double[num_buckets];
	for (int i = 1; i <= num_buckets; i++)
	{
	        double lower_interval = (*f)(((double)i-1)/num_buckets);
	        double upper_interval = (*f)((double)i/num_buckets);
		upper_bins[i] = upper_interval;
		lower_bins[i] = lower_interval;
		double lower_value, upper_value;
	        lower_value = (quantile_sketch->reverseQuantile(lower_interval, memory))/memory;
		upper_value = (quantile_sketch->reverseQuantile(upper_interval, memory))/memory;
		
		double observed_frequency = stream_size * (upper_value - lower_value);
		double lambda = fabs(observed_frequency - expected_frequency);
		
		chi_squared=chi_squared+ ((lambda*lambda)/ expected_frequency);
	}		
	return chi_squared;	
}

double ChiSquareContinuous::two_sample_statistic(const ChiSquareContinuous& distribution_2, int num_buckets)
{
  QuantileSketch *quantile_sketch_2 = distribution_2.quantile_sketch;
  int stream_size_1 = quantile_sketch->get_stream_size();
  int stream_size_2 = quantile_sketch_2->get_stream_size();
  double frequency_1 = stream_size_1 / num_buckets;

  delete upper_bins;
  delete lower_bins;
  upper_bins = new double[num_buckets];
  lower_bins = new double[num_buckets];

  double constant_1 = sqrt(stream_size_2/stream_size_1);
  double constant_2 = sqrt(stream_size_1/stream_size_2);
  for (int i = 1; i <= num_buckets; i++)
  {
    double lower_interval = quantile_sketch->getQuantile(((int)i-1)/num_buckets);
    double upper_interval = quantile_sketch->getQuantile((int)i/num_buckets);
    upper_bins[i] = upper_interval;
    lower_bins[i] = lower_interval;

    double lower_value, upper_value;
    lower_value = (quantile_sketch_2->reverseQuantile(lower_interval, memory))/memory;
    upper_value = (quantile_sketch_2->reverseQuantile(upper_interval, memory))/memory;

    double frequency_2 = stream_size_2 * (upper_value - lower_value);
    double value = frequency_1 * constant_1 - frequency_2 * constant_2;
    chi_squared += (value * value) / (frequency_1 + frequency_2);
  }
  return chi_squared;
}

double* ChiSquareContinuous::get_lower()
{
	return lower_bins;
}

double* ChiSquareContinuous::get_upper()
{
	return upper_bins;
}

/*
Adapted from John D.Cook.
URL:: http://www.johndcook.com/blog/normal_cdf_inverse/

input: p(probability 0-1), mean, standard deviation
output: corresponding x value
*/
double ChiSquareContinuous::normal_cdf_inverse(double p, double mean, double SD)
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
        return -rational_approximation( sqrt(-2.0*log(p)))*SD + mean;
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return rational_approximation( sqrt(-2.0*log(1-p)))*SD + mean;
    }
}

double ChiSquareContinuous::rational_approximation(double t)
{
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) /
                (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
