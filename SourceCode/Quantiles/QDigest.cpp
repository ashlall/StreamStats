// QDigest.cpp
#include <iostream>
using namespace std;

QDigest::QDigest(int _k, int u)
{
  k = _k;
  N = 0;
  num = 1;
  root = new QDigestNode(1,u); // or 0 for lower bound?
}

QDigest::QDigest(const QDigest& q)
{
  k = q.k;
  N = q.N;
  num = q.num;
  root = copy(q.root);
}

QDigest& QDigest::operator=(const QDigest& q)
{
  destroy(root);
  k = q.k;
  N = q.N;
  num = q.num;
  root = copy(q.root);
  return *this;
}

QDigest::~QDigest()
{
  destroy(root);
}

void QDigest::insert(double x)
{
  // if (x > root->upper)                                                      // get new upper bound, rebuild(x)                                          
  if (x > N)
    N = x;
  _insert(x, 1, root->upper, root);
  cout << "inserting "<< x<<endl;
  compress(root,0);


}

void QDigest::_insert(int x, int l, int u, QDigestNode *n)
{
  int mid = (l+u)/2;
  if (x <= mid)
  {
    if (n->left == NULL)
    {
      n->left = new QDigestNode(l, mid);
      n->left->parent = n;
      n->left->count++;
      num++;
      //N++;
    }
    else
      _insert(x, l, mid, n->left);
  }
  else
  {
    if (n->right == NULL)
    {
      n->right = new QDigestNode(mid + 1, u);
      n->right->parent = n;
      n->right->count++;
      num++;
      //N++;
    }
    else
      _insert(x, mid + 1, u, n->right);
  }
}

double QDigest::getQuantile(double f)
{
  double rank = f*N;
  return getRank(root, 0, rank);
}

void QDigest::compress(QDigestNode *n, int level) // haven't checked accuracy
{
  if (n == NULL)
    return;
  compress(n->left, level + 1);
  compress(n->right, level + 1);
  if (level > 0)
  {
    // cout << "hello "<<node_count(n->parent)<<" " << N/k <<endl;
    //cout <<"N and k "<< N << " " << k << endl;
    if (node_count(n->parent) < (N/k))
    {
      cout << "before"<<n->parent->count<<endl;
      n->parent->count = node_count(n->parent);
      cout<<"after " <<n->parent->count<<endl;
      if (n->parent->left)
	delete_node(n->parent->left);
      if (n->parent->right)
      delete_node(n->parent->right);
    }
  }
}

double QDigest::getRank(QDigestNode *n, int current, int rank) // haven't checked accuracy
{
  if (n == NULL)
    return 0;
  double val = getRank(n->left, current, rank);
  if (current >= rank)
    return val;
  val = getRank(n->right, current, rank);
  if (current < rank)
  {
    val = n->upper;
    current = n->count;
  }
  return val;
}

int QDigest::node_count(QDigestNode *n)
{
  int total = n->count;
  if (n->right)
    total += n->right->count;
  if (n->left)
    total += n->left->count;
  return total;
}

void QDigest::delete_node(QDigestNode *n)
{
  if (n->parent->left == n)
    n->parent->left = NULL;
  else
    n->parent->right = NULL;
  delete n;
  num--;
}

QDigestNode* QDigest::copy(QDigestNode *n)
{
  if (n == NULL)
    return NULL;
  QDigestNode *node = new QDigestNode(n->lower, n->upper);
  node->parent = n->parent;
  node->count = n->count;
  node->left = copy(n->left);
  node->right = copy(n->right);
  return node;
}

void QDigest::destroy(QDigestNode *n)
{
  if (n)
  {
    destroy(n->left);
    destroy(n->right);
    delete n;
  }
}
