// Q-Digest.cpp, implemented with a hash table, adapted from: 
// to do: clean

#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

QDigest::QDigest(double compression)
{
  k = compression; // Initialize the private variable Compress Factor.
  capacity = 1;
  size = 0;
  min = 100000000000;
  max = -100000000000;
}

void QDigest::insert(double x)
{
  if (x < min)
    min = x;
  if (x > max)
    max = x;
  offer(x);
}

double QDigest::getQuantile(double p)
{
  std::vector<long*> ranges = toAscRanges();
  long s = 0;
  for (int i = 0; i < ranges.size(); i++)
  {
    if (s > p * size)
      return clamp(ranges[i][1]);
    s += ranges[i][2];
  }
  double x = ranges[ranges.size() - 1][1];
  delete_ranges(ranges);
  return clamp(x);
}

long QDigest::clamp(long x)
{
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

std::vector<long*> QDigest::toAscRanges()
{
  std::vector<long*> ranges;
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
  {
    long *hold = new long[3];
    hold[0] = rangeLeft(i->first);
    hold[1] = rangeRight(i->first);
    hold[2] = i->second;
    ranges.push_back(hold);
  }
 std::sort(ranges.begin(), ranges.end(), compare_ranges);
 return ranges;
}

void QDigest::delete_ranges(std::vector<long*> ranges)
{
  for (int i = 0; i < ranges.size(); i++)
  {
    long *hold = ranges[i];
    delete [] hold;
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
 /*
   Java syntax: node2count.put(leaf, get(leaf) + 1);
   value put(Key k, Value v): Inserts key value mapping into the map. 
   The get(Object key) method is used to return the value to which the specified key is mapped, 
   or null if this map contains no mapping for the key. 
 */
   
 size++;
 /*
   Always compress at the inserted node, and recompress fully
   if the tree becomes too large.
   This is one sensible strategy which both is fast and keeps
   the tree reasonably small (within the theoretical bound of 3k nodes)
 */
 compressUpward(leaf);
 if (node2count.size() > 3 * k) 
   compressFully();
}

long QDigest::get(long node)
{
  /*
    Given the index of the index, then search the container/map.
    Return the corresponding key's value if found, 0 otherwise.
    how find() works: ttp://www.cplusplus.com/reference/unordered_map/unordered_map/find/
  */ 
  std::unordered_map<long, long>::const_iterator got = node2count.find(node); 
  return (got == node2count.end()) ? 0 : got->second;
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

void QDigest::compressUpward(long node)
{
  double threshold = std::floor(size / k); // java syntax
  long atNode = get(node);
  while (!isRoot(node))
  {
    if (atNode > threshold)
      break;
    long atSibling = get(sibling(node));
    if (atNode + atSibling > threshold)
      break;
    long p = parent(node);
    long atParent = get(p);
    if (atNode + atSibling + atParent > threshold)
      break;
    if (node2count.find(p) == node2count.end())
	node2count.insert(std::make_pair<long, long>(p, atParent + atNode + atSibling));
    else
      {
	long hold = node2count[p];
	node2count[p] += 1;
      }
    node2count.erase(node);
    if (atSibling > 0)
      node2count.erase(sibling(node));
    node = p;
    atNode = atParent + atNode + atSibling;
  }
}

 /**
  * Restore 2nd property at seedNode and guarantee that no new violations of P2 appeared.
  */
void QDigest::compressDownward(long seedNode)
{
  double threshold = std :: floor(size/k); // java syntax
  // 2nd property check same as above but shorter and slower (and invoked rarely)
	
  std::queue<long, std::list<long> > q;
  q.push(seedNode);
  while(!q.empty())
  {
    long node = q.front();
    q.pop();
    long atNode = get(node);
    long atSibling = get(sibling(node));
    if (atNode == 0 && atSibling == 0)
      continue;
    long p = parent(node);
    long atParent = get(p);
    if (atParent + atNode + atSibling > threshold)
       continue;
    if (node2count.find(p) == node2count.end())
      node2count.insert(std::make_pair<long, long>(p, atParent + atNode + atSibling));
    else
      node2count[p] += 1;
    node2count.erase(node);
    node2count.erase(sibling(node));
    // Now P2 could have vanished at the node's and sibling's subtrees since they decreased.
    if (!isLeaf(node))
    {
      q.push(leftChild(node));
      q.push(leftChild(sibling(node)));
    }
  }
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

int QDigest::highestOneBit(long value)
{
  if (!value)
    return 0;
  int ret = 1;
  while (value >>= 1)
    ret <<= 1;
  return ret;
}

void QDigest::rebuildToCapacity(long newCapacity) // check accuracy
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

