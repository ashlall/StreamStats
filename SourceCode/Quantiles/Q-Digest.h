// Q-Digest.h, implemented with hash table data structure, adapted from code from Dr. Lall (*link*)

#include <unordered_map>
#include <stdlib.h>
#include "QuantileSketch.h"
#include <stdbool.h>
#include <vector>

#ifndef QDIGEST_H
#define QDIGEST_H
#define MAX_VALUE 1000000000

class QDigest : public QuantileSketch
{
 public:
  QDigest(double compression);
  QDigest(const QDigest& q);
  QDigest& operator=(const QDigest& q);
  ~QDigest() {};
  void insert(double x);
  double getQuantile(double f);

 private:
  long value2leaf(long x) { return capacity + x; };
  long leaf2value(long id) { return id - capacity; };
  bool isRoot(long id) { return id == 1; }; // Check if the input index is root or not. (Root index is 1)
  bool isLeaf(long id) { return id >= capacity; }; // Check if the input index is leaf or not. 
  long sibling(long id) { return (id % 2 == 0) ? (id + 1) : (id - 1); };// Return the index of its sibling.
  long parent(long id) { return id / 2; }; // Return the index of its parent.
  long leftChild(long id) { return 2 * id; };// Return the index of its left child.
  long rightChild(long id) { return 2 * id + 1; }; // Return the index of its right child.
  long rangeLeft(long id);
  long rangeRight(long id);
  void offer(long value);
  void compressUpward(long node);
  void compressFully();
  long get(long node);
  int highestOneBit(long value); 
  std::vector<long*> toAscRanges();
  void rebuildToCapacity(long newCapacity);  	

  bool compare_ranges(long *a, long *b);
  	
  std::unordered_map<long, long> node2count; //= new std::unordered_map<long, long>(), Map<key, value>
  long size, capacity; 
  double k; // compression factor
};

#include "Q-Digest.cpp"

#endif

