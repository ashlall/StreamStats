// Q-Digest.cpp, implemented with a hash table, adapted from: 
// to do: debug

#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

QDigest::QDigest(double compression)
{
  k = compression; // Initialize the private variable Compress Factor.
  capacity = 1;
}

void QDigest::insert(double x)
{
  offer(x);
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
  for (int i = 0; i < ranges.size(); i++)
    cout << ranges[i][0] << " here" << endl;
  std::sort(ranges.begin(), ranges.end(), compare_ranges);
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
	  cout << "here2 " << highestOneBit(value) << endl;
	   	rebuildToCapacity(highestOneBit(value) << 1);   
	   	/* 
	   	highestOneBit() returns a long value with at most a single one-bit, in the position 
   		 of the highest-order ("leftmost") one-bit in the specified int value. 
   	 	For example, value = 220
		Binary = 11011100
		Highest one bit = 128 
		*/
	}	
   long leaf = value2leaf(value);
   cout << "value leaf: " << value << " " << leaf << endl;
   if (node2count.find(leaf) == node2count.end())
     node2count.insert(std::make_pair<long, long>(leaf, get(leaf)+1));
   else
   {
     long hold = node2count[leaf];
     node2count[leaf] = hold + 1;
   }
   for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
     cout << i->first << " " << i->second << "   ";
   cout << endl;
   /*
   Java syntax: node2count.put(leaf, get(leaf) + 1);
   value put(Key k, Value v): Inserts key value mapping into the map. 
   The get(Object key) method is used to return the value to which the specified key is mapped, 
   or null if this map contains no mapping for the key. 
   */
   
   size++;
   cout << "size: " << size << endl;
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
  if (got != node2count.end()) cout << "get: " << got->first << " "<< got->second << endl;
  return (got == node2count.end()) ? 0 : got->second;
}

void QDigest::compressFully()
{
    //long [] allNodes = node2count.keySet().toArray(new long[0]); //java syntax 
    std::vector<long> keys;
	keys.reserve(node2count.size());
	for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); i != node2count.end(); i++)
   		 keys.push_back(i->first);

 	//for (long node : allNodes)
    for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
    {
   		compressDownward(*i);   // java syntax
   	}
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
    long atParent = get(parent(node));
    if (atNode + atSibling + atParent > threshold)
      break;
    node2count.insert(std::make_pair<long, long>(parent(node), atParent + atNode + atSibling));
    node2count.erase(node);
    if (atSibling > 0)
      node2count.erase(sibling(node));
    node = parent(node);
    atNode = atParent + atNode + atSibling;
  }
  cout << "compress Upward";
  for (std::unordered_map<long, long>::const_iterator i = node2count.begin(); \
       i != node2count.end(); i++)
    cout << i->first << " " << i->second << "   ";
  cout << endl;
}

 /**
  * Restore 2nd property at seedNode and guarantee that no new violations of P2 appeared.
  */
void QDigest::compressDownward(long seedNode)
{
	double threshold = std :: floor(size/k); // java syntax
	// 2nd property check same as above but shorter and slower (and invoked rarely)
	
	//for (Queue<Long> q = new LinkedList<Long>(Arrays.asList(seedNode)); !q.isEmpty(); )
	std::queue<long, std::list<long> > q;
	q.push(seedNode);
	while(!q.empty())
	  //for (std::queue <long, std::list<long>([seedNode]) > q; !q.empty();) // not sure??? ask
	{
		long node = q.front();
		q.pop();
		long atNode = get(node);
		long atSibling = get(sibling(node));
		if (atNode == 0 && atSibling == 0)
		{
			continue;
		}
		long atParent = get(parent(node));
		if (atParent + atNode + atSibling > threshold)
		{
			continue;
		}
		//node2count.put(parent(node), atParent + atNode + atSibling);
		node2count.insert(std::make_pair<long, long>(parent(node), atParent + atNode + atSibling));
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
    // Map<Long, Long> newNode2count = new HashMap<Long, Long>(); //Java syntax 
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
	/* 	Alternative of for loop:
	for(auto k : node2count) 
   	 	keys.push_back(k.first);
	*/
	
	std::sort(keys.begin(), keys.end());
    //Long[] keys = node2count.keySet().toArray(new Long[node2count.size()]); // Java syntax	
    //the place i find how to rewrite
    //http://stackoverflow.com/questions/8483985/obtaining-list-of-keys-and-values-from-unordered-map#comment10496288_8484055
    //Arrays.sort(keys);
    
    long scaleL = 1;
    //for (long k : keys)
    for (std::vector<long>::const_iterator i = keys.begin(); i != keys.end(); i++)
	{
		while (scaleL <= *i / 2) // see the use of iterator: 
								 // http://www.cplusplus.com/reference/vector/vector/begin/
		{
			scaleL <<= 1;
		 }
		//newNode2count.put(k + scaleL * scaleR, node2count.get(k)); // Java syntax
		//newNode2count.insert(std::make_pair<long, long>(k + scaleL * scaleR, node2count.get(k))); 
		//don't forget to take off the above comment.
	 }
    node2count = newNode2count;
    capacity = newCapacity;
    compressFully();
}

