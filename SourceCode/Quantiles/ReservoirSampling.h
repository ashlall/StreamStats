// ReservoirSampling.h

#include "QuantileSketch.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#ifndef RESERVOIR_SAMPLING
#define RESERVOIR_SAMPLING

class ReservoirSampling: public QuantileSketch
{
 public:
  ReservoirSampling(int items);
  ReservoirSampling(const ReservoirSampling& r);
  ReservoirSampling& operator=(const ReservoirSampling& r);
  ~ReservoirSampling();
  void insert(double x);
  double getQuantile(double f);
  int get_stream_size(){return n;};
 protected:
  int n,k;
  double *s;

  void copy(const ReservoirSampling& r);
};
#include"ReservoirSampling.cpp"
#endif
