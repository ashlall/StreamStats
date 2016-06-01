#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  public: 
    BasicStats();
    BasicStats(const BasicStats& b);
    BasicStats& operator=(const BasicStats& b);
    ~BasicStats() {};
    void insert(double num);
    double SD();
    double MAX();
    double MIN();
    double Average();

  private:
    void copy(const BasicStats& b);
    double sum, squaredsum, min, max;
    long long int N;
    double if_MAX(double num);
    double if_MIN(double num);
};

#include "BasicStats.cpp"
#endif
