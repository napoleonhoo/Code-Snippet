// Code List 7.2, Page 175
// Code List 7.3, Page 177
// Code List 7.4, Page 178
// Code List 7.5, Page 179
// use hazard pointer
#include <atomic>
#include <memory>

#include "hazard_pointer.h"

template <typename T>
class lock_free_stack {
 private:
  struct node {
    std::shared_ptr<T> data;
    node* next;
    node(T const& data_) : data(std::make_shared<T>(data_)) {}
  };
  std::atomic<node*> head;

 public:
  void push(T const& data) {
    node* const new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node))
      ;
  }
  std::shared_ptr<T> pop() {
    std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
    node* old_head = head.load();
    do {
      node* temp;
      do {
        temp = old_head;
        hp.store(old_head);
        old_head = headl.load();
      } while (old_head != temp);
    } while (old_head &&
             !head.compare_exchange_strong(old_head, old_head->next));
    hp.store(nullptr);
    std::shared_ptr<T> res;
    if (old_head) {
      res.swap(old_head->data);
      if (outstanding_hazard_pointers_for(old_head)) {
        reclaim_later(old_head);
      } else {
        delete old_head;
      }
      delete_nodes_with_no_hazards();
    }
    return res;
  }
};

// Code List 7.8, Page 187
#include <functional>

template <typename T>
void do_delete(void* p) {
  delete static_cast<T*>(p);
}

struct data_to_reclaim {
  void* data;
  std::function<void(void*)> deleter;
  data_to_reclaim* next;

  template <typename T>
  data_to_reclaim(T* p) : data(p), deleter(&do_delete<T>), next(0) {}
  ~data_to_reclaim() { deleter(data); }
};

std::atomic<data_to_reclaim*> nodes_to_reclaim;
void add_to_reclaim_list(data_to_reclaim* node) {
  node->next = nodes_to_reclaim.load();
  while (!nodes_to_reclaim.compare_exchange_weak(node->next, node))
    ;
}
template <typename T>
void reclaim_later(T* data) {
  add_to_reclaim_list(new data_to_reclaim(data));
}
void delete_nodes_with_no_hazards() {
  data_to_reclaim* current = nodes_to_reclaim.exchange(nullptr);
  while (current) {
    data_to_reclaim* const next = current->next;
    if (!outstanding_hazard_pointers_for(current->data)) {
      delete current;
    } else {
      add_to_reclaim_list(current);
    }
    current = next;
  }
}