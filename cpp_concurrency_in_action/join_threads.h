#ifndef NPJH_JOIN_THREADS_H_
#define NPJH_JOIN_THREADS_H_

#include <thread>
#include <vector>

namespace npjh_ccia {

class join_threads {
 private:
  std::vector<std::thread> threads_;

 public:
  join_threads(std::vector<std::thread> threads) : threads_(threads) {}
  ~join_threads() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      if (threads_[i].joinable()) {
        threads_[i].join();
      }
    }
  }
};

}  // namespace npjh_ccia

#endif