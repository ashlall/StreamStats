// Q-Digest.h, implemented with hash table data structure, adapted from code from Dr. Lall (*link*)

#include <unordered_map>
#include <stdlib.h>
#include "QuantileSketch.h"
#include <stdbool.h>
#include <vector>

#ifndef QDIGEST_H
#define QDIGEST_H

class QDigest : public QuantileSketch
{
 public:
  QDigest(double compression);
  QDigest(const QDigest& q);
  QDigest& operator=(const QDigest& q);
  ~QDigest() {};
  void insert(double x);
  //double getQuantile(double f);

 private:
  long value2leaf(long x) { return capacity + x; };
  long leaf2value(long id) { return id - capacity; };
  bool isRoot(long id) { return id == 1; }; // Check if the input index is root or not. (Root index is 1)
  bool isLeaf(long id) { return id >= capacity; }; // Check if the input index is leaf or not. 
  long sibling(long id) { return (id % 2 == 0) ? (id + 1) : (id - 1); };// Return the index of its sibling.
  long parent(long id) { return id / 2; }; // Return the index of its parent.
  long leftChild(long id) { return 2 * id; };// Return the index of its left child.
  long rightChild(long id) { return 2 * id + 1; }; // Return the index of its right child.
  long doubleToLong(double d) { return (long)(((d + range)/(2 * range)) * precision); }; //Handle the case that 
  double longToDouble(long l) { return (((double)l)/precision) * 2 * range - range; }; // the original q-diget algorithm can only store integer
  long rangeLeft(long id);
  long rangeRight(long id);
  void offer(long value);
  void compressUpward(long node);
  long get(long node);
  double clamp(double value);
  int highestOneBit(long value); 
  std::vector<long*> toAscRanges();
  bool compare_ranges(long *a, long *b);
  	
  std::unordered_map<long, long> node2count; //= new std::unordered_map<long, long>(), Map<key, value>
  long size, capacity; 
  double k; // compression factor
  double range; // assume all value in range [-range, range]
  double precision;
  double min;
  double max;
};

#include "Q-Digest.cpp"

#endif

