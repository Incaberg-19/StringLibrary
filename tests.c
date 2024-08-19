#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strlen_test) {
  ck_assert_int_eq(s21_strlen("qwerty"), strlen("qwerty"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAA"
                              "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\t\t"),
                   strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAA"
                          "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\t\t"));
}
END_TEST

START_TEST(strerror_test) {
  ck_assert_str_eq(s21_strerror(123), strerror(123));
  ck_assert_str_eq(s21_strerror(134), strerror(134));
  ck_assert_str_eq(s21_strerror(-134), strerror(-134));
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(-0), strerror(-0));
}
END_TEST

START_TEST(tolower_test) {
  char *ptr = s21_to_lower("123dgfdfGDFGDFGDSFDBVCcfb/dfgsdf['gfs[e;r[wedf]]]");
  ck_assert_str_eq(ptr, "123dgfdfgdfgdfgdsfdbvccfb/dfgsdf['gfs[e;r[wedf]]]");
  free(ptr);
  ptr = s21_to_lower("");
  ck_assert_str_eq(ptr, "");
  free(ptr);
  ptr = s21_to_lower("aaaaa");
  ck_assert_str_eq(ptr, "aaaaa");
  free(ptr);
  ptr = s21_to_lower("AAAAAA");
  ck_assert_str_eq(ptr, "aaaaaa");
  free(ptr);
  char *str = S21_NULL;
  ck_assert_ptr_null(s21_to_lower(str));
  free(str);
}
END_TEST

START_TEST(toupper_test) {
  char *ptr = s21_to_upper("123dgfdfbcfb/dfgsdf['gfs[e;r[wedf]]]");
  ck_assert_str_eq(ptr, "123DGFDFBCFB/DFGSDF['GFS[E;R[WEDF]]]");
  free(ptr);
  ptr = s21_to_upper("");
  ck_assert_str_eq(ptr, "");
  free(ptr);
  ptr = s21_to_upper("aaaaa");
  ck_assert_str_eq(ptr, "AAAAA");
  free(ptr);
  ptr = s21_to_upper("AAAAAA");
  ck_assert_str_eq(ptr, "AAAAAA");
  free(ptr);
  ptr = s21_to_upper("1");
  ck_assert_str_eq(ptr, "1");
  free(ptr);
  ptr = s21_to_upper("a");
  ck_assert_str_eq(ptr, "A");
  free(ptr);
  char *str = s21_to_upper("123ABcD");
  char *str2 = S21_NULL;
  ck_assert_ptr_null(str2);
  ck_assert_str_eq(str, "123ABCD");
  free(str2);
  free(str);
}
END_TEST

START_TEST(strstr_test) {
  ck_assert_str_eq(s21_strstr("12456789", "67"), strstr("12456789", "67"));
  ck_assert_ptr_null(s21_strstr("123", "456"));
}
END_TEST

START_TEST(strstr_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_3) {
  char s1[] = "Hello, world!";
  char s2[] = "!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_4) {
  char s1[] =
      "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!";
  char s2[] = "world";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_5) {
  char s1[] = "";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_6) {
  char s1[] = "Hello, world!";
  char s2[] = "";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_7) {
  char s1[] = "";
  char s2[] = "Hello, P!";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_8) {
  char s1[] = "69917020";
  char s2[] = "0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_9) {
  char s1[] = "69917020";
  char s2[] = "\0";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_10) {
  char s1[] = "69917020";
  char s2[] = "32859160 8v3489-74 tvc4y8719c n4[nqymu uv 4vm9cw";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_11) {
  char s1[] = "1   345 345 345 345 345";
  char s2[] = "345";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_12) {
  char s1[] = "sususususpicioussusususpicious";
  char s2[] = "susp";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(strstr_13) {
  char s1[] = "sus";
  char s2[] = "suspi";
  ck_assert_pstr_eq(strstr(s1, s2), s21_strstr(s1, s2));
}
END_TEST

START_TEST(trim_test) {
  char *a = s21_trim("123abc456", "123456");
  ck_assert_str_eq(a, "abc");
  free(a);
  a = s21_trim("123ab23c456", "123456");
  ck_assert_str_eq(a, "ab23c");
  free(a);
  a = s21_trim("123abc456", "11111");
  ck_assert_str_eq(a, "23abc456");
  free(a);
  a = s21_trim("11111abc456", "1");
  ck_assert_str_eq(a, "abc456");
  free(a);
  a = s21_trim("11111abc456", "789");
  ck_assert_str_eq(a, "11111abc456");
  free(a);
  a = s21_trim("11111abc456", "");
  ck_assert_str_eq(a, "11111abc456");
  free(a);
  a = s21_trim("", "");
  ck_assert_str_eq(a, "");
  free(a);
  char *str = S21_NULL;
  a = s21_trim(str, "");
  ck_assert_ptr_null(a);
  free(a);
}
END_TEST

START_TEST(test_insert_1) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  free(s2);
}
END_TEST

