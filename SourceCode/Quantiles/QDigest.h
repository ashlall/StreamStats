// QDigest.h

#include "QDigestNode.h"

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest
{
 public:
  QDigest(int _k, int u); // constructor
  QDigest(const QDigest& q); // copy constructor
  QDigest& operator=(const QDigest& q); // assignment operator
  ~QDigest(); // deconstructor
  void insert(double x);
  double getQuantile(double f);
  
 private:
  void _insert(int x, int l, int u, QDigestNode *n);
  void compress(QDigestNode *n, int level);
  double getRank(QDigestNode *n, int current, int rank);
  int sib_par_count(QDigestNode *n);
  void delete_node(QDigestNode *n);
  QDigestNode* copy(QDigestNode *n); 
  void destroy(QDigestNode *n);

  QDigestNode *root;
  int N, k, num; //items in the stream, compression factor, number of nodes
};

#include "QDigest.cpp"

#endif
