#include "escape.h"

#include "gtest/gtest.h"

TEST(EscapeTest, EulerFormula) {
  std::string unescaped = "%45%5E%28%50%49%2A%49%29%2B%31%3D%30";
  std::string escaped;
  int err = npjh::unescape(unescaped, &escaped);
  ASSERT_EQ(0, err);
  std::string expected_result = "E^(PI*I)+1=0";
  ASSERT_STREQ(expected_result.c_str(), escaped.c_str());
}

TEST(EscapeTest, EulerPartialFormula) {
  std::string unescaped = "E%5E%28PI%2AI%29%2B1%3D0";
  std::string escaped;
  int err = npjh::unescape(unescaped, &escaped);
  ASSERT_EQ(0, err);
  std::string expected_result = "E^(PI*I)+1=0";
  ASSERT_STREQ(expected_result.c_str(), escaped.c_str());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}