#include <iostream>
#include <vector>

#include "binary_search.h"

int main(int argc, char* argv[]) {
  std::vector<int> vec{0, 1, 2, 4, 4, 5, 6};
  std::cout << npjh::BinarySearch(vec, 2) << std::endl;
  std::cout << npjh::BinarySearch_First(vec, 4) << std::endl;
  std::cout << npjh::BinarySearch_GreaterOrEqual(vec, 3) << std::endl;
  return 0;
}