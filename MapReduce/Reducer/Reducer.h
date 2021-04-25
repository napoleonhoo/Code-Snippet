#ifndef NPJH_MAPREDUCE_REDUCER_REDUCER_H_
#define NPJH_MAPREDUCE_REDUCER_REDUCER_H_

namespace npjh {

class Reducer {
 public:
  virtual void Reduce(ReduceInput* input) = 0;
};

}  // namespace npjh

#endif