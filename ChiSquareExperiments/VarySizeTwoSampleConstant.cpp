// VarySizeTwoSampleConstant.cpp
// Experiments that vary in stream size, changes one stream size and keeps the other stream constant

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cmath>
#include "DataGenerator.cpp"
#include "../SourceCode/ChiSquare/ChiSquareContinuous.cpp"
using namespace std;

void name_file(char *str, char* argv[], int extra);

// Runs the experiments that vary the size of the stream
// Input: takes 12 command line arguments
// Output: creates 5 files, the log file holds all the data generated, the
// table file holds the pvalue errors deliminated by tabs, the extra file
// holds all the calculated statistics, the pvalue file holds all the pvalues
// calculated, and the actualerror file holds the actual and estimated
// statistics deliminated by tabs  
int main(int argc, char* argv[])
{
  if (argc < 13)
  {
    cout << "usage: VarySizeTwoSample lower-size upper-size stream2-size num-stream(>0) [N|U|P|E] location1 scale1 location2 scale2 [0|1] memory-percent num-buckets" << endl;
    throw ParameterError();
  }

  double lower = atof (argv[1]);
  double upper = atof (argv[2]);
  double stream2_size = atof (argv[3]);
  int data_repeats = atoi (argv[4]);
  char distribution_type = argv[5][0];
  double location1 = atof (argv[6]);
  double scale1 = atof (argv[7]);
  double location2 = atof (argv[8]);
  double scale2 = atof (argv[9]);
  int all_quantiles = atoi (argv[10]);
  double memory_percent = atof (argv[11]);
  int num_buckets = atoi (argv[12]);
  int seed1 = 1;
  int seed2 = 2;

  // ensures that the parameters will not create error
  if (data_repeats <= 0)
  {
    cout << "The number of streams must be greater than zero.\n";
    throw ParameterError();
  }
  if (distribution_type != 'N' && distribution_type != 'U' && distribution_type != 'P' && distribution_type != 'E')
    {
      cout << "The distribution is either N, U, P, or E.\n";
      throw ParameterError();
    }
  if (lower <= 0)
    {
      cout << "The lower stream size must be greater than 0.\n";
      throw ParameterError();
    }
  if (memory_percent <= 0)
    {
      cout << "The memory percent must be greater than 0.\n";
      throw ParameterError();
    }
  if (num_buckets <= 0)
    {
      cout << "The number of bins must be greater than 0.\n";
      throw ParameterError();
    }

  // finds the number of different sizes the experiment will run on
  int stream1_size;
  int num_sizes = 0, size = lower;
  while (size <= upper)
  {
    num_sizes++;
    size *= 10;
  }

  // creates the arrays that will hold the calculated statistics
  double actual_values[data_repeats][num_sizes];
  double GK_values[data_repeats][num_sizes];
  double QD_values[data_repeats][num_sizes];
  double RS_values[data_repeats][num_sizes];
  int sizes[num_sizes];
  
  // creates and initializes the log file
  ofstream data_file;
  char str[150];
  name_file(str, argv, 0);
  data_file.open(str);
  data_file << "Distribution: " << distribution_type << endl;
  data_file << "location_1 = " << location1 << " scale_1 = " << scale1 << endl;
  data_file << "location_2 = " << location2 << " scale_2 = " << scale2 << endl;
  data_file << "number of bins = " << num_buckets << endl;
  data_file << "memory percent = " << memory_percent << endl;

  for (int i = 0; i < data_repeats; i++)  // runs all test data_repeats times
  {
    int j = 0;
    int sample2_size = memory_percent * stream2_size;

    // generates the data and the sketches of the stream held at a constant
    // size just once for each stream size of the first stream
    DataGenerator data2(distribution_type, stream2_size, seed2, location2, scale2);
    double *stream2 = data2.get_stream();
    ChiSquareContinuous GK_sketch2(sample2_size, 1);
    for (int k = 0; k < stream2_size; k++)
      GK_sketch2.insert(stream2[k]);
    
    
      ChiSquareContinuous QD_sketch2(sample2_size, 2);
      for (int k = 0; k < stream2_size; k++)
	QD_sketch2.insert(stream2[k]);
      ChiSquareContinuous RS_sketch2(sample2_size, 3);
      for (int k = 0; k < stream2_size; k++)
	RS_sketch2.insert(stream2[k]);
    
    stream1_size = lower;
    data_file << "Pass " << i+1 << ":" << endl;
    while (stream1_size <= upper)  // runs tests for every stream size
    {
      int sample1_size = memory_percent * stream1_size;
      if (!i)
	sizes[j] = stream1_size;
      data_file << "stream 1 size = " << stream1_size << endl;
      data_file << "stream 2 size = " << stream2_size << endl;

      // generates the data based on inputed parameters
      DataGenerator data1(distribution_type, stream1_size, seed1, location1, scale1);
      double *stream1 = data1.get_stream();

      // computes GK estimate
      ChiSquareContinuous GK_sketch1(sample1_size, 1);
      for (int k = 0; k < stream1_size; k++)
	GK_sketch1.insert(stream1[k]);
      //double GK_stat = GK_sketch1.two_sample_statistic(GK_sketch2, num_buckets);
      double GK_stat = GK_sketch2.two_sample_statistic(GK_sketch1, num_buckets);
      GK_values[i][j] = GK_stat;
      data_file << "GK = " << GK_stat << endl;

      if (all_quantiles)
      {
	// computes QDigest estimate
	ChiSquareContinuous QD_sketch1(sample1_size, 2);
	for (int k = 0; k < stream1_size; k++)
	  QD_sketch1.insert(stream1[k]);
	double QD_stat = QD_sketch2.two_sample_statistic(QD_sketch1, num_buckets);
	QD_values[i][j] = QD_stat;
	data_file << "QD = " << QD_stat << endl;

	// computes Reservoir Sampling estimate
	ChiSquareContinuous RS_sketch1(sample1_size, 3);
        for (int k = 0; k < stream1_size; k++)
          RS_sketch1.insert(stream1[k]);
        double RS_stat = RS_sketch2.two_sample_statistic(RS_sketch1, num_buckets);
	RS_values[i][j]= RS_stat;
	data_file << "RS = " << RS_stat<< endl;
      }
       
      // computes actual statistic
      double *upper_interval = GK_sketch2.get_upper();
      double *lower_interval = GK_sketch2.get_lower();
      double actual = data2.get_stat_two_sample(data1, num_buckets, upper_interval, lower_interval);
      actual_values[i][j] = actual;
      data_file << "Real = " << actual << endl;

      stream1_size *= 10;
      j++;
      seed1++;
    }     
    seed2++;
  }
  data_file.close();

  // creates pvalue file
  ofstream data2_file;
  char st[150];
  name_file(st, argv, 3);
  data2_file.open(st);

  // creates table file
  name_file(str, argv, 1);
  data_file.open(str);

  int deg_freedom;
  for (int i = 0; i < num_sizes; i++)
  {
    data_file << sizes[i] << "\t";
    if (sizes[i] == stream2_size)
      deg_freedom = num_buckets - 1;
    else
      deg_freedom = num_buckets;

    // adds pvalue error from the GK sketch to the table file
    double error = 0;
    for (int j = 0; j < data_repeats; j++)
      error += abs(pochisq(GK_values[j][i], deg_freedom) - pochisq(actual_values[j][i], deg_freedom));
    data_file << error / data_repeats;

    if (all_quantiles)
    {
      // adds pvalue error from the QDigest sketch to the table file
      error = 0;
      for (int j = 0; j < data_repeats; j++)
        error += abs(pochisq(QD_values[j][i], deg_freedom) - pochisq(actual_values[j][i], deg_freedom));
      data_file << "\t" << error / data_repeats << "\t";

      // adds pvalue error from the Reservoir Sampling sketch to the table file
      error = 0;
      for (int j = 0; j < data_repeats; j++)
        error += abs(pochisq(RS_values[j][i], deg_freedom) - pochisq(actual_values[j][i], deg_freedom));
      data_file << error / data_repeats;
    }
    data_file << endl;

    // adds all pvalues to the pvalue file
    data2_file << "stream1_size = " << sizes[i] << " stream2_size = " << stream2_size << endl;
    for (int j = 0; j < data_repeats; j++)
    {
      data2_file << pochisq(actual_values[j][i], deg_freedom) << " actual" << endl;
      data2_file << pochisq(GK_values[j][i], deg_freedom) << " GK" << endl;
      if (all_quantiles)
      {
	data2_file << pochisq(QD_values[j][i], deg_freedom) << " QD" << endl;
	data2_file << pochisq(RS_values[j][i], deg_freedom) << " RS" << endl;
      }
    }
  }
  data2_file.close();
  data_file.close();

  // Creates extra file
  name_file(str, argv, 2);
  data_file.open(str);

  // adds actual statistics to the extra file
  for (int i = 0; i < num_sizes; i++)
  {
    for (int j = 0; j < data_repeats; j++)
      data_file << actual_values[j][i] << "\t";
  }
  data_file << endl;

  // adds GK statistics to the extra file
  for (int i = 0; i < num_sizes; i++)
  {
    for(int j = 0; j <data_repeats; j++)
      data_file << GK_values[j][i] << "\t";
  }
  data_file << endl;
  if (all_quantiles)
  {
    // adds QDigest statistics to the extra file
    for (int i = 0; i < num_sizes; i++)
    {
      for(int j = 0; j <data_repeats; j++)
        data_file << QD_values[j][i] << "\t";
    }
    data_file << endl;

    // adds Reservoir Sampling statistic to the extra file
    for (int i = 0; i < num_sizes; i++)
    {
      for(int j = 0; j <data_repeats; j++)
        data_file << RS_values[j][i] << "\t";
    }
    data_file << endl;
  }

  data_file << endl;
  data_file.close();
  return 0;
}

