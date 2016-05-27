// BasicStats.cpp

BasicStats::BasicStats()
{
  sum = 0;
  N = 0;
  min = 0; // smallest number possible?
}

void BasicStats::insert(double num)
{
  N = N+1;
  if (N == 1)
    min = num;
  if (num < min)
    min = num;
}

double BasicStats::MIN()
{
  return min;
}
