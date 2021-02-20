#ifndef NPJH_ESCAPE_H_
#define NPJH_ESCAPE_H_

// reference: url.QueryUnescape

#include <string>

namespace npjh {

bool is_hex(char ch);
char un_hex(char ch);

int unescape(const std::string &escaped, std::string *unescaped) {
  for (auto iter = escaped.cbegin(); iter != escaped.cend(); ++iter) {
    if (*iter == '%') {
      if (iter + 1 == escaped.cend() || iter + 2 == escaped.cend()) {
        return -1;
      }
      char first_char = *(iter + 1), second_char = *(iter + 2);
      if (!is_hex(first_char) || !is_hex(second_char)) {
        return -1;
      }
      unescaped->push_back(un_hex(first_char) << 4 | un_hex(second_char));
      iter += 2;
    } else {
      unescaped->push_back(*iter);
    }
  }
  return 0;
}

bool is_hex(char ch) {
  if (ch >= '0' && ch <= '9') return true;
  if (ch >= 'A' && ch <= 'F') return true;
  if (ch >= 'a' && ch <= 'f') return true;
  return false;
}

char un_hex(char ch) {
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  return 0;
}

}  // namespace npjh

#endif