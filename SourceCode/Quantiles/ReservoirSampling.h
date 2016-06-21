// ReservoirSampling.h

#include "QuantileSketch.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#ifndef RESERVOIR_SAMPLING
#define RESERVOIR_SAMPLING

// Holds a sample of the inserted data in an array and allows for queries to
// find the quantile of a value
class ReservoirSampling: public QuantileSketch
{
 public:
  ReservoirSampling(int items);
  ReservoirSampling(const ReservoirSampling& other);
  ReservoirSampling& operator=(const ReservoirSampling& other);
  ~ReservoirSampling();
  void insert(double value);
  double getQuantile(double fraction);
  long get_stream_size(){return stream_size;};
  
 private:
  int stream_size, sample_size;
  double *array;

  void copy(const ReservoirSampling& other);
};

#include"ReservoirSampling.cpp"
#endif
