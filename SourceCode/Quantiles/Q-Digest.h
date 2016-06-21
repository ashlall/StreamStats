// Q-Digest.h, implemented with hash table data structure
// Adapted from https://raw.github.com/clearspring/stream-lib/master/src/main/
// java/com/clearspring/analytics/stream/quantile/QDigest.java

#include <unordered_map>
#include <stdlib.h>
#include "QuantileSketch.h"
#include <stdbool.h>
#include <vector>
#include <math.h>
#include <algorithm>    // std::sort
#include <list>           // std::list
#include <queue>          // std::queue

#ifndef QDIGEST_H
#define QDIGEST_H
#define MAX_VALUE 1000000000

class QDigest : public QuantileSketch
{
 public:
  QDigest(double compression);
  QDigest(const QDigest& other);
  QDigest& operator=(const QDigest& other);
  ~QDigest() {};
  
  void insert(double value);
  double getQuantile(double fraction);
  long get_stream_size(){return stream_size;};
  
 private:
  void offer(long value);
  void rebuildToCapacity(long newCapacity);  	
  void compressUpward(long node);
  void compressFully();
  void compressDownward(long seedNode);

  std::vector<long*> toAscRanges();
  void delete_ranges(std::vector<long*> ranges);
  static bool compare_ranges(long a[3], long b[3]);
  void copy(const QDigest& other);

  long rangeLeft(long id);
  long rangeRight(long id);
  long clamp(long value);
  long get(long node);
  int highestOneBit(long value);

  long value2leaf(long value) { return capacity + value; };
  long leaf2value(long id) { return id - capacity; };
  bool isRoot(long id) { return id == 1; }; // Check if the input index is root or not. (Root index is 1)
  bool isLeaf(long id) { return id >= capacity; }; // Check if the input index is leaf or not.
  long sibling(long id) { return (id % 2 == 0) ? (id + 1) : (id - 1); };// Return the index of its sibling.
  long parent(long id) { return id / 2; }; // Return the index of its parent.
  long leftChild(long id) { return 2 * id; };// Return the index of its left child.
  long rightChild(long id) { return 2 * id + 1; }; // Return the index of its right child. 

  std::unordered_map<long, long> node2count; //= new std::unordered_map<long, long>(), Map<key, value>
  long size, capacity, min, max;
  double compression_factor; // compression factor
  long stream_size;
};

#endif

