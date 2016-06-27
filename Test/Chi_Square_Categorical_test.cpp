//Chi_Square_Categorical.cpp
#include<cassert>
#include <iostream>


#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
using namespace std;
void cat_test()
{
	ChiSquareCategorical c1(100);
	ChiSquareCategorical c2(100);
	for(int j=0;j<10;j++)
	{ 
	for(int i=0;i<10000;i++)
	{
		c1.insert(i);
		c2.insert(i);
	}
	}
	cout<<c1.calculate_statistic(c2)<<endl;
}
int main()
{	
	cat_test();			
	return 0;		
}
