// QDigest.h

#include "QDigestNode.h"

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest
{
 public:
  QDigest(int _k, int u); // constructor
  ~QDigest(); // deconstructor
  void compress(QDigestNode *n, int level);
  double getRank(QDigestNode *n, int current, int rank);
  double getQuantile(double f);
  
 private:
  QDigestNode *root;
  int N, k, num; //items in the stream, compression factor, number of nodes
  *QDigestNode getSibling(QDigestNode *n);
  int sib_par_count(QDigestNode *n);
  void delete_node(QDigestNode *n);
};

#include "QDigest.cpp"

#endif
