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

double QDigest::getQuantile(double p)
{
  std::vector<long*> ranges = toAscRanges();
  long s = 0;
  for (int i = 0; i < ranges.size(); i++)
  {
    if (s > p * size)
      return ranges[i][1];
    s += ranges[i][2];
  }
  return ranges[ranges.size() - 1][1];
}

std::vector<long*> QDigest::toAscRanges()
{
  std::vector<long*> ranges;
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
  {
    long hold[3] = {rangeLeft(i->first), rangeRight(i->first), i->second};
    ranges.push_back(hold);
  }
  //std::sort(ranges.begin(), ranges.end(), compare_ranges);
  return ranges;
}

bool QDigest::compare_ranges(long *a, long *b)
{
  long rightA = a[1], rightB = b[1], sizeA = a[1] - a[0], sizeB = b[1] - b[0];
  if (rightA < rightB)
    return -1;
  else if (rightA > rightB)
    return 1;
  else if (sizeA < sizeB)
    return -1;
  else if (sizeA > sizeB)
    return 1;
  return 0;
}

void QDigest::offer(long value)
{
    	
    if (value < 0 || value == Long.MAX_VALUE)
	{
	    try 
	    {
	    	throw value;
	    }
	    catch (long value)
	    {
	    	cout << "Can only accept values in the range 0.. " <<  Long.MAX_VALUE - 1 << endl;
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
		Highest one bit = 128 
	}	
    
   long leaf = value2leaf(value);
   node2count.insert(std::make_pair<long, long>(leaf, get(leaf)+1));
   size++;
   /*
          Always compress at the inserted node, and recompress fully
          if the tree becomes too large.
          This is one sensible strategy which both is fast and keeps
          the tree reasonably small (within the theoretical bound of 3k nodes)
   
   compressUpward(leaf);
   //if (node2count.size() > 3 * k) // java syntax
  //compressFully(); 
  */
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
/*
int highestOneBit(long value)
{
    if (!num)
    	return 0;

    int ret = 1;

    while (num >>= 1)
    	ret <<= 1;

    return ret;
}*/
