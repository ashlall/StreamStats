// Continuous Chi Squared test

#include "ChiSquareContinuous.h"

// Initializes the variables used in the ChiSquareContinuous class.
// Input: memory_ is the amount of memory the sketch will use, num is an 
// integer between 1 and 4 that decides which quantile sketch the algorithm 
// will use, where if the user does not give q it will by default be 1.
// Output: this is initialized as a ChiSquareContinuous, throws IndexError if 
// q is not between 1 and 4.
ChiSquareContinuous::ChiSquareContinuous(double memory_,int num)
{
  chi_squared = 0;
  upper_bins = new double;
  lower_bins = new double;
  memory = memory_;
  switch(num)
  {
  case 1: 
    memory = memory_/3;

    quantile_sketch = new GK(memory);
    break;
  case 2:
    quantile_sketch = new QDigestDouble(memory);
    break;
  case 3: 
    quantile_sketch = new ReservoirSampling((int)memory);
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
// Input: num_buckets is the number of buckets the data is divided into, mean 
// is the mean for the normal distribution, and SD is the standard deviation 
// for the normal distribution.
// Output: Returns the chi-squared statistic for the observed quantile_sketch 
// compared to the expected normal distribution.
double ChiSquareContinuous::calculate_statistic_ifNormal(int num_buckets, double mean, double SD)
{	
  int stream_size = quantile_sketch->get_stream_size();
  double expected_frequency = stream_size/num_buckets;
  
  // Reallocates the memory for upper_bins and lower_bins.
  delete upper_bins;
  delete lower_bins;
  upper_bins = new double[num_buckets+1];
  lower_bins = new double[num_buckets+1];
  for (int i = 1; i <= num_buckets; i++)
  {
    // Finds the upper and lower values from the normal distribution that
    // mark the interval, or bin.
    double lower_interval = normal_cdf_inverse(((double)i-1)/num_buckets, mean, SD);
    double upper_interval = normal_cdf_inverse((double)i/num_buckets, mean, SD);

    upper_bins[i] = upper_interval;
    lower_bins[i] = lower_interval;

    // Finds the upper and lower quantiles from the quantile_sketch at the
    // lower_interval and upper_interval values.
    double lower_value, upper_value;
    lower_value = (quantile_sketch->reverseQuantile(lower_interval, memory))/memory;
    upper_value = (quantile_sketch->reverseQuantile(upper_interval, memory))/memory;

    double observed_frequency = stream_size * (upper_value - lower_value);
    double lambda = fabs(observed_frequency - expected_frequency);
    chi_squared = chi_squared + ((lambda*lambda)/expected_frequency);
  }		
  return chi_squared;
}

// Calculates and returns the chi-squared statistic with the given distribution
// Input: num_buckets is the number of bins the data is divided into, 
// distribution is a cumulative distribution function that computes the reverse
// lookup for any inputed percent, distribution can be for any distibution,
// however the user must write it.
// Output: Returns the chi-squared statistic where quantile_sketch is the 
// observed data and distribution is the expected data.
double ChiSquareContinuous::calculate_statistic(int num_buckets, double(ChiSquareContinuous::*distribution)(double, double, double), double location, double scale)
{		
  int stream_size = quantile_sketch->get_stream_size();
  double expected_frequency = stream_size/num_buckets;

  // Reallocates the memory for upper_bins and lower_bins
  delete upper_bins;
  delete lower_bins;
  upper_bins = new double[num_buckets+1];
  lower_bins = new double[num_buckets+1];

  for (int i = 1; i <= num_buckets; i++)
  {
    // Finds the upper and lower values from distribution that mark the bin.
    double lower_interval = (this->*distribution)(((double)i-1)/num_buckets, location, scale);
    double upper_interval = (this->*distribution)((double)i/num_buckets, location, scale);

    upper_bins[i] = upper_interval;
    lower_bins[i] = lower_interval;

    // Finds the upper and lower quantiles from quantile_sketch that correspond
    // to lower_interval and upper_interval.
    double lower_value, upper_value;
    lower_value = (quantile_sketch->reverseQuantile(lower_interval, memory))/memory;
    upper_value = (quantile_sketch->reverseQuantile(upper_interval, memory))/memory;
		
    double observed_frequency = stream_size * (upper_value - lower_value);
    double lambda = fabs(observed_frequency - expected_frequency);
    chi_squared=chi_squared+ ((lambda*lambda)/ expected_frequency);
  }		
  return chi_squared;	
}

double ChiSquareContinuous::calculate_statistic_ifUniform(int num_buckets, double location, double scale)
{
  return calculate_statistic(num_buckets, &ChiSquareContinuous::uniform_cdf_inverse, location, scale);
}

double ChiSquareContinuous::calculate_statistic_ifPareto(int num_buckets, double location, double scale)
{
  return calculate_statistic(num_buckets, &ChiSquareContinuous::pareto_cdf_inverse, location, scale);
}

double ChiSquareContinuous::calculate_statistic_ifExponential(int num_buckets, double location, double scale)
{
  return calculate_statistic(num_buckets, &ChiSquareContinuous::exponential_cdf_inverse, location, scale);
}

// Computes and returns the chi-squared statistic compared to another 
// distribution, also known as the two-sample continuous test.
// Input: distribution_2 the second stream of data, num_buckets is the number 
// of bins the data is broken into.
// Output: Returns the chi-squared statistic where quantile_sketch and distribution_2 are the two sets of data
double ChiSquareContinuous::two_sample_statistic(const ChiSquareContinuous& distribution_2, int num_buckets)
{
  QuantileSketch *quantile_sketch_2 = distribution_2.quantile_sketch;
  int stream_size_1 = quantile_sketch->get_stream_size();
  int stream_size_2 = quantile_sketch_2->get_stream_size();
  double frequency_1 = stream_size_1 / num_buckets;

  // Reallocates the memory for upper_bins and lower_bins
  delete upper_bins;
  delete lower_bins;
  upper_bins = new double[num_buckets+1];
  lower_bins = new double[num_buckets+1];

  double constant_1 = sqrt((double)stream_size_2/stream_size_1);
  double constant_2 = sqrt((double)stream_size_1/stream_size_2);
  for (int i = 1; i <= num_buckets; i++)
  {
    // Finds the upper and lower values from quantile_sketch that mark the bin.
    double lower_interval = quantile_sketch->getQuantile(((double)i-1)/num_buckets);
    //cout << "lower interval: " << lower_interval << endl;
    double upper_interval = quantile_sketch->getQuantile((double)i/num_buckets);
    
    upper_bins[i] = upper_interval;
    lower_bins[i] = lower_interval;
    //cout << "lower_interval: "<< lower_interval << "   " << "upper_interval: "<<upper_interval<<endl;

    // Finds the upper and lower quantiles from quantile_sketch_2 that 
    // correspond to lower_interval and upper_interval. 
    double lower_value, upper_value;
    lower_value = (quantile_sketch_2->reverseQuantile(lower_interval, memory))/memory;
    upper_value = (quantile_sketch_2->reverseQuantile(upper_interval, memory))/memory;
    //cout << "lower and upper value: " << lower_value << " " << upper_value << endl;
    // Calculates the chi-squared statistic with an adjusted formula for the 
    // two-sample case.
    double frequency_2 = stream_size_2 * (upper_value - lower_value);
    double value = frequency_1 * constant_1 - frequency_2 * constant_2;
    chi_squared += (value * value) / (frequency_1 + frequency_2);
    //cout << "F1: " <<frequency_1 << "  " << "F2: " << frequency_2 <<endl;
  }
  return chi_squared;
}

// Returns the array lower_bins.
double* ChiSquareContinuous::get_lower()
{
  return lower_bins;
}

// Returns the array upper_bins.
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
double ChiSquareContinuous::normal_cdf_inverse(double p, double mean, double SD){
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

double ChiSquareContinuous::uniform_cdf_inverse(double percent, double location, double scale)
{
  return location + (scale - location) * percent;
}

double ChiSquareContinuous::pareto_cdf_inverse(double percent, double location, double scale)
{
  return location / pow(1 - percent, 1 / scale);
}

double ChiSquareContinuous::exponential_cdf_inverse(double percent, double location, double scale)
{
  return location - log(1 - percent) / scale;
}

double ChiSquareContinuous::rational_approximation(double t)
{
  // Abramowitz and Stegun formula 26.2.23.
  // The absolute value of the error should be less than 4.5 e-4.
  double c[] = {2.515517, 0.802853, 0.010328};
  double d[] = {1.432788, 0.189269, 0.001308};
  return t - ((c[2]*t + c[1])*t + c[0]) / (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
