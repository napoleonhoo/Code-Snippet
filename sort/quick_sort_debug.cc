#include <stdio.h>

#include "../util/util.h"
#include "sort.h"

int main(int argc, char* argv[]) {
  int array[] = {7, 6, 5, 4, 3, 2, 1, 0, 7};
  npjh::QuickSort(array, npjh::ArrayLength(array));
  npjh::PrintArray(array);

  return 0;
}