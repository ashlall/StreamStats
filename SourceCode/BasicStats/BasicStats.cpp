// BasicStats.cpp

BasicStats::BasicStats()
{
  double sum = 0;
  int  N = 0;
  double min = 0; // smallest number possible?
  double max = 0;
}

void BasicStats::insert(double num)
{
  N = N+1;
  //min = MIN();
	max = testMAX(num);
}

/*
double BasicStats::MIN()
{
  if (N == 1)
    min = num;
  if (num < min)
    return num;
  else
    return min;
}
*/

double BasicStats::testMAX(double num)
{
  if (num >= max)
    return num;
  else
    return max;
}

double BasicStats::MAX()
{
	return max;
}