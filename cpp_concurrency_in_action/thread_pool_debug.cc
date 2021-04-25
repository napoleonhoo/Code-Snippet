#include <iostream>

#include "thread_pool.h"

int print_1() {
  std::cout << "something" << '\n';
  return 1;
}
int print_2() {
  std::cout << "something" << '\n';
  return 2;
}

int main(int argc, char* argv[]) {
  cpp_concurrency_in_action::thread_pool tp;
  auto ans1 = tp.submit(print_1);
  auto ans2 = tp.submit(print_2);
  std::cout << ans1.get() << std::endl;
  std::cout << ans2.get() << std::endl;
}