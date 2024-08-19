#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include "s21_string.h"

typedef struct {
  int numeral_system;
  int plus;
  int minus;
  int width;
  int accuracy;
  int space;
  int sharp;
  int zero;
  int dot;
  int lenght;
  int add_size;
  int up_case;
  int g;
  int e;

} Spec;

const char *get_num(const char *format, int *width, va_list *arguments);
const char *get_flags(const char *format, Spec *spec);
const char *parser_specs(const char *format, Spec *spec, va_list *arguments);
char *print_symbol(char *str, int symbol);
char *print_s(char *str, Spec *spec, va_list *arguments);
char *print_u(char *str, Spec *spec, char format, va_list *arguments);
char *parser(const char *format, Spec *spec, va_list *arguments, char *str);
char *get_specified(const char *format, Spec *spec, va_list *arguments,
                    char *str);
char *print_number(char *str, Spec *spec, va_list *arguments);
int number_to_string(Spec *spec, long int num, char *buffer, int number_size);
char get_symbol(long int num, int up_case);
s21_size_t get_number_size(Spec *spec, long int num);
int unsigned_num_to_string(char *buffer, Spec *spec, unsigned long num,
                           s21_size_t number_size);
s21_size_t get_buff_size_u_number(Spec *spec, long int num);
int float_double_to_string(char *buffer, Spec *spec, long double num,
                           s21_size_t num_size, int e);
void set_specs_for_float(Spec *spec, const char *format);
Spec cutter(Spec *spec, long double num);
s21_size_t add_sym_to_str(char *str_to_float_double, int *i, char sym);
char get_num_char(int num);
int normalize(Spec *spec, long double *num);
s21_size_t get_size_to_eg(Spec *spec, long double num);
s21_size_t get_size_float_double(Spec *spec, long double *num);
char *print_eg(char *str, Spec *spec, const char *format, va_list *arguments);
void set_num_sistem(Spec *spec, char symbol);
char *print_c(char *str, Spec *spec, int symbol);
char *print_p(char *str, Spec *spec, va_list *arguments);
void print_e(int e, s21_size_t *float_double_size, char *str_to_float_double,
             Spec *spec, int *i);
char *print_float_double(char *str, Spec *spec, const char *format,
                         va_list *arguments);

#endif
