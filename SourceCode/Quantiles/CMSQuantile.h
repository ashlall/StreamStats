//CMSQuantile

#ifndef CMS_QUANTILE_H
#define CMS_QUANTILE_H

#include "" //include the CMS Sketch
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <climits>
#include <math.h> 
#include <functional>
#include "time.h

class CMSQuantile
{
	
public:
	CMSQuantile();
	~CMSQuantile();
	void insert(double item);
	double getQuantile(double frac);
	
private:
	CMS* count_min;
	int altFindRange(int sum);
	int findRange(int sum);
	int rangeSum(int start,int end);
	int count(int depth, int item);
	void recursive(int depth,int start,int thresh,//parameter);
	
};

#include "CMSQuantile.cpp"
#endif
