#ifndef NPJH_ALGORITHM_STRUCTURE_BST_BST_H_
#define NPJH_ALGORITHM_STRUCTURE_BST_BST_H_

namespace npjh {

template <class T>
struct BST {
  T value;
  BST* left;
  BST* right;
  BST(T v, BST* l, BST* r) : value(v), left(l), right(r) {}
  BST(T v) : value(v), left(nullptr), right(nullptr) {}
};

}  // namespace npjh

#endif