// Creates a string that will be the name of one of the files using the command
// line arguments and the current day and time
// Input: argv has 12 parameters, extra is from 0 to 4
// Output: when extra is 0 i creates the name for the log file, when 1 creates
// name for table file, when 2 creates name for extra file, when 3 creates name
// for pvalues file, when 4 creates name for actual-error file
void name_file(char *str, char* argv[], int extra)
{
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%m-%d-%Y.%X", &tstruct);

  strcpy(str, "VaryS2C_");
  strcat(str, argv[1]);
  strcat(str, "-");
  strcat(str, argv[2]);
  strcat(str, "_const-");
  strcat(str, argv[3]);
  strcat(str, "_");
  strcat(str, argv[4]);
  strcat(str, "X_");
  strcat(str, argv[5]);
  strcat(str, "-1st(");
  strcat(str, argv[6]);
  strcat(str, "-");
  strcat(str, argv[7]);
  strcat(str, ")-2nd(");
  strcat(str, argv[8]);
  strcat(str, "-");
  strcat(str, argv[9]);
  strcat(str, ")_");
  strcat(str, argv[11]);
  strcat(str, "_");
  strcat(str, argv[12]);

  if (atoi(argv[10]))
    strcat(str, "_all_");
  else
    strcat(str, "_GK_");
  
  strcat(str, buf);

  if (extra == 0)
    strcat(str, "_log.dat");
  else if (extra == 1)
    strcat(str, "_table.dat");
  else if (extra == 2)
    strcat(str, "_extra.dat");
  else if (extra == 3)
    strcat(str, "_pvalues.dat");
  else 
    strcat(str, "_actual-values.dat");
}
