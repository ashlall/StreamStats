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

#endif
