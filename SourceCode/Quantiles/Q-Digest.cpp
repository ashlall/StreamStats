// Q-Digest.cpp, implemented with a hash table
// a lot of the syntax with the unordered_map (node2count) is wrong so not compiling
// to do: work on getQuantile, specifically toAscRanges()

#include <math.h>
#include <stdlib.h>

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
  // List <long [] > ranges = toAscRanges();
  long s = 0;
  for (long[] r : ranges)
  {
    if (s > q * size)
      return clamp(longToDouble(r[1]));
    s += r[2];
  }
  long v = ranges.get(ranges.size() - 1)[1];
  return clamp(longToDouble(v));
  }*/

void QDigest::offer(long value)
{
  //if (value >= capacity)
    //rebuild
  long leaf = value2leaf(value);
  //node2count.insert(leaf, get(leaf) + 1); // java syntax, insert may require a pair: 
  node2count.insert(std::make_pair<long, long>(leaf, get(leaf)+1));
  size++;
  compressUpward(leaf);
  //if (node2count.size() > 3 * k) // java syntax
      //compressFully();
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
