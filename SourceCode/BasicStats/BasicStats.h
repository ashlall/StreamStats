#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double sum, squaredsum, min, max;
    long long int N;
    double testMAX(double num);
    double _min(double num);

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
