// VarySize.cpp
// Experiments that vary in stream_size, user inputs range, number of data repeats, and type/
// parameters of the distribution
// TODO: write functions to calculate statistic for all distributions - right now only works for 
// normal distribution, segfaulting at times, not sure why

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string.h>
#include "DataGenerator.cpp"
#include "../SourceCode/ChiSquare/ChiSquareContinuous.cpp"
using namespace std;

double get_estimate(ChiSquareContinuous *quantile_sketch, char distribution_type, int num_buckets, double location, double scale);
void name_file(char *str, char* lower, char* upper, char* repeats, char* distribution, int extra);

int main(int argc, char* argv[])
{
  if (argc < 8)
    throw ParameterError();

  double lower = atof (argv[1]);
  double upper = atof (argv[2]);
  int data_repeats = atoi (argv[3]);
  char distribution_type = *argv[4];
  double location = atof (argv[5]);
  double scale = atof (argv[6]);
  int all_quantiles = atoi (argv[7]);
  int seed;
  if (argc == 9)
    seed = atoi (argv[8]);
  else
  {
    seed = 1; // change to random based on time
  }
 

  int stream_size;
  double memory_percent = 0.1; // default, change?
  int num_buckets = 45; // default, change
  int num_sizes = 0, size = lower;
  while (size <= upper)
  {
    num_sizes++;
    size *= 10;
  }

  double actual_values[data_repeats][num_sizes];
  double GK_values[data_repeats][num_sizes];
  double QD_values[data_repeats][num_sizes];
  double RS_values[data_repeats][num_sizes];

  ofstream data_file;
  char str[150];
  name_file(str, argv[1], argv[2], argv[3], argv[4],0);
  data_file.open(str);
  data_file << "Distribution: " << distribution_type << ", location = " << location << ", scale = " << scale << endl;
  for (int i = 0; i < data_repeats; i++)
  {
    stream_size = lower;
    int j = 0;
    data_file << "Data repeat = " << i << endl;
    while (stream_size <= upper)
    {
      data_file << "stream_size = " << stream_size << endl;
      DataGenerator data(distribution_type, stream_size, seed, location, scale);
      double *stream = data.get_stream();

      // computes GK estimate
      ChiSquareContinuous sketch1(memory_percent * stream_size, 1); 
      for (int i = 0; i < stream_size; i++)
	sketch1.insert(stream[i]);
      double GK_stat = get_estimate(&sketch1, distribution_type, num_buckets, location, scale);
      GK_values[i][j] = GK_stat;
      data_file << "GK = " << GK_stat << endl;

      if (all_quantiles)
      {
	// computes QDigest estimate
	ChiSquareContinuous sketch2(memory_percent * stream_size, 2);
	for (int i = 0; i < stream_size; i++)
	  sketch2.insert(stream[i]);
	double QD_stat = get_estimate(&sketch2, distribution_type, num_buckets, location, scale);
	QD_values[i][j] = QD_stat;
        data_file << "QDigest = " << QD_stat << endl;

	// computes ReservoirSampling estimate
	ChiSquareContinuous sketch3(memory_percent * stream_size, 3);
	for (int i = 0; i < stream_size; i++)
	  sketch3.insert(stream[i]);
	double RS_stat = get_estimate(&sketch3, distribution_type, num_buckets, location, scale);
	RS_values[i][j] = RS_stat;
        data_file << "Reservoir Sampling = " << RS_stat << endl;
      }

      // computes actual statistic
      double *upper_interval = sketch1.get_upper();
      double *lower_interval = sketch1.get_lower();
      double actual = data.get_stat_one_sample(num_buckets, upper_interval, lower_interval);
      actual_values[i][j] = actual;

      data_file << "Real = " << actual << endl;

      stream_size *= 10;
      j++;
    }
    seed++; // changes seed for next repeat?
  }
  data_file.close();

  // writes data into tab deliminated file
  name_file(str, argv[1], argv[2], argv[3], argv[4], 1);
  data_file.open(str);
  for (int i = 0; i < num_sizes; i++)
    {
      for (int j = 0; j < data_repeats; j++)
	data_file << actual_values[j][i] << " \t";
    }
  data_file << endl;
  for (int i = 0; i < num_sizes; i++)
    {
      for(int j = 0; j <data_repeats; j++)
        data_file << GK_values[j][i] << " \t";
    }
  data_file << endl;
  if (all_quantiles)
  {
    for (int i = 0; i < num_sizes; i++)
      {
	for(int j = 0; j <data_repeats; j++)
	  data_file << QD_values[j][i] << " \t";
      }
    data_file << endl;
    for (int i = 0; i < num_sizes; i++)
      {
	for(int j = 0; j <data_repeats; j++)
	  data_file << RS_values[j][i] << " \t";
      }
    data_file << endl;
  }
  data_file.close();
  return 0;
}

// Fix for other distributions!!!
double get_estimate(ChiSquareContinuous *quantile_sketch, char distribution_type, int num_buckets, double location, double scale)
{
  if (distribution_type == 'N')
    return quantile_sketch->calculate_statistic_ifNormal(num_buckets, location, scale);
  else if (distribution_type == 'U')
    return quantile_sketch->calculate_statistic_ifUniform(num_buckets, location, scale);
  else if (distribution_type == 'P')
    return quantile_sketch->calculate_statistic_ifPareto(num_buckets, location, scale);
  else
    return quantile_sketch->calculate_statistic_ifExponential(num_buckets, location, scale);
}

void name_file(char *str, char* lower, char* upper, char* repeats, char* distribution, int extra)
{
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%m-%d-%Y.%X", &tstruct);

  strcpy(str, "VarySize_");
  strcat(str, lower);
  strcat(str, "-");
  strcat(str, upper);
  strcat(str, "_");
  strcat(str, repeats);
  strcat(str, "-repeats_dist-");
  strcat(str, distribution);
  strcat(str, "_");
  strcat(str, buf);
  if (extra)
    strcat(str, "_table");
  strcat(str, ".dat");
}
