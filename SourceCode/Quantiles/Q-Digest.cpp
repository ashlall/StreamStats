// Q-Digest.cpp, implemented with a hash table
// Adapted from https://raw.github.com/clearspring/stream-lib/master/src/main/java/com/clearspring/analytics/stream/quantile/QDigest.java
// TODO: there is a memory leak in the toAscRanges() function with ranges

#include "Q-Digest.h"
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>    
#include <vector>       

// Constructor
// Initializes all the variables
QDigest::QDigest(double compression)
{
  compression_factor = compression; 
  capacity = 1;
  size = 0;
  stream_size = 0;
  min = MAX_VALUE;
  max = -MAX_VALUE;
}

// Copy Constructor
// Initializes this with all the variables from other
QDigest::QDigest(const QDigest& other)
{
  copy(other);
}

// Assignment Operator
// Reinitializes this with the variables from other
QDigest& QDigest::operator=(const QDigest& other)
{
  // if this != other
  //node2count.clear();
  copy(other);
  return *this;
}

// Inserts a value into the QDigest
// Input: value is a double
// Output: value has been inserted into the QDigest, and min/max may have been
// updated to reflect the addition of value
void QDigest::insert(double value)
{
  stream_size += 1;
  if (value < min)
    min = value;
  if (value > max)
    max = value;
  offer(value);
}

// Returns the value at the given fraction
// Input: fraction is between 0 and 1
// Output: returns the value at fraction, throws exception if fraction is 
// outside of the 0 to 1 range
double QDigest::getQuantile(double fraction)
{
  // throw exception if fraction < 0 || fraction > 1 ??
  std::vector<long*> ranges = toAscRanges();
  long sum = 0;
  for (int i = 0; i < ranges.size(); i++)
  {
    if (sum > fraction * size)
      return clamp(ranges[i][1]);
    sum += ranges[i][2];
  }
  double value = ranges[ranges.size() - 1][1];
  delete_ranges(ranges);
  return clamp(value);
}

// Inserts value into the QDigest and compresses if needed
// Output: throws error if value is not in the correct range, if value is 
// greater than capacity if rebuilds the tree structure
void QDigest::offer(long value)
{
  if (value < 0 || value == MAX_VALUE)
  {
    try 
    {
      throw value;
    }
    catch (long value)
    {
      cout << "Can only accept values in the range 0.. " <<  MAX_VALUE - 1 << endl;
    }  
  }
	
  // Rebuild if the value is too large for the current tree height
  if (value >= capacity)
    rebuildToCapacity(highestOneBit(value) << 1);   
		
 long leaf = value2leaf(value);
 if (node2count.find(leaf) == node2count.end())
   node2count.insert(std::make_pair (leaf, get(leaf)+1));
 else
   node2count[leaf] += 1;   
 size++;

 //Always compress at the inserted node, and recompress fully
 //if the tree becomes too large.
 compressUpward(leaf);
 if (node2count.size() > 3 * compression_factor) 
   compressFully();
}

// Rebuilds the tree structure with a higher capacity, means that the
// current tree becomes a leftmost subtree of the new tree
void QDigest::rebuildToCapacity(long newCapacity) 
{
  std::unordered_map<long, long> newNode2count;
  long scaleR = newCapacity / capacity - 1;  
  long scaleL = 1;
  std::vector<long> keys;
  keys.reserve(node2count.size());
	
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
    keys.push_back(i->first);
	
  std::sort(keys.begin(), keys.end());
    
  // adjusts and adds the values from the old tree into the new tree
  for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
  {
    while (scaleL <= *i / 2)
      scaleL <<= 1;
    newNode2count.insert(std::make_pair (*i + scaleL * scaleR, get(*i))); 
   }
  node2count = newNode2count;
  capacity = newCapacity;
  compressFully();
}

// Compress function that restores property 2 of the qdigest at node and upward
// Input: node is a node in the QDigest
void QDigest::compressUpward(long node)
{
  double threshold = std::floor(size / compression_factor);
  long atNode = get(node);
  while (!isRoot(node))
  {
    if (atNode > threshold)
      break;
    long atSibling = get(sibling(node));
    if (atNode + atSibling > threshold)
      break;
    long parent_ = parent(node);
    long atParent = get(parent_);
    if (atNode + atSibling + atParent > threshold)
      break;

    // restores property 2
    if (node2count.find(parent_) == node2count.end())
	node2count.insert(std::make_pair (parent_, atParent + atNode + atSibling));
    else
      {
	long hold = node2count[parent_];
	node2count[parent_] += 1;
      }
    node2count.erase(node);
    if (atSibling > 0)
      node2count.erase(sibling(node));
    node = parent_;
    atNode = atParent + atNode + atSibling;
  }
}

