
#include "s21_string.h"
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *s1 = src;
  unsigned char *s2 = dest;
  for (s21_size_t i = 0; i < n; i++) {
    s2[i] = s1[i];
  }
  return s2;
}
