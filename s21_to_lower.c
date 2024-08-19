#include "s21_string.h"
void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  void *pointer = S21_NULL;
  if (str) {  //если строка не равна NULL
    s21_size_t len = s21_strlen(str);
    result = malloc(len * sizeof(char) + 1);
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {  //проверяем на букавки
        result[i] = (int)str[i] + 32;  //возводим в нижний регистр
      } else {
        result[i] = str[i];
      }
    }
    result[len] = '\0';  //в конец строки ставим соответствующий символ
    pointer = &result[0];
  }
  return pointer;
}