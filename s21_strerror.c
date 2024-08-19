#include "s21_string.h"
char* s21_strerror(int errnum) {
  char* result = S21_NULL;
  if (errnum <= MAX_LIST && errnum >= MIN_LIST) {
    result = (char*)list_for_errors[errnum];
  } else {
    static char unknown_error[14 + 11];  // Используем размер известной строки
    s21_strncpy(unknown_error, "Unknown error ", 14);
    s21_sprintf(&unknown_error[14], "%d", errnum);
    result = &unknown_error[0];
  }
  return result;
}
