#ifndef NPJH_SHARED_PTR_H_
#define NPJH_SHARED_PTR_H_

namespace npjh {

template <typename T>
class SharedPtr {
 public:
  // ctor
  SharedPtr(T* ptr) : ptr_(ptr) { counter_ = new int(1); }
  // dtor
  ~SharedPtr() { OnDecreaseCounter(); }
  // copy ctor
  SharedPtr(const SharedPtr& rhs)
      : ptr_(rhs.GetPtr()), counter_(rhs.GetCounter()) {
    IncreaseCounter();
  }
  // copy assignment
  SharedPtr& operator=(const SharedPtr& rhs) {
    if (rhs.GetPtr() != GetPtr()) {
      OnDecreaseCounter();
      ptr_ = rhs.GetPtr();
      counter_ = rhs.GetCounter();
      IncreaseCounter();
    }
    return *this;
  }
  T* GetPtr() const { return ptr_; }
  int* GetCounter() const { return counter_; }

 private:
  void OnDecreaseCounter() {
    --*counter_;
    if (*counter_ <= 0) {
      delete counter_;
      counter_ = nullptr;
      delete ptr_;
      ptr_ = nullptr;
    }
  }
  void IncreaseCounter() { ++*counter_; }

 private:
  int* counter_;
  T* ptr_;
};

}  // namespace npjh

#endif