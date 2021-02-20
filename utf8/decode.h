#ifndef NPJH_DECODE_H_
#define NPJH_DECODE_H_

#include <cstdint>
#include <cstring>
#include <cwchar>

#include <string>
#include <vector>

namespace npjh {

void uint8_to_bin(uint8_t uint8_ch, int* binary_string);
void print_binary_string(int* binary_string);

#define DEBUG_DEFINE_FOUR_ARRAY                                 \
  int first_char_bin[8], second_char_bin[8], third_char_bin[8], \
      fourth_char_bin[8];

#define DEBUG_PRINT_TWO                       \
  uint8_to_bin(first_char, first_char_bin);   \
  uint8_to_bin(second_char, second_char_bin); \
  print_binary_string(first_char_bin);        \
  print_binary_string(second_char_bin);       \
  std::cout << std::endl;

#define DEBUG_PRINT_THIRD                     \
  uint8_to_bin(first_char, first_char_bin);   \
  uint8_to_bin(second_char, second_char_bin); \
  uint8_to_bin(third_char, third_char_bin);   \
  print_binary_string(first_char_bin);        \
  print_binary_string(second_char_bin);       \
  print_binary_string(third_char_bin);        \
  std::cout << std::endl;

#define DEBUG_PRINT_FOURTH                    \
  uint8_to_bin(first_char, first_char_bin);   \
  uint8_to_bin(second_char, second_char_bin); \
  uint8_to_bin(third_char, third_char_bin);   \
  uint8_to_bin(fourth_char, fourth_char_bin); \
  print_binary_string(first_char_bin);        \
  print_binary_string(second_char_bin);       \
  print_binary_string(third_char_bin);        \
  print_binary_string(fourth_char_bin);       \
  std::cout << std::endl;

/**
 * @param encoded every char is a hex number, such as c2a2
 * @param decoded  every wchar is a unicode character, such as: \u00a2
 */
int decode(const std::vector<uint8_t>& encoded, std::wstring* decoded) {
  for (auto iter = encoded.cbegin(); iter != encoded.cend(); ++iter) {
    if (*iter <= 0x7f) {
      decoded->push_back(static_cast<wchar_t>(*iter));
    } else if (*iter <= 0xdf && iter + 1 != encoded.cend() &&
               *(iter + 1) <= 0xbf) {
      uint8_t first_char = *iter, second_char = *(iter + 1);
      first_char &= 0x1f;  // delete suffix 110
      uint8_t last2bit_of_first_char =
          first_char & 0x03;                  // last two bit of first_char
      last2bit_of_first_char <<= 6;           // make last2bit the first tow bit
      second_char &= 0x3f;                    // delete suffix 10
      second_char |= last2bit_of_first_char;  // give second char first2bit
      first_char >>= 2;                       // get rid of last2bit
      decoded->push_back(static_cast<wchar_t>(first_char) << 4 |
                         static_cast<wchar_t>(second_char));
      ++iter;
    } else if (*iter <= 0xef && iter + 1 != encoded.cend() &&
               *(iter + 1) <= 0xbf && iter + 2 != encoded.cend() &&
               *(iter + 2) <= 0xbf) {
      uint8_t first_char = *iter, second_char = *(iter + 1),
              third_char = *(iter + 2);
      first_char &= 0x0f;
      second_char &= 0x3f;
      third_char &= 0x3f;
      uint8_t last2bit_of_second_char = second_char & 0x03;
      last2bit_of_second_char <<= 6;
      third_char |= last2bit_of_second_char;
      second_char >>= 2;
      uint8_t last4bit_of_first_char = first_char;
      last4bit_of_first_char <<= 4;
      second_char |= last4bit_of_first_char;
      decoded->push_back(static_cast<wchar_t>(second_char) << 8 |
                         static_cast<wchar_t>(third_char));
      iter += 2;
    } else if (*iter <= 0xf0 && iter + 1 != encoded.cend() &&
               *(iter + 1) <= 0xbf && iter + 2 != encoded.cend() &&
               *(iter + 2) <= 0xbf && iter + 3 != encoded.cend() &&
               *(iter + 3) <= 0xbf) {
      uint8_t first_char = *iter, second_char = *(iter + 1),
              third_char = *(iter + 2), fourth_char = *(iter + 3);
      first_char &= 0x0f;
      second_char &= 0x3f;
      third_char &= 0x3f;
      fourth_char &= 0x3f;
      uint8_t last2bit_of_third_char = third_char & 0x03;
      last2bit_of_third_char <<= 6;
      fourth_char |= last2bit_of_third_char;
      third_char >>= 2;
      uint8_t last4bit_of_second_char = second_char & 0x0f;
      last4bit_of_second_char <<= 4;
      third_char |= last4bit_of_second_char;
      second_char >>= 4;
      uint8_t last3bit_of_first_char = first_char;
      last3bit_of_first_char <<= 2;
      last3bit_of_first_char |= second_char;
      decoded->push_back(static_cast<wchar_t>(second_char) << 16 |
                         static_cast<wchar_t>(third_char) << 8 |
                         static_cast<wchar_t>(fourth_char));
      iter += 3;
    } else {
      decoded->push_back(static_cast<wchar_t>(*iter));
    }
  }
  return 0;
}

void uint8_to_bin(uint8_t uint8_ch, int* binary_string) {
  std::memset(binary_string, 0, 8 * sizeof(int));
  int i = 7;
  while (uint8_ch) {
    binary_string[i] = uint8_ch % 2;
    uint8_ch /= 2;
    --i;
  }
}

void print_binary_string(int* binary_string) {
  for (int i = 0; i < 8; ++i) {
    std::cout << binary_string[i];
  }
  std::cout << '\t';
}

}  // namespace npjh

#endif