// QDigest.h

#include "QDigestNode.h"

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest
{
 public:
  QDigest(int _k, int u); // constructor
  ~QDigest(); // deconstructor
  void insert(double x);
  double getQuantile(double f);
  
 private:
  void compress(QDigestNode *n, int level);
  double getRank(QDigestNode *n, int current, int rank);
  *QDigestNode getSibling(QDigestNode *n);
  int sib_par_count(QDigestNode *n);
  void delete_node(QDigestNode *n);

  QDigestNode *root;
  int N, k, num; //items in the stream, compression factor, number of nodes
};

#include "QDigest.cpp"

#endif
