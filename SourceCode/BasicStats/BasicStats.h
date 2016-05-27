#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double data, sum, min;
    long long int N;
  public: 
    BasicStats();
    ~BasicStats() {};
    void insert(double num);
    //double mean();
   // double SD(double mean, int N, double data);
   // double MAX();
   // double MIN();
    double Average();
};

#include "BasicStats.cpp"
#endif
