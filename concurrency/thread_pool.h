#ifndef NPJH_THREAD_POOL_H_
#define NPJH_THREAD_POOL_H_

#include <atomic>
#include <functional>  //  std::function
#include <future>
#include <thread>
#include <vector>

#include "function_wrapper.h"
#include "join_threads.h"
#include "threadsafe_queue.h"

namespace npjh {

class thread_pool {
 private:
  std::atomic_bool done_;
  threadsafe_queue<function_wrapper> work_queue_;
  std::vector<std::thread> threads;
  join_threads joiner_;

  void worker_thread() {
    while (!done_) {
      function_wrapper task;
      if (work_queue_.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
  }

 public:
  thread_pool() : done_(false), joiner_(threads) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        threads.push_back(std::thread(&thread_pool::worker_thread, this));
      }
    } catch (...) {
      done_ = true;
      throw;
    }
  }

  ~thread_pool() { done_ = true; }

  template <typename FunctionType>
  std::future<typename std::result_of<FunctionType()>::type> submit(
      FunctionType f) {
    typedef typename std::result_of<FunctionType()>::type result_type;
    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());
    work_queue_.push(std::move(task));
    return res;
  }
};

}  // namespace npjh

#endif