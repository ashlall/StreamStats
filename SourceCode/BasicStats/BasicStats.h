#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    double sum, min, max;
    int N;

  public: 
    BasicStats();
    ~BasicStats() {};
    void insert(double num);
    double mean();
    double SD(double mean, int N, double data);
    double testMAX(double num);
    double MAX();
    //double MIN();
};

#include "BasicStats.cpp"
#endif
