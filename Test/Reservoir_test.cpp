// unit tests for Reservoir Sampling class

#include<cassert>
#include "../SourceCode/Quantiles/ReservoirSampling.h"
#include <iostream>
using namespace std;

void test_constructor() //more formal test is needed.. involve the consideration of error term 
{
  ReservoirSampling a(100);
  for (int i=1;i<=10000;i++)
  {
  	a.insert(i);
  }
  cout << a.getQuantile(0.5) << endl; //check the median 
  cout << a.reverseQuantile(5000, 100) <<endl; //reverse look-up of the approximate index of 5000
}

int main()
{
 test_constructor();
  return 0;
}
