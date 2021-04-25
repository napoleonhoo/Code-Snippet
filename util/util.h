#ifndef NPJH_UTIL_H_
#define NPJH_UTIL_H_

#include <iostream>

namespace npjh {

static void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

template <class T, int N>
int ArrayLength(const T (&)[N]) {
  return N;
}

template <class T, int N>
void PrintArray(const T (&array)[N]) {
  for (int i = 0; i < N; ++i) {
    std::cout << array[i] << '\t';
  }
  std::cout << std::endl;
}

template <class T>
void PrintVector(const std::vector<T> vec) {
  for (const auto &item : vec) {
    std::cout << item << '\t';
  }
  std::cout << std::endl;
}

}  // namespace npjh

#endif