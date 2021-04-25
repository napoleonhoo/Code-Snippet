#ifndef NPJH_ALGORITHM_STRUCTURE_BST_TRAVERSE_H_
#define NPJH_ALGORITHM_STRUCTURE_BST_TRAVERSE_H_

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

namespace npjh {

template <class T>
void PreOrderTraversal_Recursive(BST<T>* root, std::vector<T>* vec) {
  if (root != nullptr) {
    vec->push_back(root->value);
    PreOrderTraversal_Recursive(root->left, vec);
    PreOrderTraversal_Recursive(root->right, vec);
  }
}

template <class T>
void InOrderTraversal_Recursive(BST<T>* root, std::vector<T>* vec) {
  if (root != nullptr) {
    InOrderTraversal_Recursive(root->left, vec);
    vec->push_back(root->value);
    InOrderTraversal_Recursive(root->right, vec);
  }
}

template <class T>
void PostOrderTraversal_Recursive(BST<T>* root, std::vector<T>* vec) {
  if (root != nullptr) {
    PostOrderTraversal_Recursive(root->left, vec);
    PostOrderTraversal_Recursive(root->right, vec);
    vec->push_back(root->value);
  }
}

template <class T>
void PreOrderTraversal_Iterative(BST<T>* root, std::vector<T>* vec) {
  std::stack<BST<T>*> st;
  BST<T>* node = root;
  while (true) {
    while (node != nullptr) {
      st.push(node);
      vec->push_back(node->value);
      node = node->left;
    }
    if (st.empty()) return;
    BST<T>* n = st.top();
    st.pop();
    node = n->right;
  }
}

template <class T>
void InOrderTraversal_Iterative(BST<T>* root, std::vector<T>* vec) {
  std::stack<BST<T>*> st;
  BST<T>* node = root;
  while (true) {
    while (node != nullptr) {
      st.push(node);
      node = node->left;
    }
    if (st.empty()) return;
    BST<T>* n = st.top();
    st.pop();
    vec->push_back(n->value);
    node = n->right;
  }
}

template <class T>
void PostOrderTraversal_Iterative(BST<T>* root, std::vector<T>* vec) {
  std::stack<BST<T>*> st;
  BST<T>* node = root;
  BST<T>* last_visit = root;
  while (node != nullptr || !st.empty()) {
    while (node != nullptr) {
      st.push(node);
      node = node->left;
    }
    node = st.top();
    if (node->right == nullptr || node->right == last_visit) {
      vec->push_back(node->value);
      st.pop();
      last_visit = node;
      node = nullptr;
    } else {
      node = node->right;
    }
  }
}

template <class T>
void WidthFirstTraversal_Iterative(BST<T>* root, std::vector<T>* vec) {
  std::queue<BST<T>*> qu;
  qu.push(root);
  while (!qu.empty()) {
    BST<T>* node = qu.front();
    qu.pop();
    if (node == nullptr) continue;
    vec->push_back(node->value);
    qu.push(node->left);
    qu.push(node->right);
  }
}

template <class T>
void DepthFirstTraversal_Iterative(BST<T>* root, std::vector<T>* vec) {
  PreOrderTraversal_Iterative(root, vec);
}

}  // namespace npjh

#endif