// QDigest.h

#include <stdlib.h>
#include <iostream>
using namespace std; 

#ifndef QDIGEST_H
#define QDIGEST_H

struct QDigestNode
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



class QDigest
{
 public:
  QDigest(int _k, int u); // constructor
  QDigest(const QDigest& q); // copy constructor
  QDigest& operator=(const QDigest& q); // assignment operator
  ~QDigest(); // deconstructor
  void insert(double x);
  double getQuantile(double f);
  string toString();
  
 private:
  void _insert(int x, int l, int u, QDigestNode *n);
  void _toString(QDigestNode *n, ostream &s);
  void compress(QDigestNode *n, int level);
  double getRank(QDigestNode *n, int current, int rank);
  int node_count(QDigestNode *n);
  void delete_node(QDigestNode *n);
  QDigestNode* copy(QDigestNode *n); 
  void destroy(QDigestNode *n);

  QDigestNode *root;
  int N, k, num; //items in the stream, compression factor, number of nodes
};

#include "QDigest.cpp"
#endif
