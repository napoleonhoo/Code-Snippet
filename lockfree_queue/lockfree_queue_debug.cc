#include <iostream>

#include "lockfree_queue.h"

int main(int argc, char* argv[]) {
  npjh::LockFreeQueue<int> lfq;
  lfq.EnQueue(100);
  int a;
  if (lfq.DeQueue(&a) == 0) {
    std::cout << a << std::endl;
  }
}