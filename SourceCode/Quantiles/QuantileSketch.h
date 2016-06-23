// QuantileSketch.h

#ifndef QUANTILE_SKETCH
#define QUANTILE_SKETCH

#include <iostream>
using namespace std;

/*
Prototypes:
*/
class QuantileSketch
{
 public:
  QuantileSketch() {};
  ~QuantileSketch() {};
  virtual void insert(double x) { } ;
  virtual double getQuantile(double f) {return 0;};
  double reverseQuantile(double r, int n);
  virtual long get_stream_size(){return 0;};
  
  // To do the following:
  void reset();
  void read(); 
  void write(); // write on the disk?
};


/*
Member Functions:
*/

// performs a search to find the largest index that has value less than or equal to r
double QuantileSketch::reverseQuantile(double r, int n)
{
  int lo=0, hi= n;
  while (lo < hi)
  {
    int mid = (lo+hi)/2;
    double value = getQuantile(((double)mid)/n);
    if (value < r)
      lo = mid+1;
    else
      hi = mid;
  }
  return lo;
}

#endif










