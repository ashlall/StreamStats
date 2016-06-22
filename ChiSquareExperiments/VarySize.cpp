// VarySize.cpp
// Experiments that vary in stream_size, user inputs range, number of data repeats, and type/
// parameters of the distribution

#include "DataGenerator.cpp"
#include <iostream>
#include <stdlib.h>
using namespace std;



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
 
  double *stream;
  int stream_size = lower;
  for (int i = 0; i < data_repeats; i++)
  {
    while (stream_size <= upper)
    {
      DataGenerator data(distribution_type, stream_size, seed, location, scale);
      stream = data.get_stream();
      /*for (int i = 0; i < stream_size; i++)
	cout << stream[i] << " ";
	cout << endl;*/
      //VarySize(lower, upper, stream);
      stream_size *= 10;
    }
  }
  return 0;
}
