// BasicStats.cpp
#include <math.h>

BasicStats::BasicStats()
{
  sum = 0;
  squaredsum = 0;
  N = 0;
  min = 0; // smallest number possible?
  max = 0;
  //  count=0;
}

void BasicStats::insert(double num)
{
  N = N+1;
  sum=sum+num;
  squaredsum += num*num;
  min = _min(num);
  max = testMAX(num);
}

double BasicStats::_min(double num)
{
  if (N == 1)
    min = num;
  if (num < min)
    return num;
  else
    return min;
}

double BasicStats::MIN()
{
  return min;
}

double BasicStats::testMAX(double num)
{
	if (num >= max)
	  return num;
	else 
	  return max; 
}

double BasicStats:: Average()
{
	return sum/N;
}

double BasicStats::MAX()
{
	return max;
}

double BasicStats::SD()
{
  return sqrt((squaredsum - (N*Average()*Average()))/(N-1));
}
