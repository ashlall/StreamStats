#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double sum, squaredsum, min, max;
    long long int N;
    double if_MAX(double num);
    double if_MIN(double num);

  public: 
    BasicStats();
    ~BasicStats() {};
    void insert(double num);
    double SD();
    double MAX();
    double MIN();
    double Average();
};

#include "BasicStats.cpp"
#endif
