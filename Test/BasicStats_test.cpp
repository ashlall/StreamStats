// Unit tests for the BasicStats class

#include "../SourceCode/BasicStats/BasicStats.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_constructor()
{
  
}

void test_MIN()
{
  BasicStats a; // tests when there is one item in the stream
  a.insert(3);
  assert(a.MIN()==3);

  BasicStats b; // tests with 100 items in the stream in ascending order
  for (int i=1;i<100;i++)
    b.insert(i);
  assert(b.MIN()==1);

  BasicStats c; // tests with one million items in the stream in descending order 
  for (int i=1000000;i>=1;i--)
    c.insert(i);
  assert(c.MIN()==1);

  BasicStats d; // tests the stream in ascending order
  for (int i=1;i<=100000;i++)
    d.insert(i*3);
  assert(d.MIN()==3);
}

void test_Average()
{
	BasicStats a;
	for (int i=1;i<=100;i++)
	  a.insert(i);
	
	assert(a.Average()==50);


}

int main()
{
  test_constructor();
  test_MIN();
  test_Average();
}
