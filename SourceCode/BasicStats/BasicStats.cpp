// BasicStats.cpp

BasicStats::BasicStats()
{
  sum = 0;
  N = 0;
  min = 0; // smallest number possible?
  max = 0;
  count=0;
}

void BasicStats::insert(double num)
{
  N = N+1;
  sum=sum+num;
  //min = MIN();
  //max = BasicStats.MAX(num);
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

double BasicStats ::Max(double num)
{
	if (num >= max)
	  return num;
	else 
	  return max; 
}*/

double Basic Stats:: Average(double num)
{
	return sum/N;

}
