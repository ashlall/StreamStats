// QDigestDouble.h, sub class of Q-Digest that takes doubles and converts them to longs

#include "Q-Digest.cpp"

#ifndef QDIGESTDOUBLE_H
#define QDIGESTDOUBLE_H

class QDigestDouble : public QDigest
{
 public:
 QDigestDouble(double compression) : QDigest(compression) { 
    precision = 1000000000.0; 
    range = 10000.0; };
  QDigestDouble(const QDigestDouble& q) : QDigest(q) {};
  
  void insert(double x)
  { 
    if (x < -range)
      x = 0;
    if (x > range)
      x = precision;
    QDigest::insert(doubleToLong(x)); 
  };
  double getQuantile(double f) { return longToDouble(QDigest::getQuantile(f)); };

 private:
  long doubleToLong(double d) { return (long)(((d + range)/(2 * range)) * precision); };
  double longToDouble(long l) { return (((double)l)/precision) * 2 * range - range; };
  double precision, range;
};

#endif
