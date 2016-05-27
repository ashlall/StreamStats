// Unit tests for the BasicStats class

#include "../SourceCode/BasicStats/BasicStats.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_constructor()
{
  
}

void test_insert()
{
  BasicStats b;
  b.insert(3);
  b.insert(7);
  b.insert(1);
  assert(b.MIN()==1);
}

void test_MIN()
{

}

int main()
{
  test_constructor();
  test_insert();
  test_MIN();
}
