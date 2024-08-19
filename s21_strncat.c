#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t j = 0;
  s21_size_t i = 0;
  while (dest[j] != '\0') {
    j += 1;
  }
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[j + i] = src[i];
  }
  dest[j + i] = '\0';
  return dest;
}