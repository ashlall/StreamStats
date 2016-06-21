// Unit tests for the BasicStats class

#include "../SourceCode/BasicStats/BasicStats.cpp"
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace std;

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
  
  BasicStats e;
  for(int i=1;i<=10000;i++)
     e.insert(rand()%1000+250); //tests in a randomly generated stream with 100 as minimum
  e.insert(100);
  for(int i=1;i<=1000;i++)
     e.insert(rand()%1000+550);
  assert(e.MIN()==100);
  
}

void test_MAX()
{
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
  
  BasicStats e;
  for(int i=1;i<=10000;i++)
     e.insert(rand()%1000+250); //tests in a randomly generated stream with 200 as maximum
  e.insert(2000);
  for(int i=1;i<=1000;i++)
     e.insert(rand()%1000+550);
  assert(e.MAX()==2000);
}

void test_Average()
{
  BasicStats a;
  a.insert(50);
  assert(a.Average()==50); //tests when there is only one number in the stream.       
        
  BasicStats b;
  for (int i=1;i<=100;i++) //tests for ascending number from 1 to 100. 
    b.insert(i);
  assert(b.Average()==50.5);
  
  BasicStats c; // tests with one million items in the stream in descending order 
  for (int i=1000000;i>=1;i--)
    c.insert(i);
  assert(c.Average()==500000.5);
  
  BasicStats d;
  double sum=0;
  int random_num;
  for(int i=0;i<100000;i++)
  {
     random_num=(rand()%1000+250);
     d.insert(random_num); //tests for a randomly generated stream
     sum=sum+random_num;
  }
   assert(d.Average()==sum/100000);
}

void test_SD()
{
  BasicStats a; // tests with 10 items in the stream in ascending order
  for (int i=1;i<=10;i++)
    a.insert(i);
  assert(3.02765 <= a.SD() <= 3.0275);

  for (int i=100;i>=11;i--) // tests with 100 items in the stream in descending order
    a.insert(i);
  assert(29.01149<=a.SD()<=29.01149);

  a.insert(1000); // tests adding an outlier to the stream
  assert(98.79013<=a.SD()<=98.79013);

  for (int i=1;i<10;i++) // tests having 10 max values in the stream
    a.insert(1000);
  assert(275.6017<=a.SD()<=275.6017);

  BasicStats b; // tests with father apart integers
  for (int i=1;i<=50;i++)
    b.insert(i*3);
  assert(43.73214<=b.SD()<=43.73214);
}

int main()
{
  test_Average();
  test_MIN();
  test_MAX();
  test_SD();
}
