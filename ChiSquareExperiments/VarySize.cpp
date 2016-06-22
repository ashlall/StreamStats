// VarySize.cpp
// Experiments that vary in stream_size, user inputs range, number of data repeats, and type/
// parameters of the distribution

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string.h>
#include "DataGenerator.cpp"
#include "../SourceCode/ChiSquare/ChiSquareContinuous.cpp"
using namespace std;

void name_file(char *str, char* lower, char* upper, char* repeats, char* distribution);

int main(int argc, char* argv[])
{
  if (argc < 7)
    throw ParameterError();

  double lower = atof (argv[1]);
  double upper = atof (argv[2]);
  int data_repeats = atoi (argv[3]);
  char distribution_type = *argv[4];
  double location = atof (argv[5]);
  double scale = atof (argv[6]);
  int seed;
  if (argc == 8)
    seed = atoi (argv[7]);
  else
  {
    seed = 1; // change to random based on time
  }
 

  int stream_size;
  double memory_percent = 1; // default, change?
  int num_buckets = 5; // default, change
  int num_sizes = 0, size = lower;
  while (size <= upper)
  {
    num_sizes++;
    size *= 10;
  }
  
  ofstream data_file;
  time_t timer = time(NULL);
  char str[100];
  name_file(str, argv[1], argv[2], argv[3], argv[4]);
  data_file.open(str);
  for (int i = 0; i < data_repeats; i++)
  {
    stream_size = lower;
    data_file << "Data repeat = " << i << endl;
    while (stream_size <= upper)
    {
      data_file << "stream_size = " << stream_size << endl;
      DataGenerator data(distribution_type, stream_size, seed, location, scale);
      double *stream = data.get_stream();

      // tests GK sketch
      ChiSquareContinuous sketch1(memory_percent * stream_size, 1); 
      for (int i = 0; i < stream_size; i++)
	sketch1.insert(stream[i]);

      double GK_stat = sketch1.calculate_statistic_ifNormal(num_buckets, location, scale); //FIX
      //double GK_stat = sketch1.calculate_statistic(num_buckets, ...);
      double *upper_interval = sketch1.get_upper();
      double *lower_interval = sketch1.get_lower();
      //int actual = data.get_stat_one_sample(num_buckets, upper_interval, lower_interval);
      //VarySize(lower, upper, stream);

      //data_file << "Real = " << actual << endl;
      data_file << "GK = " << GK_stat << endl;
      stream_size *= 10;
    }
    seed++; // changes seed for next repeat?
  }
  data_file.close();
  return 0;
}

void name_file(char *str, char* lower, char* upper, char* repeats, char* distribution)
{
  strcpy(str, "VarySize_");
  strcat(str, lower);
  strcat(str, "-");
  strcat(str, upper);
  strcat(str, "_");
  strcat(str, repeats);
  strcat(str, "-repeats_distribution-");
  strcat(str, distribution);
  strcat(str, "_");
  strcat(str, "_time"); // need to include the actual time                                         
  //  strcpy(str, timer);
  strcat(str, ".dat");
}
