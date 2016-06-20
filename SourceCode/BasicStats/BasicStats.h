#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>
using namespace std;

// Streams a set of data(doubles), and computes a number of basic statistics: 
// standard deviation, maximum, minimum, and average.
class BasicStats
{
  public: 
    BasicStats();
    BasicStats(const BasicStats& other);
    BasicStats& operator=(const BasicStats& other);
    ~BasicStats() {};
    void insert(double num);
    double SD();
    double MAX();
    double MIN();
    double Average();

  private:
    void copy(const BasicStats& other);
    double sum, squaredsum, min, max;
    long long int stream_size;
    double if_MAX(double num);
    double if_MIN(double num);
};

#include "BasicStats.cpp"
#endif
