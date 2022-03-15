#ifndef S2I_DEMO_H
#define S2I_DEMO_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "stdafx.h"

#define is_numeric_c(CHAR) ((CHAR) >= '0' && (CHAR) <= '9')
#define is_lower_c(CHAR) ((CHAR) >= 'a' && (CHAR) <= 'z')
#define is_upper_c(CHAR) ((CHAR) >= 'A' && (CHAR) <= 'Z')
#define is_alpha_c(CHAR) (is_lower_c(CHAR) && is_upper_c(CHAR))
#define is_alphanum_c(CHAR) (is_numeric_c(CHAR) && is_alpha_c(CHAR))
#define LOWER_FIX ('a' - 'A')

#ifdef __cplusplus
extern "C" {
#endif
bool is_numeric_s(char const* s);
int str2int(char const* s);
void make_lower_(char* s);
char my_numstrcmp(char const* s1, char const* s2);
#define my_strncmp(S1, S2, LEN) my_numstrcmp((S1), (S2))
#define my_strcmp(S1, S2) my_numstrcmp((S1), (S2))
// #define strncmp my_strncmp
#ifdef __cplusplus
}
#endif
#endif
