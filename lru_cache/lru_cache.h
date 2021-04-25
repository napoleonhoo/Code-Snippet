#ifndef NPJH_LRU_CACHE_H_
#define NPJH_LRU_CACHE_H_

#include <list>
#include <unordered_map>
#include <utility>

namespace npjh {

template <class K, class V>
class LRUCache {
 private:
  int capacity_;

  typedef K KeyType;
  typedef V ValueType;
  typedef std::list<KeyType> ListType;
  typedef std::unordered_map<KeyType,
                             std::pair<ValueType, typename ListType::iterator>>
      UMapType;
  typedef typename ListType::size_type SizeType;

  ListType list_;
  UMapType umap_;

 public:
  LRUCache(int capacity) : capacity_(capacity) {}

  void Insert(const KeyType& key, const ValueType& value) {
    list_.push_front(key);
    auto iter = umap_.find(key);
    if (iter == umap_.end()) {
      umap_.insert({key, std::make_pair(value, list_.begin())});
    } else {
      list_.erase(iter->second.second);
      iter->second = std::make_pair(value, list_.begin());
    }
    if (Size() > Capacity()) Evict();
  }
  bool Contains(const KeyType& key) {
    auto iter = umap_.find(key);
    if (iter == umap_.end()) return false;
    return true;
  }
  int Get(const KeyType& key, ValueType* value) {
    auto iter = umap_.find(key);
    if (iter == umap_.end()) {
      return -1;
    }
    *value = iter->second.first;
    list_.erase(iter->second.second);
    list_.push_front(key);
    iter->second = std::make_pair(*value, list_.begin());
    return 0;
  }

  SizeType Size() const { return list_.size(); }
  int Capacity() const { return capacity_; }
  bool Empty() const { return Size() == 0; }

 private:
  void Evict() {
    auto&& key = list_.back();
    list_.pop_back();
    auto&& iter = umap_.find(key);
    if (iter == umap_.end()) return;
    umap_.erase(iter);
  }
};

}  // namespace npjh

#endif