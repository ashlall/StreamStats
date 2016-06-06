// Q-Digest.cpp, implemented with a hash table
// a lot of the syntax with the unordered_map (node2count) is wrong so not compiling
// to do: work on getQuantile, specifically toAscRanges()

#include <math.h>
#include <stdlib.h>
#include <vector>

QDigest::QDigest(double compression)
{
  k = compression; // Initialize the private variable Compress Factor.
  capacity = 1;
  range = 1000000000.0;
  precision = 1000000000.0;
  min = range;
  max = -range;
}

void QDigest::insert(double x)
{
  if (x < min)
    min = x;
  if (x > max)
    max = x;
  offer(doubleToLong(x));
}

/*double QDigest::getQuantile(double p)
{
  List <long [] > ranges = toAscRanges();
  long s = 0;
  for (long[] r : ranges)
  {
    if (s > p * size)
      return r[1];
    s += r[2];
  }
  return ranges.get(ranges.size() - 1)[1];
}*/

std::vector<long*> QDigest::toAscRanges()
{
  std::vector<long*> ranges;
  return ranges;
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
	{
	   	rebuildToCapacity(highestOneBit(value) << 1);   
	   	/* highestOneBit() returns a long value with at most a single one-bit, in the position 
   		 of the highest-order ("leftmost") one-bit in the specified int value. 
   	 	For example, value = 220
		Binary = 11011100
		Highest one bit = 128 */ 
	}	
    
   long leaf = value2leaf(value);
   node2count.insert(std::make_pair<long, long>(leaf, get(leaf)+1)); //??? not sure about how get(leaf) works 
   //Java syntax: node2count.put(leaf, get(leaf) + 1);
   // value put(Key k, Value v): Inserts key value mapping into the map. 
   //The get(Object key) method is used to return the value to which the specified key is mapped, 
   // or null if this map contains no mapping for the key.
   
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

/*void QDigest::compressFully()
{
  long [] allNodes = node2count.keySet().toArray(new long[0]);
  for (long node : allNodes)
    compressDownward(node);   // java syntax
}*/

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
    long atParent = get(parent(node));
    if (atNode + atSibling + atParent > threshold)
      break;
    //node2count.insert(parent(node), atParent + atNode + atSibling);
    node2count.insert(std::make_pair<long, long>(parent(node), atParent + atNode + atSibling));
    node2count.erase(node);
    if (atSibling > 0)
      node2count.erase(sibling(node));
    node = parent(node);
    atNode = atParent + atNode + atSibling;
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

long QDigest::get(long node)
{
  std::unordered_map<long, long>::const_iterator got = node2count.find(node);
  return (got == node2count.end()) ? 0 : got->second;
}

double QDigest::clamp(double value)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

int highestOneBit(long value)
{
    if (!value)
    	return 0;

    int ret = 1;

    while (value >>= 1)
    	ret <<= 1;

    return ret;
}

void rebuildToCapacity(long newCapacity)
{
	//code needed
}

void compressFully()
{
	//code needed
}