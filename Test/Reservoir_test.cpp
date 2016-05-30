// unit tests for Reservoir Sampling class

#include<cassert>
#include "../SourceCode/Quantiles/ReservoirSampling.h"
#include <iostream>
using namespace std;

void test_constructor()
{
  ReservoirSampling a(10);
  a.insert(1);
  a.insert(2);
  a.insert(3);
}

int main()
{
  return 0;
}
