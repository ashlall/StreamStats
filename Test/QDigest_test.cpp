// unit tests for QDigest class

#include<cassert>
#include "../SourceCode/Quantiles/QDigest.h"
#include <iostream>

void test_qdigest()
{
	//Example from the paper
	int hi[15] = {1, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 6, 7, 8};
	QDigest a(5, 8);
	for(int i=0; i<15; i++)
	{
		a.insert(hi[i]);
	}
	cout << "median:" << a.getQuantile(0.5) << endl;
}

void test_constructors()
{
  QDigest a(3,10);
  a.insert(2);
  
  QDigest b(a);

}

int main()
{
  test_qdigest();
  test_constructors();
  return 0;
}