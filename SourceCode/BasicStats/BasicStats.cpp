// BasicStats.cpp

BasicStats::BasicStats()
{
  sum = 0;
  N = 0;
  min = 0x80000000; // smallest number possible?
}

void BasicStats::insert(double num)
{
  if (num < min)
    min = num;
}

double BasicStats::MIN()
{
  return min;
}
