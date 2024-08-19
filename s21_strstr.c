#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  const char *buffer = S21_NULL;
  if (haystack && needle) {
    s21_size_t k = 0, key_for_first_progon = 0,
               len_haystack = s21_strlen(haystack),
               len_needle = s21_strlen(needle);
    if (len_needle == 0) {
      buffer = &haystack[0];
      result = (char *)buffer;
    }
    for (s21_size_t i = 0; (i < len_haystack + 1); i++) {
      if (haystack[i] == needle[k] && haystack[i] != '\0') {
        if (key_for_first_progon == 0) {
          buffer = &haystack[i];
          key_for_first_progon = 1;
        }
        k++;
      } else {
        if (k == len_needle) {
          result = (char *)buffer;
          break;
        } else {
          i = i - k;
          k = 0;
          key_for_first_progon = 0;
        }
      }
    }
  }
  return result;
}