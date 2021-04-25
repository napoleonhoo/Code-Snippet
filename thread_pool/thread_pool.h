#ifndef NPJH_THREAD_POOL_H_
#define NPJH_THREAD_POOL_H_

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <vector>

namespace npjh {

class ThreadPool {
 private:
  int worker_number_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex mtx_;
  bool done_;
  std::condition_variable cv_;

 public:
  ThreadPool(int worker_number) : worker_number_(worker_number), done_(false) {
    for (int i = 0; i < worker_number; ++i) {
      workers_.push_back(std::thread(&ThreadPool::Run, this));
    }
  }

  ~ThreadPool() {
    done_ = true;
    cv_.notify_all();
    for (auto& worker : workers_) {
      if (worker.joinable()) worker.join();
    }
  }

  void Run() {
    while (true) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lk(mtx_);
        cv_.wait(lk, [this]() { return this->done_ || !this->tasks_.empty(); });
        if (done_ || tasks_.empty()) return;
        task = std::move(tasks_.front());
        tasks_.pop();
      }
      task();
    }
  }

  template <class F, class... Args>
  std::future<typename std::result_of<F(Args...)>::type> Submit(
      F&& f, Args&&... args) {
    typedef typename std::result_of<F(Args...)>::type ResultType;
    auto task = std::make_shared<std::packaged_task<ResultType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<ResultType> rtn = task->get_future();
    {
      std::lock_guard<std::mutex> lk(mtx_);
      tasks_.push([task]() { (*task)(); });
    }
    cv_.notify_one();
    return rtn;
  }
};

}  // namespace npjh

#endif