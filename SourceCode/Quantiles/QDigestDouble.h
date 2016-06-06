// QDigestDouble.h, sub class of Q-Digest that takes doubles and converts them to longs
// ****not yet compiled or tested****

#include "Q-Digest.h"

#ifndef QDIGESTDOUBLE_H
#define QDIGESTDOUBLE_H

class QDigestDouble : public QDigest
{
 public:
 QDigestDouble(double compression) : QDigest(compression) { 
    precision = 1000000000.0; 
    range = 1000000000.0;
    min = range;
    max = -range; };
  QDigestDouble(const QDigestDouble& q) : QDigest(q) {};
  
  void insert(double x) { 
    if (x < min)
      min = x;
    if (x > max)
      max = x;
    QDigest::insert(doubleToLong(x)); };
  double getQuantile(double f) { return clamp(longToDouble(QDigest::getQuantile(f))); };

 private:
  long doubleToLong(double d) { return (long)(((d + range)/(2 * range)) * precision); };
  double longToDouble(long l) { return (((double)l)/precision) * 2 * range - range; };
  double clamp(double value){
    if (value < min)
      return min;
    if (value > max)
      return max;
    return value; };
  double precision, min, max, range;
};

#include "QDigestDouble.cpp"

#endif