// Restores property 2 at each node, needed only if compressUpward does not
// fix all the violations of property 2
void QDigest::compressFully()
{
  std::vector<long> keys;
  keys.reserve(node2count.size());
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
    keys.push_back(i->first);

  for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
  {
    if (!isRoot(*i))
      compressDownward(*i);  
  }
}

// Restores 2nd property at seedNode and guarantees that no new violations of P2 appear.
// Same as compressUpward but slower, and therefore used less often
void QDigest::compressDownward(long seedNode)
{
  double threshold = std :: floor(size/compression_factor); 
	
  std::queue<long, std::list<long> > queue;
  queue.push(seedNode);
  while(!queue.empty())
  {
    long node = queue.front();
    queue.pop();
    long atNode = get(node);
    long atSibling = get(sibling(node));
    if (atNode == 0 && atSibling == 0)
      continue;
    long parent_ = parent(node);
    long atParent = get(parent_);
    if (atParent + atNode + atSibling > threshold)
       continue;
    if (node2count.find(parent_) == node2count.end())
      node2count.insert(std::make_pair (parent_, atParent + atNode + atSibling));
    else
      node2count[parent_] += 1;
    node2count.erase(node);
    node2count.erase(sibling(node));

    // Ensures that P2 holds for node and sibling subtrees
    if (!isLeaf(node))
    {
      queue.push(leftChild(node));
      queue.push(leftChild(sibling(node)));
    }
  }
}	

// Creates and returns a sorted array of each node and its ranges
std::vector<long*> QDigest::toAscRanges()
{
  std::vector<long*> ranges;
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
  {
    long *next_range = new long[3];
    next_range[0] = rangeLeft(i->first);
    next_range[1] = rangeRight(i->first);
    next_range[2] = i->second;
    ranges.push_back(next_range);
  }
 std::sort(ranges.begin(), ranges.end(), compare_ranges);
 return ranges;
}

// Deletes the dynamically allocated array of ranges
void QDigest::delete_ranges(std::vector<long*> ranges)
{
  for (int i = 0; i < ranges.size(); i++)
  {
    long *next = ranges[i];
    delete [] next;
  }
}

// Returns a boolean based on the inputed a and b, used to sort the ranges
bool QDigest::compare_ranges(long a[3], long b[3])
{
  long rightA = a[1], rightB = b[1], sizeA = a[1] - a[0], sizeB = b[1] - b[0];
  if (rightA < rightB)
    return 1;
  else if (rightA > rightB)
    return 0;
  else if (sizeA < sizeB)
    return 1;
  else if (sizeA > sizeB)
    return 0;
  return 0;
}

// Copies all the properties from other to this
void QDigest::copy(const QDigest& other)
{
  node2count = other.node2count;
  compression_factor = other.compression_factor;
  capacity = other.capacity;
  size = other.size;
  min = other.min;
  max = other.max;
}

// Returns the left range of id, or the leftmost value id covers
long QDigest::rangeLeft(long id)
{
  while (!isLeaf(id))
    id = leftChild(id);
  return leaf2value(id);
}

// Returns the right range of id, or the rightmost value id covers
long QDigest::rangeRight(long id)
{
  while (!isLeaf(id))
    id = rightChild(id);
  return leaf2value(id);
}

// If value is not in the range of values that were inserted, returns the
// min/max to ensure that it returns a value in the range
long QDigest::clamp(long value)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

// Searchs the map and returns the key's value if found
long QDigest::get(long node)
{
  std::unordered_map<long, long>::const_iterator got = node2count.find(node); 
  return (got == node2count.end()) ? 0 : got->second;
}

// Returns a long value with at most a single one-bit, in the position
// of the highest-order ("leftmost") one-bit in the specified int value.  
int QDigest::highestOneBit(long value)
{
  if (!value)
    return 0;
  int ret = 1;
  while (value >>= 1)
    ret <<= 1;
  return ret;
}
