#include "s21_string.h"
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (src && str) {
    s21_size_t len_str = s21_strlen(str), len_src = s21_strlen(src), i = 0,
               j = 0, k = 0;
    if (start_index <= len_src) {
      result = malloc(((len_src + len_str + 1) * sizeof(char)));
      while (i != start_index) {
        result[k] = src[i];
        i++, k++;
      }
      while (j != len_str) {
        result[k] = str[j];
        j++, k++;
      }
      while (i != len_src) {
        result[k] = src[i];
        i++, k++;
      }
      result[k] = '\0';
    }
  }
  return (void *)result;
}