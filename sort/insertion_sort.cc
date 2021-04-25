#include "sort.h"

void InsertionSort(int array[], int length) {
  int i, j, pivot;
  for (i = 1; i < length; ++i) {
    pivot = array[i];
    j = i - 1;
    while (j >= 0 && array[j] > pivot) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = pivot;
  }
}