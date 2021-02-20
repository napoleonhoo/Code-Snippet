#include "gtest/gtest.h"

#include "decode.h"

TEST(UTF_TEST, TEST_0) {
  std::vector<uint8_t> encoded{0x24};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"$";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_1) {
  std::vector<uint8_t> encoded{0xc2, 0xa2};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"¢";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_2_1) {
  std::vector<uint8_t> encoded{0xe0, 0xa4, 0xb9};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"ह";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_2_2) {
  std::vector<uint8_t> encoded{0xe2, 0x82, 0xac};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"€";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_2_3) {
  std::vector<uint8_t> encoded{0xed, 0x95, 0x9c};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"한";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_3) {
  std::vector<uint8_t> encoded{0xf0, 0x90, 0x8d, 0x88};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"𐍈";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

TEST(UTF_TEST, TEST_all) {
  std::vector<uint8_t> encoded{0x24, 0xc2, 0xa2, 0xe0, 0xa4, 0xb9, 0xe2, 0x82,
                               0xac, 0xed, 0x95, 0x9c, 0xf0, 0x90, 0x8d, 0x88};
  std::wstring decoded;
  npjh::decode(encoded, &decoded);
  std::wstring expected = L"$¢ह€한𐍈";
  ASSERT_STREQ(decoded.c_str(), expected.c_str());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}