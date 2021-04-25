#include <iostream>
#include <vector>

#include "../../util/util.h"
#include "bst.h"
#include "traverse.h"

int main(int argc, char* argv[]) {
  npjh::BST<int> one(1);
  npjh::BST<int> two(2);
  npjh::BST<int> three(3);
  npjh::BST<int> four(4);
  npjh::BST<int> five(5);
  npjh::BST<int> six(6);
  npjh::BST<int> seven(7);
  one.left = &two;
  one.right = &three;
  two.left = &four;
  two.right = &five;
  four.left = &six;
  five.right = &seven;

  std::vector<int> vec;
  std::cout << "PreOrderTraversal_Recursive\n";
  npjh::PreOrderTraversal_Recursive(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "InOrderTraversal_Recursive\n";
  npjh::InOrderTraversal_Recursive(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "PostOrderTraversal_Recursive\n";
  npjh::PostOrderTraversal_Recursive(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "PreOrderTraversal_Iterative\n";
  npjh::PreOrderTraversal_Iterative(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "InOrderTraversal_Iterative\n";
  npjh::InOrderTraversal_Iterative(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "PostOrderTraversal_Iterative\n";
  npjh::PostOrderTraversal_Iterative(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "WidthFirstTraversal_Iterative\n";
  npjh::WidthFirstTraversal_Iterative(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();
  std::cout << "DepthFirstTraversal_Iterative\n";
  npjh::DepthFirstTraversal_Iterative(&one, &vec);
  npjh::PrintVector(vec);
  vec.clear();

  return 0;
}