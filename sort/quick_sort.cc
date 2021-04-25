#include "../util/util.h"
#include "sort.h"

namespace npjh {

void QuickSort(int array[], int length) {
  if (length <= 1) return;
  int pivot = array[0];
  int i = 0, j = length - 1;
  while (i < j) {
    while (i < j && array[j] > pivot) --j;
    if (i < j) {
      array[i] = array[j];
      ++i;
    }
    while (i < j && array[i] < pivot) ++i;
    if (i < j) {
      array[j] = array[i];
      --j;
    }
  }
  array[i] = pivot;
  QuickSort(array, i);
  QuickSort(array + i + 1, length - i - 1);
  return;
}

}  // namespace npjh