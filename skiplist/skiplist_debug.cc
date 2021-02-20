#include "skiplist.h"

int main() {
  npjh::SkipList<int> lst(3, 0.5);
  lst.InsertElement(3);
  lst.InsertElement(6);
  lst.InsertElement(7);
  lst.InsertElement(9);
  lst.InsertElement(12);
  lst.InsertElement(19);
  lst.InsertElement(17);
  lst.InsertElement(26);
  lst.InsertElement(21);
  lst.InsertElement(25);
  lst.DisplayList();
  std::cout << lst.SearchElement(19) << std::endl;
  lst.DeleteElement(19);
  lst.DeleteElement(3);
  lst.DisplayList();
}