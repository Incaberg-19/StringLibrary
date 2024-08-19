#include "s21_string.h"
char *s21_strchr(const char *str, int c) {
  const char *s = str;
  char *result = S21_NULL;
  for (;; s++) {
    if (*s == (char)c) {
      result = (char *)s;
      break;
    }
    if (*s == '\0') break;
  }
  return result;
}