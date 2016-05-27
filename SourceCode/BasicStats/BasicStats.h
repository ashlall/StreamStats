#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double data, sum, min, max;
    long long int N;
    double testMAX(double num);
    double _min(double num);

  public: 
    BasicStats();
    ~BasicStats() {};
    void insert(double num);
   // double SD(double mean, int N, double data);
    double MAX();
    double MIN();
    double Average();
};

#include "BasicStats.cpp"
#endif