START_TEST(test_insert_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_4) {
  char s1[30] = "abcdefghij";
  char s3[] = "\'I WAS HERE\'";
  char s4[] = "abc\'I WAS HERE\'defghij";
  s21_size_t num = 3;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = S21_NULL;
  s21_size_t num = 10;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_6) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char *s4 = S21_NULL;
  s21_size_t num = -1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_9) {
  char s1[] = "wtf";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_10) {
  char s1[] = "";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s2, s4);
  if (s2) free(s2);
}
END_TEST

START_TEST(strncmp_test) {
  ck_assert_int_eq(s21_strncmp("123", "456", 3), strncmp("123", "456", 3));
  ck_assert_int_eq(s21_strncmp("193", "456", 3), strncmp("193", "456", 3));
  ck_assert_int_eq(s21_strncmp("123", "459", 3), strncmp("123", "459", 3));
  ck_assert_int_eq(s21_strncmp("", "459", 3), strncmp("", "459", 3));
  ck_assert_int_eq(s21_strncmp("", "", 3), strncmp("", "", 3));
  ck_assert_int_eq(s21_strncmp("123", "459", 0), strncmp("123", "459", 0));
}
END_TEST

START_TEST(strcspn_test) {
  ck_assert_int_eq(s21_strcspn("abcdef", "xyz"), strcspn("abcdef", "xyz"));
  ck_assert_int_eq(s21_strcspn("abcdexyz", "xyz"), strcspn("abcdexyz", "xyz"));
  ck_assert_int_eq(s21_strcspn("", "xyz"), strcspn("", "xyz"));
  ck_assert_int_eq(s21_strcspn("abcde", ""), strcspn("abcde", ""));
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
  ck_assert_int_eq(s21_strcspn("abcde", "xyz"), strcspn("abcde", "xyz"));
}
END_TEST

START_TEST(strpbrk_test) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "xyz"), strpbrk("abcdef", "xyz"));
  ck_assert_ptr_eq(s21_strpbrk("abxcdef", "xyz"), strpbrk("abxcdef", "xyz"));
}
END_TEST

START_TEST(strncpy_test) {
  char a[10] = "123456";
  char b[10] = "45";
  ck_assert_str_eq(s21_strncpy(a, b, 1), strncpy(a, b, 1));
  ck_assert_str_eq(s21_strncpy(b, a, 2), strncpy(b, a, 2));
}
END_TEST

START_TEST(strrchr_test) {
  char a[10] = "123456";
  char b[10] = "452";
  ck_assert_ptr_null(s21_strrchr(a, 2));
  ck_assert_ptr_null(s21_strrchr(b, 5));
  ck_assert_str_eq(s21_strrchr(b, 50), strrchr(b, 50));
  ck_assert_str_eq(s21_strrchr(a, 50), strrchr(a, 50));
}
END_TEST

