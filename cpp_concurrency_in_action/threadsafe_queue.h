#ifndef NPJH_THREADSAFE_QUEUE_H_
#define NPJH_THREADSAFE_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

namespace npjh_ccia {

template <typename T>
class threadsafe_queue {
 private:
  mutable std::mutex mtx_;
  std::queue<T> data_queue_;
  std::condition_variable data_cond_;

 public:
  threadsafe_queue();
  threadsafe_queue(const threadsafe_queue& other) {
    std::lock_guard<std::mutex> lk(other.mtx_);
    data_queue_ = other.data_queue_;
  }
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;

  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mtx_);
    data_queue_.push(new_value);
    data_cond_.notify_one();
  }
  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lk(mtx_);
    if (data_queue_.empty()) return false;
    value = data_queue_.front();
    data_queue_.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lk(mtx_);
    if (data_queue_.empty()) return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
    data_queue_.pop();
    return res;
  }
  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mtx_);
    data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
    value = data_queue_.front();
    data_queue_.pop();
  }
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lk(mtx_);
    data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
    data_queue_.pop();
    return res;
  }
  bool empty() const {
    std::lock_guard<std::mutex> lk(mtx_);
    return data_queue_.empty();
  }
};

}  // namespace npjh_ccia

#endif