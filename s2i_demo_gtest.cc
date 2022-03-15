#include <gtest/gtest.h>

#include "s2i_demo.h"

namespace {
TEST(stringutils, is_numeric_c) {
  ASSERT_TRUE(is_numeric_c('0'));
  ASSERT_TRUE(is_numeric_c('1'));
  ASSERT_TRUE(is_numeric_c('9'));

  ASSERT_FALSE(is_numeric_c('9' + 1));
  ASSERT_FALSE(is_numeric_c('0' - 1));
}

TEST(stringutils, is_lower_c) {
  ASSERT_TRUE(is_lower_c('a'));
  ASSERT_TRUE(is_lower_c('b'));
  ASSERT_TRUE(is_lower_c('z'));

  ASSERT_FALSE(is_lower_c('a' - 1));
  ASSERT_FALSE(is_lower_c('z' + 1));
}

TEST(stringutils, is_numeric_s) {
  ASSERT_TRUE(is_numeric_s("123"));
  ASSERT_TRUE(is_numeric_s("0123"));

  ASSERT_FALSE(is_numeric_s("ABC123"));
  ASSERT_FALSE(is_numeric_s("ABC123" + 2));
  ASSERT_TRUE(is_numeric_s("ABC123" + 3));
}

TEST(stringutils, make_lower_) {
  char ss[5][20] = {"HELLO WORLD!\n", "H", "123", "hello", "heLLo"};
  int i = 0;
  for (i = 0; i < 5; ++i) {
    make_lower_(ss[i]);
  }
  ASSERT_STREQ(ss[0], "hello world!\n");
  ASSERT_STREQ(ss[1], "h");
  ASSERT_STREQ(ss[2], "123");
  ASSERT_STREQ(ss[3], "hello");
  ASSERT_STREQ(ss[4], "hello");
}

TEST(stringlib, strlen) {
  ASSERT_EQ(strlen(""), 0);
  ASSERT_EQ(strlen("1"), 1);
  ASSERT_EQ(strlen("123"), 3);
  ASSERT_EQ(strlen("123\0"), 3);
  ASSERT_EQ(strlen("123\00"), 3);
  ASSERT_EQ(strlen("123\000"), 3);
  ASSERT_EQ(strlen("123\x00"), 3);
  ASSERT_EQ(strlen("0xfee1dead"), 10);
  ASSERT_EQ(strlen("0xfee1\000dead"), 6);
  // ASSERT_EQ(strlen("0xfee1\x00dead"), 6); // not pass yet
  ASSERT_EQ(strlen("0xfee1dead" + 2), 8);

  // about escape char
  ASSERT_EQ(strlen("\xff"), 1);
  ASSERT_EQ(strlen("\xffff"), 1);
  ASSERT_EQ(strlen("\u1234"), 3);
  // ASSERT_EQ(strlen("\U12345678"), 1); // =6, why
  ASSERT_EQ(strlen("\x1234"), 1);  // 0x1234 may overflow?
}

TEST(stringlib, strcmp) {
  ASSERT_GT(strcmp("123", "122"), 0);
  ASSERT_GT(strcmp("123", "12"), 0);
  ASSERT_GT(strcmp("123", ""), 0);
  ASSERT_LT(strcmp("", "123"), 0);

  ASSERT_EQ(strcmp("123", "123"), 0);
  ASSERT_EQ(strcmp("", ""), 0);
  ASSERT_EQ(strcmp("12345" + 2, "345"), 0);
  ASSERT_EQ(strcmp("123\00045", "123"), 0);
  ASSERT_GT(strcmp("123\045", "123"), 0);

  char c[2];
  c[0] = 0x1234 % (0xff + 1);
  c[1] = 0;
  ASSERT_EQ(strcmp("\x1234", c), 0);
}

TEST(stringlib, my_numstrcmp) {
  ASSERT_GT(my_numstrcmp("123", "122"), 0);
  ASSERT_GT(my_numstrcmp("123", "12"), 0);
  ASSERT_EQ(my_numstrcmp("12", "12"), 0);
  ASSERT_EQ(my_numstrcmp("0", "0"), 0);
  ASSERT_GT(my_numstrcmp("2147483648", "1827984487"), 0);
}

TEST(stringlib, strncmp) {
  ASSERT_EQ(strncmp("abc", "abc", 3), 0);
  ASSERT_EQ(strncmp("abcde", "abc", 3), 0);

  ASSERT_GT(strncmp("abcde", "abc", 4), 0);
  ASSERT_GT(strncmp("2147483648", "2147483647", 10), 0);
}

TEST(str2int, decimal) {
  // ASSERT_EQ(str2int("123456789012"),1); // too long
  // ASSERT_EQ(str2int("abc123456789"),1);  // invalid
  ASSERT_EQ(str2int("1"), 1);
  ASSERT_EQ(str2int("+1"), 1);
  ASSERT_EQ(str2int("+11"), 11);
  ASSERT_EQ(str2int("0"), 0);
  ASSERT_EQ(str2int("123"), 123);
  ASSERT_EQ(str2int("+123"), 123);
  ASSERT_EQ(str2int("-123"), -123);
  // ASSERT_EQ(str2int("4294967295"), 0xffffffff); // too big
  // ASSERT_EQ(str2int("4294967296"),0xffffffff); // too big
  ASSERT_EQ(str2int("2147483647"), 2147483647);
  ASSERT_EQ(str2int("-2147483647"), -2147483647);
  ASSERT_EQ(str2int("-2147483648"), -2147483648);
  ASSERT_EQ(str2int("-572111984"), -572111984);
  ASSERT_EQ(str2int("1827984487"), 1827984487);

  // ASSERT_EQ(str2int("-2147483649"),-2147483649); // too big
}

TEST(str2int, hex) {
  // ASSERT_EQ(str2int("0x1"),1);
}
TEST(str2int, oct) {
  // ASSERT_EQ(str2int("01"),1);
}

}  // namespace
