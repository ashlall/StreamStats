#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double data, sum;
    int N;
  public: 
    BasicStats();
    ~BasicStats();
    BasicStats insert()
    BasicStats mean();
    BasicStats SD(double mean, int N, double data);
    BasicStats MAX();
    BasicStats MIN();
}

#include "BasicStats.cpp"
#endif
