#ifndef NPJH_FUNCTION_WRAPPER_H_
#define NPJH_FUNCTION_WRAPPER_H_

#include <memory>

namespace npjh_ccia {

class function_wrapper {
 private:
  struct impl_base {
    virtual void call() = 0;
    virtual ~impl_base() {}
  };
  std::unique_ptr<impl_base> impl_;

  template <typename F>
  struct impl_type : impl_base {
    F f;
    impl_type(F&& rhs) : f(std::move(rhs)) {}
    void call() { f(); }
  };

 public:
  // TODO: use std::enable_if
  template <typename F>
  function_wrapper(F&& f) : impl_(new impl_type<F>(std::move(f))) {}
  void operator()() { impl_->call(); }
  function_wrapper() = default;
  function_wrapper(function_wrapper&& other) : impl_(std::move(other.impl_)) {}
  function_wrapper& operator=(function_wrapper&& other) {
    impl_ = std::move(other.impl_);
    return *this;
  }
  function_wrapper(const function_wrapper&&) = delete;
  function_wrapper(function_wrapper&) = delete;
  function_wrapper& operator=(const function_wrapper&) = delete;
};

}  // namespace npjh_ccia

#endif