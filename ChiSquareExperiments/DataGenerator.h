// DataGenerator.h
// Creates a stream of data based on parameters

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

class DataGenerator
{
 public:
  DataGenerator(char distribution, int size, int seed, double location, double scale);
  ~DataGenerator() { delete [] stream; };

  double* get_stream() { return stream; };
  double get_stat_one_sample(int num_buckets, double *upper_intervals, double *lower_intervals);
  double get_stat_two_sample(const DataGenerator& other, int num_buckets, double *upper_intervals, double *lower_intervals);

 private:
  double* stream;
  int stream_size;
};

class ParameterError {};

#endif
