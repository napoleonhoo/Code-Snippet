#ifndef NPJH_MAPREDUCE_MAPPER_MAPPER_H_
#define NPJH_MAPREDUCE_MAPPER_MAPPER_H_

namespace npjh {

class Mapper {
 public:
  virtual void Map(const MapInput& input) = 0;
};

}  // namespace npjh

#endif