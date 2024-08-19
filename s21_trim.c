#include "s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src && trim_chars) {
    int key_for_left = 0, key_for_right = 0, key_for_left_if = 0,
        key_for_right_if = 0;
    long long int len_src = s21_strlen(src),
                  len_trim_chars = s21_strlen(trim_chars),
                  count_for_check_left = 0, count_for_left_shift = 0,
                  count_for_right_shift = 0, count_for_check_right = 0;
    for (long long int i1 = 0, i2 = len_src - 1; (i1 < len_src) && (i2 >= 0);
         i1++, i2--) {
      for (long long int j = 0; j < len_trim_chars; j++) {
        if (key_for_left == 0 && key_for_left_if == 0) {
          (src[i1] != trim_chars[j])
              ? (count_for_check_left++)
              : (count_for_left_shift++, key_for_left_if = 1);
        }
        if (key_for_right == 0 && key_for_right_if == 0) {
          (src[i2] != trim_chars[j])
              ? (count_for_check_right++)
              : (count_for_right_shift++, key_for_right_if = 1);
        }
      }
      key_for_left_if = 0;  //эти переменные нужны для того чтобы не залазить в
                            //ифы во втором форе. Раньше когда там был один иф
      key_for_right_if =
          0;  //я делал просто брейк, но так как я совместил проверку начала и
              //конца строки в одном форе я создал эти переменные
      (count_for_check_left == len_trim_chars) ? (key_for_left = 1)
                                               : (count_for_check_left = 0);
      (count_for_check_right == len_trim_chars) ? (key_for_right = 1)
                                                : (count_for_check_right = 0);
    }
    if (len_src == count_for_left_shift) count_for_left_shift = 0;  //костыль
    s21_size_t len_final =
        len_src - count_for_left_shift - count_for_right_shift;
    if (len_final > 0) {
      result = malloc((len_final + 1) * sizeof(char));
      s21_strncpy(result, &src[count_for_left_shift], len_final);
      result[len_final] = '\0';
    } else {
      result = malloc(1);
      result[0] = '\0';
    }
  }
  return (void *)result;
}