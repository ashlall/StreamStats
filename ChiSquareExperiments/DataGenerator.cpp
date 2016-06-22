// DataGenerator.cpp

#include "DataGenerator.h"
#include <random>
#include <stdio.h>

DataGenerator::DataGenerator(char distribution_type, int size, int seed, double location, double scale)
{
  stream_size = size;
  location_ = location;
  scale_ = scale;
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
      std::exponential_distribution<double> distribution(location); // mean, must be positive
      for (int i = 0; i < stream_size; i++)
	stream[i] = distribution(generator);
    }
  else
    throw ParameterError();
}

