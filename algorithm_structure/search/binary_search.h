#ifndef NPJH_ALGORITHM_STRUCTURE_SEARCH_BINARY_SEARCH_H_
#define NPJH_ALGORITHM_STRUCTURE_SEARCH_BINARY_SEARCH_H_

#include <vector>

namespace npjh {

template <class T>
int BinarySearch(std::vector<T> array, T value) {
  int low = 0, high = array.size() - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (array[mid] > value)
      high = mid - 1;
    else if (array[mid] < value)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

template <class T>
int BinarySearch_First(std::vector<T> array, T value) {
  int low = 0, high = array.size() - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (array[mid] >= value)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return (low < array.size() && array[low] == value) ? low : -1;
}

template <class T>
int BinarySearch_Last(std::vector<T> array, T value) {
  int low = 0, high = array.size() - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (array[mid] > value)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return (high >= 0 && array[high] == value) ? high : -1;
}

template <class T>
int BinarySearch_GreaterOrEqual(std::vector<T> array, T value) {
  int low = 0, high = array.size() - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (array[mid] >= value)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return (low < array.size()) ? low : -1;
}

template <class T>
int BinarySearch_LeastOrEqual(std::vector<T> array, T value) {
  int low = 0, high = array.size() - 1;
  while (low <= high) {
    int mid = low + ((high - low) >> 1);
    if (array[mid] > value)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return (high >= 0) ? high : -1;
}

}  // namespace npjh

#endif