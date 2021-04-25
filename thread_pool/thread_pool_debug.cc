#include <iostream>

#include "thread_pool.h"

int increase(int x) { return ++x; }
int decrease(int x) { return --x; }

int main(int argc, char* argv[]) {
  // ThreadPool thread_pool(10);
  // int a = 10, b = 10;
  // auto inc_ans = thread_pool.enqueue(increase, a);
  // auto dec_ans = thread_pool.enqueue(decrease, b);
  // std::cout << inc_ans.get() << " " << dec_ans.get() << std::endl;
  npjh::ThreadPool thread_pool(10);
  int a = 10, b = 10;
  auto inc_ans = thread_pool.Submit(increase, a);
  auto dec_ans = thread_pool.Submit(decrease, b);
  std::cout << inc_ans.get() << " " << dec_ans.get() << std::endl;

  return 0;
}