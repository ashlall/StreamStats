// QuantileSketch.h

#ifndef QUANTILE_SKETCH
#define QUANTILE_SKETCH

#include <iostream>
using namespace std;

class  QuantileSketch
{
 public:
  QuantileSketch() {};
  ~QuantileSketch() {};
  virtual void insert(double x);
  virtual double getQuantile(double q);
  int reverseQuantile(double r, int n);
};

//#include "QuantileSketch.cpp"

#endif QUANTILE_SKETCH

int QuantileSketch::reverseQuantile(double r, int n)
{
  int lo=0, hi= n-1;
  while (lo < hi)
  {
    int mid = (lo+hi)/2;
    double value = getQuantile(((double)mid)/n);
    if (value <= r)
      lo = mid+1;
    else
      hi = mid;
  }
  return lo;
}