START_TEST(strrchr_1) {
  char s[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_2) {
  char s[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_3) {
  char s[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_4) {
  char s[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_5) {
  char s[] = "Hello, Polina!";
  int ch = 'P';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_6) {
  char s[] = "Hello, world!";
  int ch = 'w';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_7) {
  char s[] = "Hello, world!";
  int ch = '0';
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(strrchr_8) {
  char s[] = "Hello, world!";
  int ch = 'm';
  // ck_assert_ptr_null(s21_strrchr(s, ch));
  ck_assert_pstr_eq(strrchr(s, ch), s21_strrchr(s, ch));
}
END_TEST

START_TEST(sprintf_test) {
  char str1[100];
  char str2[100];

  char *formatd = "integer %d%%";
  char *formats = "string %s";
  char *formats_space = "string % s";
  char *formats82 = "string %8.2s";
  char *formats28 = "string %2.8s";
  char *formatc = "char %c";
  char *formatc_width = "char %4c";
  char *formatc_width_minus = "char %-3c";
  char *formatu = "u %#lu";
  char *formatu_acc = "u %10.lu";
  char *formatx_hash = "x %#X";
  char *formatx = "x %25.20x";
  char *formatX = "X %010X";
  char *formatX_space_plus = "X % +X";
  char *formatp = "p %p";
  char *test_string = "qwerty";
  int integer = 12345;
  float fl = 123.456;
  long double with_dot = 123.456;
  char symb = 'q';
  int a = s21_sprintf(str1, formatd, integer);
  int b = sprintf(str2, formatd, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_minusfive = "integer %-5d";
  a = s21_sprintf(str1, formatd_minusfive, integer);
  b = sprintf(str2, formatd_minusfive, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatc_width_minus, symb);
  b = sprintf(str2, formatc_width_minus, symb);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_widthmore = "integer %0-d";
  a = s21_sprintf(str1, formatd_widthmore, integer);
  b = sprintf(str2, formatd_widthmore, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatd_widthmore, 0);
  b = sprintf(str2, formatd_widthmore, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_space_otrits = "integer % d";
  integer = -12345;
  a = s21_sprintf(str1, formatd_space_otrits, integer);
  b = sprintf(str2, formatd_space_otrits, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
  integer = 12345;
  char *formatd_null = "integer %1d";
  a = s21_sprintf(str1, formatd_null, 0);
  b = sprintf(str2, formatd_null, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatLf = "long double %Lf";
  a = s21_sprintf(str1, formatLf, with_dot);
  b = sprintf(str2, formatLf, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatLf, with_dot);
  b = sprintf(str2, formatLf, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_space = "long double % d";
  a = s21_sprintf(str1, formatd_space, integer);
  b = sprintf(str2, formatd_space, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatLf_charpsharp = "long double %%d ";
  a = s21_sprintf(str1, formatLf_charpsharp, integer);
  b = sprintf(str2, formatLf_charpsharp, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  with_dot = 134.5456;
  a = s21_sprintf(str1, formatLf, with_dot);
  b = sprintf(str2, formatLf, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatF = "float %F";
  a = s21_sprintf(str1, formatF, fl);
  b = sprintf(str2, formatF, fl);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatLf_star = "long double %*Lf";
  a = s21_sprintf(str1, formatLf_star, with_dot, 2);
  b = sprintf(str2, formatLf_star, with_dot, 2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatLf_star, with_dot, -2);
  b = sprintf(str2, formatLf_star, with_dot, -2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatLf_minus = "long double %-Lf";
  with_dot = -234.645;
  a = s21_sprintf(str1, formatLf_minus, with_dot);
  b = sprintf(str2, formatLf_minus, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf = "long double %lf";
  a = s21_sprintf(str1, formatlf, 0.0);
  b = sprintf(str2, formatlf, 0.0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf_cr = "long double % Lf";
  with_dot = 123.43;
  a = s21_sprintf(str1, formatlf_cr, with_dot);
  b = sprintf(str2, formatlf_cr, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf_cr2 = "long double %010.6Lf";
  with_dot = 12345.6;
  a = s21_sprintf(str1, formatlf_cr2, with_dot);
  b = sprintf(str2, formatlf_cr2, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatLf, fabsl(NAN));
  b = sprintf(str2, formatLf, fabsl(NAN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatLf, fabsl(INFINITY));
  b = sprintf(str2, formatLf, fabsl(INFINITY));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatLf, with_dot);
  b = sprintf(str2, formatLf, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf_zero = "long double %05Lf";
  a = s21_sprintf(str1, formatlf_zero, with_dot);
  b = sprintf(str2, formatlf_zero, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf_space_ni = "long double % Lf";
  with_dot = -123.456;
  a = s21_sprintf(str1, formatlf_space_ni, with_dot);
  b = sprintf(str2, formatlf_space_ni, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatlf86 = "long double %8.6Lf";
  with_dot = 123.456789;
  a = s21_sprintf(str1, formatlf86, with_dot);
  b = sprintf(str2, formatlf86, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatLe = "long double %Le";
  with_dot = 1.23456789218999999999;
  a = s21_sprintf(str1, formatLe, with_dot);
  b = sprintf(str2, formatLe, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formateg = "long double %Le %+Lg";
  a = s21_sprintf(str1, formateg, with_dot, with_dot);
  b = sprintf(str2, formateg, with_dot, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatede = " double %20e";

  a = s21_sprintf(str1, formatede, 12.45);
  b = sprintf(str2, formatede, 12.45);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_spase_plusnum = "long double % +Lf";
  with_dot = -123.456;
  a = s21_sprintf(str1, formatd_spase_plusnum, with_dot);
  b = sprintf(str2, formatd_spase_plusnum, with_dot);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatedg_acc = " double %6g";

  a = s21_sprintf(str1, formatedg_acc, 12.4567);
  b = sprintf(str2, formatedg_acc, 12.4567);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatedE = " double %E";
  a = s21_sprintf(str1, formatedE, 0.123456);
  b = sprintf(str2, formatedE, 0.123456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatedE, 123456789777.2);
  b = sprintf(str2, formatedE, 123456789777.2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatedG = " double %lG";
  a = s21_sprintf(str1, formatedG, -0.1234);
  b = sprintf(str2, formatedG, -0.1234);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatedG, 12.345);
  b = sprintf(str2, formatedG, 12.345);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatedG, 0.3456);
  b = sprintf(str2, formatedG, 0.3456);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  integer = 123;
  char *formatd_sharp = "integer %#d";
  a = s21_sprintf(str1, formatd_sharp, integer);
  b = sprintf(str2, formatd_sharp, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
  char *formatd_width = "integer %8d";
  a = s21_sprintf(str1, formatd_width, 123);
  b = sprintf(str2, formatd_width, 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
  char *formatd_width_acc = "integer %2.4d";
  a = s21_sprintf(str1, formatd_width_acc, 123);
  b = sprintf(str2, formatd_width_acc, 123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_plus = "integer %+d";
  integer = -12345;
  a = s21_sprintf(str1, formatd_plus, integer);
  b = sprintf(str2, formatd_plus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_zero_minus = "integer %0-d";
  a = s21_sprintf(str1, formatd_zero_minus, integer);
  b = sprintf(str2, formatd_zero_minus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formato = "cringe %#o";
  a = s21_sprintf(str1, formato, 0x11345);
  b = sprintf(str2, formato, 0x11345);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_spase_plus = "integer % +i";
  integer = -123;
  a = s21_sprintf(str1, formatd_spase_plus, integer);
  b = sprintf(str2, formatd_spase_plus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  integer = 12345;
  a = s21_sprintf(str1, formatd_plus, integer);
  b = sprintf(str2, formatd_plus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatdh = "integer %hd";
  short int shorter = 12;
  a = s21_sprintf(str1, formatdh, shorter);
  b = sprintf(str2, formatdh, shorter);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_minus = "integer %-d";
  integer = -1234;
  a = s21_sprintf(str1, formatd_minus, integer);
  b = sprintf(str2, formatd_minus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_five = "integer %5d";
  a = s21_sprintf(str1, formatd_five, 0);
  b = sprintf(str2, formatd_five, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatd_five, 0);
  b = sprintf(str2, formatd_five, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  integer = 1234;
  a = s21_sprintf(str1, formatd_minus, integer);
  b = sprintf(str2, formatd_minus, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_spase = "integer % .d";
  integer = -1234;
  a = s21_sprintf(str1, formatd_spase, integer);
  b = sprintf(str2, formatd_spase, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_zero = "integer %0d";
  integer = -1234;
  a = s21_sprintf(str1, formatd_zero, integer);
  b = sprintf(str2, formatd_zero, integer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  char *formatd_long = "integer %ld";
  long longer = 1234567890;
  a = s21_sprintf(str1, formatd_long, longer);
  b = sprintf(str2, formatd_long, longer);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formats_space, test_string);
  b = sprintf(str2, formats_space, test_string);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formats, test_string);
  b = sprintf(str2, formats, test_string);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
  char *formats_minus = "string %-22s";
  a = s21_sprintf(str1, formats_minus, test_string);
  b = sprintf(str2, formats_minus, test_string);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formats82, test_string);
  b = sprintf(str2, formats82, test_string);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formats28, "qw");
  b = sprintf(str2, formats28, "qw");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formats, S21_NULL);
  b = sprintf(str2, formats, S21_NULL);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatu, 0x15387134);
  b = sprintf(str2, formatu, 0x15387134);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatx, 0);
  b = sprintf(str2, formatx, 0);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatu, 0x15abcdef3);
  b = sprintf(str2, formatu, 0x15abcdef3);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatx, 15454);
  b = sprintf(str2, formatx, 15454);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatx, 0xabcd2ef);
  b = sprintf(str2, formatx, 0xabcd2ef);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatX, 0x15387134);
  b = sprintf(str2, formatX, 0x15387134);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatc, 'q');
  b = sprintf(str2, formatc, 'q');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatx_hash, 0x15387134);
  b = sprintf(str2, formatx_hash, 0x15387134);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatX_space_plus, 0x15387134);
  b = sprintf(str2, formatX_space_plus, 0x15387134);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatc_width, 'q');
  b = sprintf(str2, formatc_width, 'q');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);

  a = s21_sprintf(str1, formatp, 0x1343515);
  b = sprintf(str2, formatp, 0x1343515);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
  a = s21_sprintf(str1, formatu_acc, 0x123);
  b = sprintf(str2, formatu_acc, 0x123);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(memchr_test) {
  char array[] = {"1234567890"};
  ck_assert_pstr_eq(s21_memchr(array, '1', 10), memchr(array, '1', 10));
  ck_assert_pstr_eq(s21_memchr(array, '9', 5), memchr(array, '9', 5));
}
END_TEST

START_TEST(memcmp_test) {
  char array1[] = {"123"};
  char array2[] = {"12345"};
  char array3[] = {"321"};
  ck_assert_int_eq(s21_memcmp(array1, array2, 3), memcmp(array1, array2, 3));
  ck_assert_int_eq(s21_memcmp(array1, array2, 5), memcmp(array1, array2, 5));
  ck_assert_int_eq(s21_memcmp(array1, array3, 3), memcmp(array1, array3, 3));
}
END_TEST

START_TEST(memcpy_test) {
  char array1[5];
  char array2[5] = "1234";
  char array3[5];
  char array4[5] = "1234";
  s21_memcpy(array1, array2, 5);
  memcpy(array3, array4, 5);
  ck_assert_str_eq(array1, array3);
}
END_TEST

START_TEST(memset_test) {
  char array1[5] = {};
  char array2[5] = {};
  char symbol = 'c';
  s21_memset(array1, symbol, 4);
  memset(array2, symbol, 4);
  ck_assert_str_eq(array1, array2);
}
END_TEST

START_TEST(strchr_test) {
  char array1[5] = {"1234"};
  ck_assert_str_eq(s21_strchr(array1, '3'), strchr(array1, '3'));
  ck_assert_ptr_null(s21_strchr(array1, '0'));
}
END_TEST

START_TEST(strncat_test) {
  char array1[10] = {"1234"};
  char array2[5] = {"5678"};
  char array3[10] = {"1234"};
  char array4[5] = {"5678"};
  ck_assert_str_eq(s21_strncat(array1, array2, 3), strncat(array3, array4, 3));
}
END_TEST

START_TEST(strtok_test) {
  char *a = S21_NULL;
  char str[13] = "hello world";
  char *token1;
  char *token2;
  strcpy(str, "hello,,world");
  token1 = s21_strtok(str, ",");
  token2 = strtok(str, ",");
  ck_assert_str_eq(token1, token2);
  token1 = s21_strtok(a, " ");
  ck_assert_ptr_null(token1);
  token1 = s21_strtok(" ", " ");
  token1 = s21_strtok(str, "h");
  token2 = strtok(str, "h");
  ck_assert_str_eq(token1, token2);
  token1 = s21_strtok(a, a);
  ck_assert_ptr_null(token1);

  char str12[] = "School-21";
  char *tok1 = s21_strtok(str12, "-");
  char *tok2 = strtok(str12, "-");
  char *tok3 = s21_strtok(str12, "");
  char *tok4 = strtok(str12, "");
  char *tok5 = s21_strtok(str12, "oo");
  char *tok6 = strtok(str12, "oo");
  char *tok7 = s21_strtok(str12, "Sc");
  char *tok8 = strtok(str12, "Sc");
  char *tok9 = s21_strtok(str12, "21");
  char *tok10 = strtok(str12, "21");

  ck_assert_msg(!strcmp(tok1, tok2), "1st strtok test failed");
  ck_assert_msg(!strcmp(tok3, tok4), "2nd strtok test failed");
  ck_assert_msg(!strcmp(tok5, tok6), "3rd strtok test failed");
  ck_assert_msg(!strcmp(tok7, tok8), "4rth strtok test failed");
  ck_assert_msg(!strcmp(tok9, tok10), "5th strtok test failed");
}
END_TEST

START_TEST(strchr_1) {
  char s[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_2) {
  char s[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_3) {
  char s[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_4) {
  char s[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_5) {
  char s[] = "Hello, Polina!";
  int ch = 'P';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_6) {
  char s[] = "Hello, world!";
  int ch = 'w';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_7) {
  char s[] = "Hello, world!";
  int ch = '0';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr_8) {
  char s[] = "Hello, world!";
  int ch = 'm';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *suite = suite_create("s21_string+");
  TCase *tcase = tcase_create("s21_string+");
  tcase_add_test(tcase, trim_test);
  tcase_add_test(tcase, strchr_1);
  tcase_add_test(tcase, strchr_2);
  tcase_add_test(tcase, strchr_3);
  tcase_add_test(tcase, strchr_4);
  tcase_add_test(tcase, strchr_5);
  tcase_add_test(tcase, strchr_6);
  tcase_add_test(tcase, strchr_7);
  tcase_add_test(tcase, strchr_8);
  tcase_add_test(tcase, strstr_1);
  tcase_add_test(tcase, strstr_2);
  tcase_add_test(tcase, strstr_3);
  tcase_add_test(tcase, strstr_4);
  tcase_add_test(tcase, strstr_5);
  tcase_add_test(tcase, strstr_6);
  tcase_add_test(tcase, strstr_7);
  tcase_add_test(tcase, strstr_8);
  tcase_add_test(tcase, strstr_9);
  tcase_add_test(tcase, strstr_10);
  tcase_add_test(tcase, strstr_11);
  tcase_add_test(tcase, strstr_12);
  tcase_add_test(tcase, strstr_13);
  tcase_add_test(tcase, strlen_test);
  tcase_add_test(tcase, strerror_test);
  tcase_add_test(tcase, tolower_test);
  tcase_add_test(tcase, toupper_test);
  tcase_add_test(tcase, strstr_test);
  tcase_add_test(tcase, strncmp_test);
  tcase_add_test(tcase, strcspn_test);
  tcase_add_test(tcase, strpbrk_test);
  tcase_add_test(tcase, strrchr_test);
  tcase_add_test(tcase, strncpy_test);
  tcase_add_test(tcase, strrchr_1);
  tcase_add_test(tcase, strrchr_2);
  tcase_add_test(tcase, strrchr_3);
  tcase_add_test(tcase, strrchr_4);
  tcase_add_test(tcase, strrchr_5);
  tcase_add_test(tcase, strrchr_6);
  tcase_add_test(tcase, strrchr_7);
  tcase_add_test(tcase, strrchr_8);
  tcase_add_test(tcase, test_insert_1);
  tcase_add_test(tcase, test_insert_2);
  tcase_add_test(tcase, test_insert_3);
  tcase_add_test(tcase, test_insert_4);
  tcase_add_test(tcase, test_insert_5);
  tcase_add_test(tcase, test_insert_6);
  tcase_add_test(tcase, test_insert_7);
  tcase_add_test(tcase, test_insert_8);
  tcase_add_test(tcase, test_insert_9);
  tcase_add_test(tcase, test_insert_10);
  tcase_add_test(tcase, memchr_test);
  tcase_add_test(tcase, memcmp_test);
  tcase_add_test(tcase, memcpy_test);
  tcase_add_test(tcase, memset_test);
  tcase_add_test(tcase, strchr_test);
  tcase_add_test(tcase, strncat_test);
  tcase_add_test(tcase, strtok_test);
  tcase_add_test(tcase, sprintf_test);
  suite_add_tcase(suite, tcase);
  return suite;
}

int main() {
  Suite *s = s21_string_suite();
  SRunner *suite_runner = srunner_create(s);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return failed ? 1 : 0;
}
