// Q-Digest.cpp, implemented with a hash table
// Adapted from https://raw.github.com/clearspring/stream-lib/master/src/main/java/com/clearspring/analytics/stream/quantile/QDigest.java
// TODO: add exception in getQuantile

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

// Inserts value into the QDigest
// 
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
    /* 
      highestOneBit() returns a long value with at most a single one-bit, in the position 
      of the highest-order ("leftmost") one-bit in the specified int value. 
      For example, value = 220
      Binary = 11011100
      Highest one bit = 128 
    */
		
 long leaf = value2leaf(value);
 if (node2count.find(leaf) == node2count.end())
   node2count.insert(std::make_pair<long, long>(leaf, get(leaf)+1));
 else
   node2count[leaf] += 1;
   
 size++;
 /*
   Always compress at the inserted node, and recompress fully
   if the tree becomes too large.
   This is one sensible strategy which both is fast and keeps
   the tree reasonably small (within the theoretical bound of 3k nodes)
 */
 compressUpward(leaf);
 if (node2count.size() > 3 * compression_factor) 
   compressFully();
}

void QDigest::rebuildToCapacity(long newCapacity) 
{
  std::unordered_map<long, long> newNode2count;
  /*
     rebuild to newLogCapacity.
     This means that our current tree becomes a leftmost subtree
     of the new tree.
     E.g. when rebuilding a tree with logCapacity = 2
     (i.e. storing values in 0..3) to logCapacity = 5 (i.e. 0..31):
     node 1 => 8 (+= 7 = 2^0*(2^3-1))
     nodes 2..3 => 16..17 (+= 14 = 2^1*(2^3-1))
     nodes 4..7 => 32..35 (+= 28 = 2^2*(2^3-1))
     This is easy to see if you draw it on paper.
     Process the keys by "layers" in the original tree.
  */
  long scaleR = newCapacity / capacity - 1;  
  std::vector<long> keys;
  keys.reserve(node2count.size());
	
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
    keys.push_back(i->first);
	
  std::sort(keys.begin(), keys.end());
    //the place i find how to rewrite
    //http://stackoverflow.com/questions/8483985/obtaining-list-of-keys-and-values-from-unordered-map#comment10496288_8484055
    
  long scaleL = 1;
  for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
  {
    while (scaleL <= *i / 2) // see the use of iterator: // http://www.cplusplus.com/reference/vector/vector/begin/
      scaleL <<= 1;
    newNode2count.insert(std::make_pair<long, long>(*i + scaleL * scaleR, get(*i))); 
   }
  node2count = newNode2count;
  capacity = newCapacity;
  compressFully();
}

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
    if (node2count.find(parent_) == node2count.end())
	node2count.insert(std::make_pair<long, long>(parent_, atParent + atNode + atSibling));
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

void QDigest::compressFully()
{
  std::vector<long> keys;
  keys.reserve(node2count.size());
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
    keys.push_back(i->first);

  for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
    compressDownward(*i);   // java syntax
}

 /**
  * Restore 2nd property at seedNode and guarantee that no new violations of P2 appeared.
  */
void QDigest::compressDownward(long seedNode)
{
  double threshold = std :: floor(size/compression_factor); 
  // 2nd property check same as above but shorter and slower (and invoked rarely)
	
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
      node2count.insert(std::make_pair<long, long>(parent_, atParent + atNode + atSibling));
    else
      node2count[parent_] += 1;
    node2count.erase(node);
    node2count.erase(sibling(node));
    // Now P2 could have vanished at the node's and sibling's subtrees since they decreased.
    if (!isLeaf(node))
    {
      queue.push(leftChild(node));
      queue.push(leftChild(sibling(node)));
    }
  }
}	

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

void QDigest::delete_ranges(std::vector<long*> ranges)
{
  for (int i = 0; i < ranges.size(); i++)
  {
    long *next = ranges[i];
    delete [] next;
  }
}

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

void QDigest::copy(const QDigest& other)
{
  node2count = other.node2count;
  compression_factor = other.compression_factor;
  capacity = other.capacity;
  size = other.size;
  min = other.min;
  max = other.max;
}

long QDigest::rangeLeft(long id)
{
  while (!isLeaf(id))
    id = leftChild(id);
  return leaf2value(id);
}

long QDigest::rangeRight(long id)
{
  while (!isLeaf(id))
    id = rightChild(id);
  return leaf2value(id);
}

long QDigest::clamp(long value)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

// Searchs the map and returns the key's value if found, 0 otherwise
long QDigest::get(long node)
{
  std::unordered_map<long, long>::const_iterator got = node2count.find(node); 
  return (got == node2count.end()) ? 0 : got->second;
}

int QDigest::highestOneBit(long value)
{
  if (!value)
    return 0;
  int ret = 1;
  while (value >>= 1)
    ret <<= 1;
  return ret;
}
