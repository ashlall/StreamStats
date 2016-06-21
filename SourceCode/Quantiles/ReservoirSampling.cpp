//ReservoirSamping.cpp

#include "ReservoirSampling.h"

/*
Parameterized Constructor.
pre-condition: The number of items to be randomly sampled.
post-condition: Dynamically Allocated array of specified sample size.
*/
ReservoirSampling::ReservoirSampling(int items)
{
  sample_size = items; //Assigning sample size k to items
  array = new double[sample_size]; //Dynamically allocating an array of sample size K  
  stream_size = 0; //Setting the initial size of the stream to be 0. 
}

ReservoirSampling::ReservoirSampling(const ReservoirSampling& other)
{
  copy(other);
}

ReservoirSampling& ReservoirSampling::operator=(const ReservoirSampling& other)
{
  delete [] array;
  copy(other);
  return *this;
}

/*
Destructor.
pre-condition:None. 
post-condition:Deallocates the dynamically allocated memory. 
*/
ReservoirSampling::~ReservoirSampling()
{
  delete [] array; //Deallocating the dynamically allocated array.
}

/*
Insert Method.
pre-condition: A floating point number. 
post-condition:Chooses to insert the number as a random sample or not
*/
void ReservoirSampling::insert(double value)
{
  stream_size += 1; //incrementing the size of the stream as a new element is inserted
  if (stream_size <= sample_size) //Checking if stream size is less than random sample size
    array[stream_size - 1] = value;
  else if ((rand() % stream_size + 1) <= sample_size)
    array[(rand() % sample_size)] = value;
}

/*
getQuantile Method.
pre-condition: A number from the data set. 
post-condition: The quantile for the number. 
*/
double ReservoirSampling::getQuantile(double fraction)
{
  sort(array, array + sample_size); // sorting from range s to s+k
  if (fraction >= 1) 
    return array[sample_size - 1];// if f is greater than one
  else if (fraction < 0) 
    return array[0];//if f is less than 1
  else
    return array[(int)(fraction * sample_size)]; //if f is between 0 and 1. 
}

void ReservoirSampling::copy(const ReservoirSampling& other)
{
  sample_size = other.sample_size;
  stream_size = other.stream_size;
  array = new double[sample_size];
  for (int i = 0; i < sample_size; i++)
    array[i] = other.array[i];
}
