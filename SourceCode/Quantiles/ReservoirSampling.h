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

//#endif

ReservoirSampling::ReservoirSampling(int items)
{
  k = items;
  s = new double[k];
  n = 0;
}

void ReservoirSampling::insert(double x)
{
  n += 1;
  if (n <= k)
    s[n-1] = x;
  else if ((rand() % n + 1) <= k)
    s[(rand() % k)] = x;
}

double ReservoirSampling::getQuantile(double f)
{
  sort(s,s+k);
  if (f >= 1)
    return s[k-1];
  else if (f < 0)
    return s[0];
  else
    return s[(int)(f*k)];
}

#endif
