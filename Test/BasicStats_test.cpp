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

void test_MAX()
{
/*BasicStats e;
	e.insert(5);
	e.insert(109);
	e.insert(10);
	cout << e.MAX() <<endl;
*/
	
 BasicStats a; // tests when there is one item in the stream
  a.insert(3);
  assert(a.MAX()==3);

  BasicStats b; // tests with 100 items in the stream in ascending order
  for (int i=1;i<100;i++)
    b.insert(i);
  assert(b.MAX()==99);

  BasicStats c; // tests with one million items in the stream in descending order 
  for (int i=1000000;i>=1;i--)
    c.insert(i);
  assert(c.MAX()==1000000);

  BasicStats d; // tests the stream in ascending order
  for (int i=1;i<=100000;i++)
    d.insert(i*3);
  assert(d.MAX()==300000);
}

void test_Average()
{
	BasicStats a;
	for (int i=1;i<=100;i++)
	  a.insert(i);
       	assert(a.Average()==50.5);


}

void test_SD()
{
  BasicStats a;
  for (int i=1;i<=10;i++)
    a.insert(i);
  cout<<a.SD()<<endl;
  // assert(a.SD()==3.02765);
}

int main()
{
  test_constructor();
  test_Average();
  test_MIN();
  test_MAX();
  test_SD();
}
