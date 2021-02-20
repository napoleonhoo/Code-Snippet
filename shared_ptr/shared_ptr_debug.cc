#include "shared_ptr.h"

#include <iostream>

int main(int argc, char* argv[]) {
  int* int_ptr1 = new int(1);
  std::cout << int_ptr1 << std::endl;
  npjh::SharedPtr<int> sp1(int_ptr1);
  std::cout << "smart ptr1:" << *(sp1.GetPtr()) << std::endl;
  std::cout << "smart cnt1:" << *(sp1.GetCounter()) << std::endl;
  int* int_ptr2 = new int(2);
  std::cout << int_ptr2 << std::endl;
  npjh::SharedPtr<int> sp2(int_ptr2);
  std::cout << "smart ptr2:" << *(sp2.GetPtr()) << std::endl;
  std::cout << "smart cnt2:" << *(sp2.GetCounter()) << std::endl;
  sp1 = sp2;
  std::cout << "smart ptr1:" << *(sp1.GetPtr()) << std::endl;
  std::cout << "smart cnt1:" << *(sp1.GetCounter()) << std::endl;
  std::cout << "smart ptr2:" << *(sp2.GetPtr()) << std::endl;
  std::cout << "smart cnt2:" << *(sp2.GetCounter()) << std::endl;
  std::cout << (int_ptr1 != nullptr) << std::endl;
  std::cout << int_ptr1 << std::endl;
}