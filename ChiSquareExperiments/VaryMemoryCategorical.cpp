// VaryMemoryCategorical.cpp
// Experiments on real data for the categorical algorithm that vary in memory

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cmath>
#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
#include "../SourceCode/ChiSquare/Chi_Square_Distribution.cpp"

void name_file(char *str, char *argv[], int extra);

// Runs experiments with one inputed data set and varies the memory
// Input: takes 5 command line arguments, lower and upper fraction of memory,
// names of files the data are in, and number of bins
// Output: creates 4 files, the log file holds all the data generated, the 
// table file holds the pvalues deliminated by tabs, the extra file holds all 
// the calculated statistics. and the pvalue holds the actual and estimated 
// pvalues
int main(int argc, char* argv[])
{
  if (argc < 5)
  {
    cout << "usage: VaryMemoryCategorical lower-memory upper-memory filename1 filename2" << endl;
    exit(1);
  }
  
  double lower = atof(argv[1]), upper = atof(argv[2]);
  char *filename1 = argv[3], *filename2 = argv[4];

  double memory_percent, mem = lower;
  int repeats = 0;
  while (mem <= (upper + 0.00000001))
  {
    repeats++;
    mem *= sqrt(10);
  }

  double actual_values[repeats], estimated_values[repeats], percents[repeats];
  std::vector<double> data1, data2;
  std::unordered_map<double,int> stream1, stream2;

  // creates and initializes the log file
  ofstream data_file;
  char str[100];
  name_file(str, argv, 0);
  data_file.open(str);
  ifstream input_file;
  char output[100];
  int stream_size1 = 0, stream_size2 = 0;

  input_file.open(filename1);
  while (!input_file.eof())
    {
      input_file >> output;
      data1.push_back(atof(output));
      stream_size1++;
      if (stream1.find(atof(output)) == stream1.end())
	stream1.insert(std::make_pair(atof(output),1));
      else
	stream1[atof(output)] += 1;
    }
  input_file.close();

  input_file.open(filename2);
  while (!input_file.eof())
    {
      input_file >> output;
      data2.push_back(atof(output));
      stream_size2++;
      if (stream2.find(atof(output)) == stream2.end())
	stream2.insert(std::make_pair(atof(output),1));
      else
	stream2[atof(output)] += 1;
    }
  input_file.close();

  data_file << filename1 << endl << filename2 << endl;
  data_file << "stream 1 size: " << stream_size1 << endl;
  data_file << "stream 2 size: " << stream_size2 << endl;
  data_file << "number of categories: " << stream1.size() << endl;
  memory_percent = lower;
  int i = 0, num_categories;

  while (memory_percent <= (upper + 0.00000001)) //accounts for rounding
  {
    data_file << "memory percent: " << memory_percent << endl;
    percents[i] = memory_percent;

    // calculates the estimated statistic
    ChiSquareCategorical sketch1(memory_percent);
    for (std::vector<double>::iterator j = data1.begin(); j != data1.end();j++)
      sketch1.insert(*j);
    ChiSquareCategorical sketch2(memory_percent);
    for (std::vector<double>::iterator j = data2.begin(); j != data2.end();j++)
      sketch2.insert(*j);

    double estimated_stat = sketch1.calculate_statistic(sketch2, 0);

    estimated_values[i] = estimated_stat;
    data_file << "estimate = " << estimated_stat << endl;

    // calculates actual statistic
    double constant1 = sqrt(double(stream_size2) / double(stream_size1));
    double constant2 = sqrt(double(stream_size1) / double(stream_size2));
    double actual_stat = 0;

    for (std::unordered_map<double,int>::const_iterator j = stream1.begin(); j!= stream1.end(); j++)
    {
      double frequency1 = j->second;
      double frequency2 = 0;
      num_categories++;
      if (stream2.find(j->first) != stream2.end())
	frequency2 = stream2[j->first];
      double value = frequency1 * constant1 - frequency2 * constant2;
      actual_stat += (value * value) / (frequency1 + frequency2);
    }
    // have to loop through other stream to find when first one is 0
    for (std::unordered_map<double,int>::const_iterator j = stream2.begin(); j!= stream2.end(); j++)
    {
      if (stream1.find(j->first) == stream1.end())
      {
	num_categories++;
	int frequency1 = 0;
	int frequency2 = j->second;
	double value = frequency1 * constant1 - frequency2 * constant2;
	actual_stat += (value * value) / (frequency1 + frequency2);
      }
    }
    actual_values[i] = actual_stat;
    data_file << "actual = " << actual_stat << endl;
    i++;
    memory_percent *= sqrt(10);
  }
  data_file.close();

  // creates pvalues file
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

  int deg_freedom = num_categories - 1;
  for (int i = 0; i < repeats; i++)
    {
      // adds values to the table
      data2_file << percents[i] << "\t";
      double error = abs(pochisq(estimated_values[i], deg_freedom) - pochisq(actual_values[i], deg_freedom));
      data2_file << error << endl;

      // adds values to pvalue file
      data_file << pochisq(actual_values[i], deg_freedom) << " actual" << endl;
      data_file << pochisq(estimated_values[i], deg_freedom) << " estimated" << endl;

      // adds values to extra file
      data3_file << percents[i] << "\t";
      error = abs(estimated_values[i] - actual_values[i]) / actual_values[i];
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

  strcpy(str, "RealCategorical_");
  strcat(str, argv[1]);
  strcat(str, "-");
  strcat(str, argv[2]);
  strcat(str, "_");
  strcat(str, argv[3]);
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
