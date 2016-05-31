// QDigest.cpp

QDigest::QDigest(int _k, int u)
{
  k = _k;
  N = 0;
  num = 1;
  root = new QDigestNode(1,u); // or 0 for lower bound?
}

QDigest::~QDigest()
{
  //destructor
}

void QDigest::insert(double x)
{

}

double QDigest::getQuantile(double f)
{
  double rank = f*N;
  return getRank(root, 0, rank);
}

void QDigest::compress(QDigestNode *n, int level)
{
  if (n == NULL)
    return;
  compress(n->left, level + 1);
  compress(n->right, level + 1);
  if (level > 0)
  {
    if (sib_par_count(n) < (N/k))
    {
      n->parent->count = sib_par_count(n);
      if (n->parent->left)
	delete_node(n->parent->left);
      if (n->parent->right)
	delete_node(n->parent->right);
    }
  }
}

double QDigest::getRank(QDigestNode *n, int current, int rank)
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

QDigestNode* QDigest::getSibling(QDigestNode *n)
{
  if (n->parent->right == n)
    return n->parent->left;
  return n->parent->right;
}

int QDigest::sib_par_count(QDigestNode *n)
{
  QDigestNode *s = getSibling();
  return n->count + s->count + n->parent->count;
}

void delete_node(QDigestNode *n)
{
  if (n->parent->left == n)
    n->parent->left == NULL;
  else
    n->parent->right == NULL;
  delete n;
  --num;
}
