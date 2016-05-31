// QDigest.h

#include "QDigestNode.h"

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest
{
 public:
  QDigest(int _k, int u); // constructor
  ~QDigest(); // deconstructor
  compress(QDigestNode *n, int level);
  getRank(QDigestNode *n, int current, int rank);
  getQuantile(double f);
  
 private:
  QDigestNode *root;
  int N, k, num; //items in the stream, compression factor, number of nodes
  getSibling(QDigestNode *n);
  sib_par_count(QDigestNode *n);
  delete_node(QDigestNode *n);
};

#include "QDigest.cpp"

#endif
