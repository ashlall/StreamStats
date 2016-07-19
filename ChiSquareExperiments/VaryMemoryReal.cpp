// VaryMemoryReal.cpp
// runs tests on real data inputed from a file while varying memory

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cmath>
#include <random>
#include "../SourceCode/ChiSquare/ChiSquareContinuous.cpp"

void name_file(char *str, char* argv[], int extra);

// Runs experiments with one inputed data set and varies the memory
// Input: takes 5 command line arguments, lower and upper fraction of memory,
// names of files the data are in, and number of bins
// Output: creates 4 files, the log file holds all the data generated. the tabl
// file holds the pvalues deliminated by tabs, the extra file holds all the 
// calculated statistics. and the pvalue holds the actual and estimated pvalues
int main(int argc, char* argv[])
{
  if (argc < 6)
  {
    cout << "usage: VaryMemoryReal lower-memory upper-memory filename1 filename2 num_bins\n";
    exit(1);
  }

  double lower = atof(argv[1]), upper = atof(argv[2]);
  char *filename1 = argv[3], *filename2 = argv[4];
  int num_buckets = atoi(argv[5]);

  if (lower <=0 || upper <= 0)
  {
    cout << "The memory must be greater than 0.\n";
    exit(1);
  }
  if (num_buckets <= 0)
  {
    cout << "The number of buckets must be greater than 0.\n";
    exit(1);
  }

  // finds the number of times the experiment will run
  double memory_percent;
  int repeats = 0;
  double mem = lower;
  while (mem <= (upper + 0.0000001)) // accounts for rounding error
  {
    repeats++;
    mem *= sqrt(10);
  }

  double actual_values[repeats];
  double GK_values[repeats];
  double QD_values[repeats];
  double RS_values[repeats];
  double percents[repeats];
  std::vector<double> data1, data2;

  // creates and initializes the log file
  ofstream data_file;
  char str[100];
  name_file(str, argv, 0);
  data_file.open(str);
  ifstream input_file;
  char output[100];
  int stream_size1 = 0, stream_size2 = 0;

  std::default_random_engine generator(1);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  input_file.open(filename1);
  while (!input_file.eof())
  {
    input_file >> output;
    data1.push_back(atof(output) + (distribution(generator) * 0.000000001));
    stream_size1++;
  }
  input_file.close();

  input_file.open(filename2);
  while (!input_file.eof())
  {
    input_file >> output;
    data2.push_back(atof(output) + (distribution(generator) * 0.000000001));
    stream_size2++;
  }
  input_file.close();

  data_file << filename1 << endl << filename2 << endl;
  data_file << "num_buckets: " << num_buckets << endl;
  data_file << "stream 1 size: " << stream_size1 << endl;
  data_file << "stream 2 size: " << stream_size2 << endl;
  memory_percent = lower;
  int i = 0;
  while (memory_percent <= (upper + 0.00000001)) //accounts for rounding
  {
    data_file << "memory percent: " << memory_percent << endl;
    percents[i] = memory_percent;
    int sample_size1 = memory_percent * stream_size1;
    int sample_size2 = memory_percent * stream_size2;

    // calculates GK statistic
    ChiSquareContinuous GK_sketch1(sample_size1,1);
    for (std::vector<double>::iterator j = data1.begin(); j != data1.end();j++)
      GK_sketch1.insert(*j);
    ChiSquareContinuous GK_sketch2(sample_size2,1);
    for (std::vector<double>::iterator j = data2.begin(); j != data2.end();j++)
      GK_sketch2.insert(*j);
    
    double GK_stat = GK_sketch1.two_sample_statistic(GK_sketch2, num_buckets);
    GK_values[i] = GK_stat;
    data_file << "GK = " << GK_stat << endl;
    cout << 1 << endl;
    // calculates real statistic
    double *upper_intervals = GK_sketch1.get_upper();
    double *lower_intervals = GK_sketch1.get_lower();
    double constant_1 = sqrt((double)stream_size2/stream_size1);
    double constant_2 = sqrt((double)stream_size1/stream_size2);
    double chi_squared = 0;
    cout << 2 << endl;
    for (int i = 0; i < num_buckets; i++)
    {
      cout << 3 << endl;
      double frequency1 = 0, frequency2 = 0;
      cout << 4 << endl;
      cout << lower_intervals[i+1] << " " << upper_intervals[i+1] << " " << i << endl;
      for (std::vector<double>::iterator j = data1.begin(); j!=data1.end();j++)
	{
        if (*j <= upper_intervals[i+1] && *j > lower_intervals[i+1])
          frequency1++;
      }
      cout << 5 << endl;
      for (std::vector<double>::iterator j = data2.begin(); j!=data2.end();j++)
      {
        if (*j <= upper_intervals[i+1] && *j > lower_intervals[i+1])
	  frequency2++;
      }
      cout << 6 << endl;
      double lambda = frequency1 * constant_1 - frequency2 * constant_2;
      chi_squared += (lambda * lambda) / (frequency1 + frequency2);
    }
    cout << 7 << endl;
    actual_values[i] = chi_squared;
    data_file << "actual = " << chi_squared << endl;

    memory_percent *= sqrt(10);
    i++;
  }
  data_file.close();

  // creates pvalue file
  name_file(str, argv, 3);
  data_file.open(str);
  
  // creates table file
  ofstream data2_file;
  name_file(str, argv, 1);
  data2_file.open(str);

  // creates extra file
  ofstream data3_file;
  name_file(str, argv, 2);
  data3_file.open(str);

  int deg_freedom = num_buckets;
  if (stream_size1 != stream_size2)
    deg_freedom--;
  for (int i = 0; i < repeats; i++)
  {
    // adds values to the table
    data2_file << percents[i] * 100 << "\t";
    double error = abs(pochisq(GK_values[i], deg_freedom) - pochisq(actual_values[i], deg_freedom));
    data2_file << error << endl;

    // adds values to pvalue file
    data_file << pochisq(actual_values[i], deg_freedom) << " actual" << endl;
    data_file << pochisq(GK_values[i], deg_freedom) << " GK" << endl;

    // adds values to extra file
    data3_file << percents[i] * 100 << "\t";
    error = abs(GK_values[i] - actual_values[i]) / actual_values[i]; 
    data3_file << error << endl;
  }
  data3_file.close();
  data2_file.close();
  data_file.close();
  return 0;
}

void name_file(char *str, char* argv[], int extra)
{
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%m-%d-%Y.%X", &tstruct);

  strcpy(str, "RealContinuous_");
  strcat(str, argv[1]);
  strcat(str, "-");
  strcat(str, argv[2]);
  strcat(str, "_");
  strcat(str, argv[3]);
  strcat(str, "_");
  strcat(str, argv[5]);
  strcat(str, "_");
  strcat(str, buf);

  if (extra == 0)
  strcat(str, "_log.dat");
 else if (extra == 1)
   strcat(str, "_table.dat");
 else if (extra == 2)
   strcat(str, "_extra.dat");
 else 
   strcat(str, "_pvalues.dat");
}
