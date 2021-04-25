#include <iostream>
#include <string>

#include "lru_cache.h"

int main(int argc, char* argv[]) {
  npjh::LRUCache<int, std::string> lru_cache(3);
  lru_cache.Insert(0, "zero");
  lru_cache.Insert(1, "one");
  lru_cache.Insert(2, "two");
  lru_cache.Insert(3, "three");
  lru_cache.Insert(4, "four");
  lru_cache.Insert(5, "five");
  std::cout << lru_cache.Contains(0) << std::endl;  // 0
  std::cout << lru_cache.Contains(1) << std::endl;  // 0
  std::cout << lru_cache.Contains(2) << std::endl;  // 0
  std::string get3;
  lru_cache.Get(3, &get3);
  std::cout << get3 << std::endl;  // three
  lru_cache.Insert(6, "six");
  std::cout << lru_cache.Contains(4) << std::endl;  // 0
}