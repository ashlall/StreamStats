// Q-Digest.h, implemented with hash table data structure, adapted from code from Dr. Lall (*link*)

#include <unordered_map>
#include <stdlib.h>
#include "QuantileSketch.h"
#include <stdbool.h>

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest : public QuantileSketch
{
 public:
  QDigest(double compression) { k = compression; };
  QDigest(const QDigest& q);
  QDigest& operator=(const QDigest& q);
  ~QDigest() {};
  void insert(double x);
  double getQuantile(double f);

 private:
  long value2leaf(long x) { return capacity + x; };
  long leaf2value(long id) { return id - capacity; };
  bool isRoot(long id) { return id == 1; };
  bool isLeaf(long id) { return id >= capacity; };
  long sibling(long id) { return (id % 2 == 0) ? (id + 1) : (id - 1); };
  long parent(long id) { return id / 2; };
  long leftChild(long id) { return 2 * id; };
  long rightChild(long id) { return 2 * id + 1; };
  long doubleToLong(double d) { return (long)(((d + range)/(2 * range)) * precision); };
  double longToDouble(long l) { return (((double)l)/precision) * 2 * range - range; };
  long rangeLeft(long id);
  long rangeRight(long id);
  void offer(long value);
  void compressUpward(long node);
  long get(long node);
  double clamp(double value);

  std::unordered_map<long, long> node2count; //= new std::unordered_map<long, long>();
  long size, capacity = 1; 
  double k; // compression factor
  double range = 1000000000.0; // assume all value in range [-range, range]
  double precision = 1000000000.0;
  double min = range;
  double max = -range;
};

#include "Q-Digest.cpp"

#endif

