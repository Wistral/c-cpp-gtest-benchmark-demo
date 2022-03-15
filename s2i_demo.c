#include "s2i_demo.h"

char my_numstrcmp(char const* s1, char const* s2) {
  const size_t L1 = strlen(s1), L2 = strlen(s2);
  size_t offset;
  // printf("my_numstrcmp() cmp %s %s\n", s1, s2);
  if (L1 > L2) return 1;
  if (L1 < L2) return -1;
  offset = 0;
  while (s1[offset] == s2[offset] && offset < L1) {
    ++offset;
  }
  if (s1[offset] > s2[offset]) return 1;
  if (s1[offset] < s2[offset]) return -1;
  return 0;
}

bool is_numeric_s(char const* s) {
  size_t len = strlen(s), c;
  for (c = 0; c < len; ++c) {
    if (!is_numeric_c(s[c])) return false;
  }
  return true;
}

void make_lower_(char* s) {
  size_t len = strlen(s), c;
  for (c = 0; c < len; ++c) {
    if (is_upper_c(s[c])) s[c] += LOWER_FIX;
  }
}

int str2int(char const* s) {
  assertMsg(s, "number string should not be NULL!");
  ssize_t offset = 0;
  // hex mode
  if (!strncmp(s, "0x", 2)) {
    assertMsg(0, "Not support hex yet!");
  }
  // oct mode
  else if (s[0] == '0' && strcmp(s, "0")) {
    assertMsg(0, "Not support oct yet!");
  }
  // decimal mode
  else {
    bool is_positive = (s[0] != '-');
    if (s[0] == '-' || s[0] == '+') {
      offset = 1;
    }
    size_t len = strlen(s) - offset, i;
    unsigned int result = 0;
    // bundary check
    assertMsg(is_numeric_s(s + offset), "number string invalid!");
    assertMsg(len <= 10, "string length beyond limit!");
    if (is_positive)
      assertMsg((my_strncmp("2147483647", s + offset, 10) >= 0),
                "positive value beyond limit!");
    else
      assertMsg((my_strncmp("-2147483648" + offset, s + offset, 10) >= 0),
                "negtive value beyond limit!");

    for (i = 0; i < len; ++i) {
      result = result * 10 + s[offset + i] - '0';
    }
    if (!is_positive) result *= -1;
    return result;
  }
  return 0;
}

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define WITHMAIN
int main(int argc, char const* argv[]) {
#ifdef __cplusplus
  printf("Build with C++!\n");
#endif
  printf("Use self-defined main()\n");

#define CHECK_S2I(SS) printf("%s in int is %d\n", (SS), str2int((SS)))
  CHECK_S2I("0");
  CHECK_S2I("2147483647");
  CHECK_S2I("0x3");
  return 0;
}
#endif
