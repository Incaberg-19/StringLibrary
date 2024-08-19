#include <string.h>

#include "s21_string.h"
char *s21_strtok(char *str, const char *delim) {
  static char *token =
      S21_NULL;  // Статическая переменная для хранения текущей позиции в строке
  char *start = S21_NULL;
  if (str) {
    token = str;  // Инициализация текущего токена
    while (*token != '\0' && s21_strchr(delim, *token) != S21_NULL) {
      token++;
    }
    start = token;  // Запоминаем начало текущего токена
    if (*token != '\0') {
      // Поиск конца текущего токена
      while (*token != '\0' && s21_strchr(delim, *token) == S21_NULL) {
        token++;
      }
      if (*token != '\0') {
        *token = '\0';  // Заменяем разделитель нулевым символом
        token++;  // Переходим к следующему символу после разделителя
      }
    }
  }
  return start;  // Возвращаем указатель на начало текущего токена
}
