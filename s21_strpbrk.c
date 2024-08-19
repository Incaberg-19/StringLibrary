#include "s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
        break;
      }
    }
  }
  return result;
}