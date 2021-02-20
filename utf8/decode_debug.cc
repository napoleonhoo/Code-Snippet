#include <clocale>
#include <cwchar>
#include <iostream>
#include <locale>

#include "decode.h"

void print_decode(const wchar_t& warr);

void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

int main() {
  std::cout << sizeof(wchar_t) << std::endl;
  test0();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}

void test0() {
  std::vector<uint8_t> encoded{0x24};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test1() {
  std::vector<uint8_t> encoded{0xc2, 0xa2};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test2() {
  std::vector<uint8_t> encoded{0xe0, 0xa4, 0xb9};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test3() {
  std::vector<uint8_t> encoded{0xe2, 0x82, 0xac};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test4() {
  std::vector<uint8_t> encoded{0xed, 0x95, 0x9c};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test5() {
  std::vector<uint8_t> encoded{0xf0, 0x90, 0x8d, 0x88};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void test6() {
  std::vector<uint8_t> encoded{0x24, 0xc2, 0xa2, 0xe0, 0xa4, 0xb9, 0xe2, 0x82,
                               0xac, 0xed, 0x95, 0x9c, 0xf0, 0x90, 0x8d, 0x88};
  std::wstring decoded;
  decode(encoded, &decoded);
  for (auto& warr : decoded) {
    print_decode(warr);
  }
}

void print_decode(const wchar_t& warr) {
  // char narrow_str[] = "z\u00df\u6c34\U0001f34c";
  // wchar_t warr[29];
  uint64_t i = static_cast<uint64_t>(warr);
  std::cout << i << std::endl;
  // std::setlocale(LC_ALL, "");
  // std::swprintf(warr, sizeof warr / sizeof *warr,
  //               L"Converted from UTF-8: '%s' ", narrow_str);
  std::wcout.imbue(std::locale(""));
  std::wcout << warr << '\n';
}