//Chi_Square_Categorical.cpp
#include <iostream>
#include <random>

#include "../SourceCode/ChiSquare/ChiSquareCategorical.cpp"
using namespace std;
void categorical_test1()
{
	ChiSquareCategorical c1(100);
	ChiSquareCategorical c2(100);
	for(int j=0;j<10;j++)
	{ 
	for(int i=0;i<10000;i++)
	{
		c1.insert(i);
	}
	for(int i=9999;i>=0;i--)
	{
		c2.insert(i);
	}
	
	}
	cout<<c1.calculate_statistic(c2)<<endl;
}
int main()
{	
	categorical_test1();
	//categorical_test2();
	return 0;		
}
