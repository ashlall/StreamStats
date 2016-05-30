//ReservoirSamping.cpp

/*
Parameterized Constrcutor.
pre-condition: The number of items to be randomly sampled.
post-condition: Dynamically Allocated array of specified sample size.
*/
ReservoirSampling::ReservoirSampling(int items)
{
  k = items; //Assigning sample size k to items
  s = new double[k]; //Dynamically allocating an array of sample size K  
  n = 0; //Setting the initial size of the stream to be 0. 
}


/*
Destructor.
pre-condition:None. 
post-condition:Deallocates the dynamically allocated memory. 
*/
ReservoirSampling::~ReservoirSampling()
{
	delete []s; //Deallocating the dynamically allocated array.
}


/*
Insert Method.
pre-condition: A floating point number. 
post-condition:Chooses to insert the number as a random sample or not
*/
void ReservoirSampling::insert(double x)
{
  n += 1; //incrementing the size of the stream as a new element is inserted
  if (n <= k) //Checking if stream size is less than random sample size
    s[n-1] = x;
  else if ((rand() % n + 1) <= k)
    s[(rand() % k)] = x;
}


/*
getQuantile Method.
pre-condition: A number from the data set. 
post-condition: The quantile for the number. 
*/
double ReservoirSampling::getQuantile(double f)
{
  sort(s,s+k); // sorting from range s to s+k
  if (f >= 1) 
    return s[k-1];// if f is greater than one
  else if (f < 0) 
    return s[0];//if f is less than 1
  else
    return s[(int)(f*k)]; //if f is between 0 and 1. 
}
