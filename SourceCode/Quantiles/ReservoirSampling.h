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
  ~ReservoirSampling();
  void insert(double x);
  double getQuantile(double f);
 protected:
  int n,k;
  double *s;
};
#include"ReservoirSampling.cpp"
#endif
