// DataGenerator.cpp

#include "DataGenerator.h"
#include <random>
#include <stdio.h>
#include <iostream>
using namespace std;

// Constructor, based on the parameters creates and holds a stream of data in
// an array
// Input: distribution_type is either N,U,P, or E, size is a positive integer
// Output: based on the distribution_type, location, and scale stream is filled
// with data, throws parameter error if size is negative or 0, and if 
// distribution_type is not one of the aforementioned characters
DataGenerator::DataGenerator(char distribution_type, int size, int seed, double location, double scale)
{
  if (size <= 0)
    throw ParameterError();
  stream_size = size;
  stream = new double[stream_size];
  std::default_random_engine generator(seed);
  if (distribution_type == 'N')
    {
      std::normal_distribution<double> distribution(location, scale); // mean, SD
      for (int i = 0; i < stream_size; i++)
	stream[i] = distribution(generator);
    }
  else if (distribution_type == 'U')
    {
      std::uniform_real_distribution<double> distribution(location, scale); // lower, upper bounds
      for (int i = 0; i < stream_size; i++)
	stream[i] = distribution(generator);
    }
  else if (distribution_type == 'P')
    {
      std::uniform_real_distribution<double> distribution(0.0, 1.0);
      for (int i = 0; i < stream_size; i++)
	stream[i] = location / std::pow(1.0 - distribution(generator), 1.0/scale);
    }
  else if (distribution_type == 'E')
    {
      std::uniform_real_distribution<double> distribution(0.0, 1.0);
      for (int i = 0; i < stream_size; i++)
	stream[i] = location - std::log(1 - distribution(generator))/scale;
    }
  else
    throw ParameterError();
}

// Returns the chi squared statistic for the one sample continuous test
// Input: num_buckets is a positive integer, upper_intervals and 
// lower_intervals are arrays of doubles generated by a ChiSquareContinuous
//  that had all the values from stream inserted
double DataGenerator::get_stat_one_sample(int num_buckets, double *upper_intervals, double *lower_intervals)
{
  if (num_buckets <= 0)
    throw ParameterError();
  double expected = (double)stream_size / num_buckets;
  double chi_squared = 0;
  for (int i = 1; i <= num_buckets; i++)
  { 
    double observed = 0;
    for (int j = 0; j < stream_size; j++)
    {
      if (stream[j] <= upper_intervals[i] && stream[j] >= lower_intervals[i])
	observed++;
    }
    chi_squared += (observed - expected) * (observed - expected) / expected;
  }
  return chi_squared;
}

// Returns the chi square statistic for the two sample continuous variation
// Input: num_buckets is positive, upper_intervals and lower_intervals are 
// arrays of doubles generated by a ChiSquareContinuous that had all the values
// from stream inserted and called two_sample_statistic with the stream from
// other
double DataGenerator::get_stat_two_sample(const DataGenerator& other, int num_buckets, double *upper_intervals, double *lower_intervals)
{
  if (num_buckets <= 0)
    throw ParameterError();
  double *stream2 = other.stream;
  int stream2_size = other.stream_size;
  double constant_1 = sqrt((double)stream2_size/stream_size);
  double constant_2 = sqrt((double)stream_size/stream2_size);
  double chi_squared = 0;
  for (int i = 0; i < num_buckets; i++)
  {
    double frequency1 = 0, frequency2 = 0;
    for (int j = 0; j < stream_size; j++)
    {
      if (stream[j] <= upper_intervals[i+1] && stream[j] >= lower_intervals[i+1])
	frequency1++;
    }
    for (int j = 0; j < stream2_size; j++)
    {
      if (stream2[j] <= upper_intervals[i+1] && stream2[j] >= lower_intervals[i+1])
	frequency2++;
    }
    double lambda = frequency1 * constant_1 - frequency2 * constant_2;
    chi_squared += (lambda * lambda) / (frequency1 + frequency2);
  }
  return chi_squared;
}
