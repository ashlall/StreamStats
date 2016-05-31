// QDigestNode.h

#include <stdlib.h>

#ifndef QDIGESTNODE_H
#define QDIGESTNODE_H

class QDigestNode
{
 public:
  QDigestNode(int l,int u)
  {
    left = right = parent = NULL; // null node?
    count = 0;
    lower = l;
    upper = u;
  }
  ~QDigestNode() {};
  QDigestNode *left, *right, *parent;
  int count, lower, upper;
};

/*
struct QDigestNode
{
	int* l;	//pointer to the lower range
	int* u; //pointer to the upper range
	int* count; //count frequency
	QDigestNode* parent; //pointer to the parent  
	QDigestNode* left; //left child
	QDigestNode* right;	//right child
	
	QDigestNode() // default constructor
		:l(NULL), u(NULL), count(NULL), parent(NULL), left(NULL), right(NULL){};
	QDigestNode(int* low, int* upp, QDigestNode*parent1, QDigestNode*left1, QDigestNode*right1, int* count1)s //constructor
	{
		l = low; 
		u = upp;
		count = count1;
		parent = parent1;
		left = left1;
		right = right1;
	}
};
*/

#endif
