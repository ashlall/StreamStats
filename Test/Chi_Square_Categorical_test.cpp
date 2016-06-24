//Chi_Square_Categorical.cpp
#include "../SourceCode/ChiSquare/ChiSquareCategorical.h"

void cat_test()
{
	ChiSquareCategorical c1();
	ChiSquareCategorical c2();	
	
	for(int i=0;i<=10000;i++)
	{
		c1.insert(i);
		c2.insert(i);
	}
	
	cout<<c1.calculate_statistic(c2)<<endl;
int main()
{	
	cat_test();			
	return 0;		
}
