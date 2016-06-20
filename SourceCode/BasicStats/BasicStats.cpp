// BasicStats.cpp
#include <math.h>

// Initializes all of the variables used by BasicStats
BasicStats::BasicStats()
{
  sum = 0;
  squaredsum = 0;
  stream_size = 0;
  min = 0; 
  max = 0;
}

// Copy Constructor
// Input: other is another BasicStats
// Output: this is initialized with all the values from other
BasicStats::BasicStats(const BasicStats& other)
{
  copy(other);
}

// Assignment Operator
// Input: other is another BasicStats
// Output: this is reinitialized will all the values from other
BasicStats& BasicStats::operator=(const BasicStats& other)
{
  copy(other);
  return *this;
}

// Updates all of the statistical variables with the addition of num
void BasicStats::insert(double num)
{
  stream_size++; 
  sum = sum + num;
  squaredsum += num * num;
  min = if_MIN(num);
  max = if_MAX(num);
}

// Returns the smaller value between num and min.
double BasicStats::if_MIN(double num)
{
  if (stream_size == 1)
    min = num;
  if (num < min)
    return num;
  else
    return min;
}

// Returns min.
double BasicStats::MIN()
{
  return min;
}

// Returns the larger value between num and max.
double BasicStats::if_MAX(double num)
{
  if(stream_size == 1)
    max = num;
  if (num >= max)
    return num;
  else 
    return max; 
}

// Returns the average.
double BasicStats:: Average()
{
  return sum/stream_size;
}

// Returns max.
double BasicStats::MAX()
{
  return max;
}

// Returns the standard deviation
double BasicStats::SD()
{
  double average = Average();
  return sqrt((squaredsum - (stream_size*average*average))/(stream_size-1));
}

// Copies the values from other to this
void BasicStats::copy(const BasicStats& other)
{
  sum = other.sum;
  squaredsum = other.squaredsum;
  stream_size = other.stream_size;
  min = other.min;
  max = other.max;
}
