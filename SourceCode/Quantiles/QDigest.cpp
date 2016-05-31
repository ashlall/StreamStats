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
