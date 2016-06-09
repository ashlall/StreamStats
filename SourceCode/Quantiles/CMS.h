//CMS.h

#ifndef CMS_H
#define CMS_H

#include "QuantileSketch.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <climits>
#include <math.h> 
#include <functional>
#include "time.h"

class HashTable
{
public:
	int rand_num;
	HashTable();
	HashTable(int n)
	{
		rand_num=n;
	}
	int hash(int item)
	{
		return ((rand_num+item)%6456007)%8529047;
	}
};

class CMS
{
	
public:
	CMS(int width,int depth);
	~CMS();
	void update(unsigned int item,int diff);
	int pointEstimate(int item);
	

private:
	long count;
	int depth;
	int width;
	int **c;
	HashTable **hashA;
	HashTable **hashB;
};

#include"CMS.cpp"
#endif
