#ifndef NPJH_THREAD_POOL_QSORT_H_
#define NPJH_THREAD_POOL_QSORT_H_

#include <list>

#include "thread_pool.h"

namespace npjh_ccia {

template <typename T>
struct sorter {
  thread_pool pool;

  std::list<T> do_sort(std::list<T>& chunk_data) {
    if (chunk_data.empty()) {
      return chunk_data;
    }
    std::list<T> result;
    result.splice(result.begin, chunk_data, chunk_data.begin());
    T const& partition_val = *result.begin();
    typename std::list<T>::iterator divide_poit =
        std::partition(chund_data.begin(), chunk_data.end(), [&](T const& val))
  }
};

}  // namespace npjh_ccia

#endif