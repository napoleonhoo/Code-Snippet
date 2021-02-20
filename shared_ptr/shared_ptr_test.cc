#include "shared_ptr.h"

#include "gtest/gtest.h"

TEST(SharedPtrTest, CtorTest) {
  int* int_ptr = new int(1);
  npjh::SharedPtr<int> sp(int_ptr);
  ASSERT_EQ(*(sp.GetPtr()), 1);
  ASSERT_EQ(*(sp.GetCounter()), 1);
}

TEST(SharedPtrTest, CopyCtorTest) {
  int* int_ptr = new int(1);
  npjh::SharedPtr<int> sp(int_ptr);
  npjh::SharedPtr<int> sp1(sp);
  ASSERT_EQ(*(sp.GetPtr()), 1);
  ASSERT_EQ(*(sp1.GetPtr()), 1);
  ASSERT_EQ(*(sp.GetCounter()), 2);
  ASSERT_EQ(*(sp1.GetCounter()), 2);
}

TEST(SharedPtrTest, CopyAssignTest) {
  int* int_ptr = new int(1);
  npjh::SharedPtr<int> sp(int_ptr);
  npjh::SharedPtr<int> sp1(new int(2));
  sp = sp1;
  ASSERT_EQ(*(sp.GetPtr()), 2);
  ASSERT_EQ(*(sp1.GetPtr()), 2);
  ASSERT_EQ(*(sp.GetCounter()), 2);
  ASSERT_EQ(*(sp1.GetCounter()), 2);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
