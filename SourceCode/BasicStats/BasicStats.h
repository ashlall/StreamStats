#ifndef BASICSTATS
#define BASICSTATS

#include <iostream>

using namespace std;

class BasicStats
{
  private:
    int data, sum, N;
  public: 
    BasicStats(int num, int counter);
    ~BasicStats();
    BasicStats mean();
    BasicStats SD(mean, N, data);
    BasicStats MAX();
    BasicStats MIN();
}

#include "BasicStats.cpp"
#endif
