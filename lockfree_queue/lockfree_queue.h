#ifndef NPJH_LOCKFREE_QUEUE_H_
#define NPJH_LOCKFREE_QUEUE_H_

#include <atomic>

namespace npjh {

template <class T>
class LockFreeQueue {
 private:
  struct Node {
    T value;
    Node* next;
  };
  std::atomic<Node*> head_;
  std::atomic<Node*> tail_;

 public:
  LockFreeQueue() {
    Node* n = new Node;
    n->next = nullptr;
    std::atomic<Node*> node;
    node.store(n);
    head_ = node;
    tail_ = node;
  }

  void EnQueue(const T& data) {
    Node* node = new Node;
    node->value = data;
    node->next = nullptr;
    std::atomic<Node*> n;
    n.sotre(node);

    std::atomic<Node*> tail, next;
    while (true) {
      tail = tail_;
      next = tail_->next;
      if (tail != tail_) continue;
      if (next != nullptr) {
        std::atomic_compare_exchange_weak(&tail_, &tail, next);
        continue;
      }
      if (std::atomic_compare_exchange_weak(&tail->next, &next, n) == true)
        break;
    }
    std::atomic_compare_exchange_weak(&tail_, &tail, n);
  }

  int DeQueue(T* data) {
    std::atomic<Node*> head, tail, next;
    while (true) {
      head = head_;
      tail = tail_;
      next = head->next;

      if (head != head_) continue;
      if (head == tail && next == nullptr) {
        return -1;
      }
      if (head == tail && next == nullptr) {
        std::atomic_compare_exchange_weak(&tail_, &tail, next);
        continue;
      }
      if (std::atomic_compare_exchange_weak(&head_, &head, next) == true) {
        *data = next->value;
        break;
      }
    }
    delete head;
    return 0;
  }
};

}  // namespace npjh

#endif