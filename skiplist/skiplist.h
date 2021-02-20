#ifndef NPJH_SKIPLIST_H_
#define NPJH_SKIPLIST_H_

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>

namespace npjh {

template <typename T>
class SkipList {
 private:
  struct Node;

 public:
  SkipList(int max_level, float p) : MAXLVL(max_level), p_(p) {
    level_ = 0;
    header_ = new Node(-1, MAXLVL);
    std::srand(std::time(nullptr));
  }
  ~SkipList() {
    Node* current = header_->forward_[0];
    while (current != nullptr) {
      Node* tmp = current;
      current = current->forward_[0];
      delete tmp;
    }
    delete header_;
  }

  int RandomLevel() {
    float r = (float)std::rand() / RAND_MAX;
    int lvl = 0;
    while (r < p_ && lvl < MAXLVL) {
      ++lvl;
      r = (float)std::rand() / RAND_MAX;
    }
    return lvl;
  }

  Node* CreateNoe(T key, int level) { return new Node(key, level); }

  void InsertElement(T key) {
    Node* current = header_;
    Node* update[MAXLVL + 1];
    for (int i = level_; i >= 0; --i) {
      while (current->forward_[i] != nullptr &&
             current->forward_[i]->key_ < key)
        current = current->forward_[i];
      update[i] = current;
    }
    current = current->forward_[0];
    if (current == nullptr || current->key_ != key) {
      int rlevel = RandomLevel();
      if (rlevel > level_) {
        for (int i = level_ + 1; i < rlevel + 1; ++i) update[i] = header_;
        level_ = rlevel;
      }
      Node* n = CreateNoe(key, rlevel);
      for (int i = 0; i <= rlevel; ++i) {
        n->forward_[i] = update[i]->forward_[i];
        update[i]->forward_[i] = n;
      }
    }
  }

  void DeleteElement(T key) {
    Node* current = header_;
    Node* update[MAXLVL + 1];
    for (int i = level_; i >= 0; --i) {
      while (current->forward_[i] != nullptr &&
             current->forward_[i]->key_ < key)
        current = current->forward_[i];
      update[i] = current;
    }
    current = current->forward_[0];
    if (current != nullptr && current->key_ == key) {
      for (int i = 0; i <= level_; ++i) {
        if (update[i]->forward_[i] != current) break;
        update[i]->forward_[i] = current->forward_[i];
      }
      delete current;
      current = nullptr;
      while (level_ > 0 && header_->forward_[level_] == nullptr) --level_;
    }
  }

  bool SearchElement(T key) {
    Node* current = header_;
    for (int i = level_; i >= 0; --i) {
      while (current->forward_[i] && current->forward_[i]->key_ < key)
        current = current->forward_[i];
    }
    current = current->forward_[0];
    if (current && current->key_ == key) {
      return true;
    }
    return false;
  }

  void DisplayList() {
    std::cout << "***********Skip List**********" << '\n';
    for (int i = 0; i <= level_; ++i) {
      Node* node = header_->forward_[i];
      std::cout << "Level " << i << ": ";
      while (node != nullptr) {
        std::cout << node->key_ << ' ';
        node = node->forward_[i];
      }
      std::cout << '\n';
    }
  }

 private:
  int MAXLVL;
  float p_;
  int level_;
  Node* header_;
};

template <typename T>
struct SkipList<T>::Node {
 public:
  T key_;
  Node** forward_;

  Node(int key, int level) {
    key_ = key;
    forward_ = new Node*[level + 1];
    std::memset(forward_, 0, sizeof(Node*) * (level + 1));
  }
  ~Node() { delete[] forward_; }
};

}  // namespace npjh

#endif