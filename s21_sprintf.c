#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *src_str = str;
  va_list arguments;
  va_start(arguments, format);

  char *specificators = "diouxXcspnegGEfF%";
  while (
      *format) {  //пока есть format добавляем в str символ пока не встретим '%'
    if (*format == '%') {
      format++;
      if (*format == '%') {
        *str++ = '%';
        format++;
        continue;
      }
      Spec spec = {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      format = parser_specs(format, &spec, &arguments);
      while (!s21_strchr(specificators, *format)) format++;
      str = parser(format, &spec, &arguments, str);

      // printf("Система счисления %d\n+ %d\n- %d\nШирина %d\nТочность
      // %d\nПробел %d\n0 %d\nРешетка %d\n", spec.numeral_system, spec.plus,
      // spec.minus, spec.width, spec.accuracy, spec.space, spec.zero,
      // spec.sharp);
    } else {
      *str = *format;
      str++;
    }
    format++;
  }
  *str = '\0';
  va_end(arguments);
  return (str - src_str);
}
const char *get_num(const char *format, int *width, va_list *arguments) {
  if (*format == '*') {
    *width = va_arg(*arguments, int);
    format++;
  }

  while (format) {
    if (*format >= '0' && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else {
      break;
    }
    format++;
  }

  return format;
}

const char *get_flags(const char *format, Spec *spec) {
  int break_flag = 0;
  while (*format) {
    switch (*format) {
      case '0':
        spec->zero = 1;
        break;
      case '+':
        spec->plus = 1;
        break;
      case '-':
        spec->minus = 1;
        break;
      case '#':
        spec->sharp = 1;
        break;
      case ' ':
        spec->space = 1;
        break;

      default:
        break_flag = 1;
        break;
    }

    if (break_flag) break;
    format++;
  }

  if (spec->space && spec->plus) {
    spec->space = 0;
  }
  if (spec->zero && spec->minus) {
    spec->zero = 0;
  }
  return format;
}
const char *parser_specs(const char *format, Spec *spec, va_list *arguments) {
  format = get_flags(format, spec);
  format = get_num(format, &spec->width, arguments);
  if (*format == '.') {
    spec->dot = 1;
    spec->zero = 0;
    format = get_num(++format, &spec->accuracy, arguments);
  }
  switch (*format) {
    case 'L':
      spec->lenght = 'L';
      break;
    case 'l':
      spec->lenght = 'l';
      break;
    case 'h':
      spec->lenght = 'h';
      break;
  }
  if (spec->width < 0) {
    spec->width = -spec->width;
    spec->minus = 1;
  }
  return format;
}

char *parser(const char *format, Spec *spec, va_list *arguments, char *str) {
  str = get_specified(format, spec, arguments, str);
  return str;
}

char *get_specified(const char *format, Spec *spec, va_list *arguments,
                    char *str) {
  if (*format == 'd' || *format == 'i') {
    str = print_number(str, spec, arguments);
  } else if (*format == 'c') {
    int symbol = va_arg(*arguments, int);

    str = print_c(str, spec, symbol);
  } else if (*format == 's') {
    str = print_s(str, spec, arguments);
  } else if (*format == 'x' || *format == 'X' || *format == 'o' ||
             *format == 'u') {
    set_num_sistem(spec, *format);
    str = print_u(str, spec, *(format - 1), arguments);
  } else if (*format == 'f' || *format == 'F') {
    set_specs_for_float(spec, format);
    str = print_float_double(str, spec, (format - 1), arguments);
  } else if (*format == 'e' || *format == 'g' || *format == 'G' ||
             *format == 'E') {
    set_specs_for_float(spec, format);
    str = print_eg(str, spec, (format - 1), arguments);
  } else {
    str = print_p(str, spec, arguments);
  }
  return str;
}
char *print_c(char *str, Spec *spec, int symbol) {
  char *pointer = S21_NULL;
  while (spec->width - 1 > 0 && !spec->minus) {
    *str = ' ';
    str++;
    spec->width--;
  }
  str = print_symbol(str, symbol);
  str++;
  while (spec->width - 1 > 0 && spec->minus) {
    *str = ' ';
    str++;
    spec->width--;
  }
  pointer = str;
  return pointer;
}
void set_specs_for_float(Spec *spec, const char *format) {
  if (*format == 'g' || *format == 'G') {
    spec->g = 1;
  } else if (*format == 'e' || *format == 'E') {
    spec->e = 1;
  }
  if (*format == 'G' || *format == 'F' || *format == 'E') {
    spec->up_case = 1;
  }
}

char *print_eg(char *str, Spec *spec, const char *format, va_list *arguments) {
  long double num = 0;
  int e = 0;
  s21_size_t size_num = 0;
  if (*format == 'L') {
    num = (long double)va_arg(*arguments, long double);
  } else {
    num = (double)va_arg(*arguments, double);
  }
  if (spec->g) {
    *spec = cutter(spec, num);
  }
  if (spec->e) {
    e = normalize(spec, &num);
    size_num += 2;
  }
  if (spec->accuracy == 0 && !spec->g) spec->accuracy = 6;
  size_num += get_size_to_eg(spec, num);
  if ((s21_size_t)spec->width > size_num) size_num = spec->width;

  char *buffer = malloc(sizeof(char) * size_num + 1);
  if (buffer) {
    int i = float_double_to_string(buffer, spec, num, size_num, e);  //меееее
    for (int j = i - 1; j >= 0; j--) {
      *str = buffer[j];
      str++;
    }
    free(buffer);
  }
  return str;
}
s21_size_t get_size_to_eg(Spec *spec, long double num) {
  s21_size_t result = 0;
  int acc = spec->accuracy;
  long double tmp_num = num;
  int i = 0, dot = 1;
  long double integer = num;
  long double fraction = modfl(num, &integer);
  for (i = 0; i < acc; i++) {
    if (fabsl(tmp_num - ((int)fraction + integer * powl(10, i))) <= 0.000001)
      break;
    result++;
    tmp_num *= 10;
    fraction *= 10;
  }
  if ((s21_size_t)spec->accuracy > result && !spec->g) result = spec->accuracy;

  if ((spec->g && !result)) dot = 0;
  if (result && (long)integer == 0) result++;
  while ((long)integer) {
    result++;
    integer /= 10;
  }
  if (spec->e) {
    result += 2;
  }
  if (spec->space || spec->plus || num < 0) {
    result++;
    spec->add_size = 1;
  }

  return result + dot;
}

int normalize(Spec *spec, long double *num) {
  int i = 0;
  if (fabsl(*num) > 1) {
    while (fabsl(*num) > 10) {
      *num /= 10;
      i++;
      spec->e = 2;
    }
  } else {
    while (fabsl(*num) < 0.9999999) {
      *num *= 10;
      i++;
      spec->e = 1;
    }
  }
  return i;
}

Spec cutter(Spec *spec, long double num) {
  long double tmp_num = num;
  Spec tmp_spec = *spec;
  int e = normalize(&tmp_spec, &tmp_num);
  if (tmp_spec.accuracy == 0) {
    tmp_spec.accuracy = 5;
  }
  //если степень находится между 4 и 6 то кратчайшая записиь то же число иначе
  //нормализированное
  if ((e >= -4 && tmp_spec.e == 1) || (tmp_spec.e == 2 && e < 6)) {
    tmp_spec.e = 0;
    tmp_spec.accuracy -= e;
  }

  return tmp_spec;
}

void set_num_sistem(Spec *spec, char symbol) {
  if (symbol == 'o') {
    spec->numeral_system = 8;
  } else if (symbol == 'x' || symbol == 'X') {
    spec->numeral_system = 16;
    if (symbol == 'X') {
      spec->up_case = 1;
    }
  }
}

void print_e(int e, s21_size_t *float_double_size, char *str_to_float_double,
             Spec *spec, int *i) {
  int copy_e = e;
  if (str_to_float_double) {
    if (!copy_e) {
      *float_double_size -= add_sym_to_str(
          str_to_float_double, i, get_num_char(copy_e % spec->numeral_system));
    }
    while (copy_e) {
      *float_double_size -= add_sym_to_str(
          str_to_float_double, i, get_num_char(copy_e % spec->numeral_system));
      copy_e /= spec->numeral_system;
    }
    if (e < 10)
      *float_double_size -= add_sym_to_str(str_to_float_double, i, '0');
    if (spec->e == 2 || e == 0) {
      *float_double_size -= add_sym_to_str(str_to_float_double, i, '+');
    } else {
      *float_double_size -= add_sym_to_str(str_to_float_double, i, '-');
    }
    if (spec->up_case) {
      *float_double_size -= add_sym_to_str(str_to_float_double, i, 'E');
    } else {
      *float_double_size -= add_sym_to_str(str_to_float_double, i, 'e');
    }
  }
}
s21_size_t add_sym_to_str(char *str_to_float_double, int *i, char sym) {
  str_to_float_double[*i] = sym;
  *i = *i + 1;
  return 1;
}
char get_num_char(int num) { return num + '0'; }
char *print_s(char *str, Spec *spec, va_list *arguments) {
  char *symbols = va_arg(*arguments, char *);
  int count_space = 0, start_width = spec->width;
  if (!symbols) {
    str = s21_memcpy(str, "(null)", 6);
    str += 6;
  } else {
    if (spec->width < (int)s21_strlen(symbols))
      spec->width = s21_strlen(symbols);
    else {
      count_space = spec->width - s21_strlen(symbols);
    }
    //если точность не указанна
    if (spec->accuracy == 0) spec->accuracy = spec->width;
    //если точность меньше начальной ширины и она указана, меняем кол-во
    //пробелов
    if (spec->accuracy != 0 && spec->accuracy < start_width)
      count_space = start_width - spec->accuracy;

    while (count_space && !spec->minus) {  //пробелы слева
      *str = ' ';
      str++, count_space--;
    }

    while (*symbols != '\0' && spec->accuracy > 0) {
      *str = *symbols;
      str++;
      symbols++;
      spec->accuracy--;
    }

    while (count_space && spec->minus) {  //пробелы справа
      *str = ' ';
      str++, count_space--;
    }
  }
  return str;
}
char *print_symbol(char *str, int symbol) {
  *str = symbol;
  return str;
}
char *print_p(char *str, Spec *spec, va_list *arguments) {
  unsigned long int pointer =
      (unsigned long int)va_arg(*arguments, unsigned long int);
  //адресса записываются в 16-ричной СС, зададим настройки для записи
  spec->numeral_system = 16, spec->sharp = 1, spec->up_case = 0;

  s21_size_t size_to_num = get_buff_size_u_number(spec, pointer);
  char *buffer = malloc(sizeof(char) * (size_to_num + 1));
  if (buffer) {
    int i = unsigned_num_to_string(buffer, spec, pointer, size_to_num);
    for (int j = i - 1; j >= 0; j--) {
      *str = buffer[j];
      str++;
    }

    free(buffer);
  }
  return str;
}

char *print_number(char *str, Spec *spec, va_list *arguments) {
  long int num = 0;
  switch (spec->lenght) {
    case ('l'):
      num = va_arg(*arguments, long int);
      break;
    case ('h'):
      num = (short)va_arg(*arguments, int);
      break;
    default:
      num = (int)va_arg(*arguments, int);
  }
  s21_size_t number_size = get_number_size(spec, num);
  char *buffer = malloc(number_size);
  if (buffer) {
    int number_width = number_to_string(spec, num, buffer, number_size);
    for (int i = number_width - 1; i >= 0; i--) {
      *str = buffer[i];
      str++;
    }

    free(buffer);
  }
  return str;
}
int number_to_string(Spec *spec, long int num, char *buffer, int number_size) {
  long int tmp_num = num, real_num_size = 0;
  int flag_minus = 0, i = 0, num_size = number_size;

  if (tmp_num < 0) {
    tmp_num = -tmp_num;
    flag_minus = 1;
  }
  long tmp_num2 = tmp_num;
  while (tmp_num2) {
    tmp_num2 /= 10;
    real_num_size++;
  }

  if (!tmp_num && buffer && num_size) {
    buffer[i++] = '0';
    num_size--;
  }

  //обработка свободного места в строке
  while (real_num_size < num_size && spec->minus &&
         ((num_size - real_num_size > 1 && flag_minus) || (!flag_minus)) &&
         num_size) {
    buffer[i++] = ' ';
    num_size--;
  }
  while (tmp_num && buffer && num_size) {
    char sym = get_symbol(tmp_num % spec->numeral_system, spec->up_case);
    buffer[i++] = sym;
    num_size--;
    tmp_num /= 10;
  }

  //можем ли мы применить флаг 0
  if (spec->accuracy - i > 0) {  // если  точность больше ширины ставим флаг 0
    spec->accuracy -= i;
    spec->zero = 1;
  } else {
    flag_minus = 1;
    if (num_size == 1 && spec->zero == 1 &&
        spec->add_size == 1) {  //если не осталось место под 0
      spec->zero = 0;
    }
  }
  //обработка флага 0
  while (spec->zero && buffer && (num_size - spec->add_size > 0) &&
         (spec->accuracy || flag_minus)) {
    buffer[i++] = '0';
    num_size--;
    spec->accuracy--;
  }

  //обработка space/-/+/
  if (spec->space && num >= 0 && num_size) {
    buffer[i++] = ' ';
    num_size--;
  }
  if (num > 0 && spec->plus && num_size) {
    buffer[i++] = '+';
    num_size--;
  }
  if (num < 0 && num_size) {
    buffer[i++] = '-';
    num_size--;
  }

  //обработка свободного места в строке
  if (num_size > 0 && !spec->minus) {
    while ((num_size > 0 && !spec->minus) && buffer) {
      buffer[i++] = ' ';
      num_size--;
    }
  }

  return i;
}

char get_symbol(long int num, int up_case) {
  char result = '0';
  switch (num) {
    case 10:
      result = (char)('a' - up_case * 32);
      break;
    case 11:
      result = (char)('b' - up_case * 32);
      break;
    case 12:
      result = (char)('c' - up_case * 32);
      break;
    case 13:
      result = (char)('d' - up_case * 32);
      break;
    case 14:
      result = (char)('e' - up_case * 32);
      break;
    case 15:
      result = (char)('f' - up_case * 32);
      break;
  }
  if (num >= 0 && num <= 9) {
    result = (char)(num + 48);
  }
  return result;
}

s21_size_t get_number_size(Spec *spec, long int num) {
  s21_size_t result = 0;
  long int tmp_num = num;
  if (tmp_num < 0) tmp_num = -tmp_num;
  while (tmp_num) {
    tmp_num /= 10;
    result++;
  }
  if (result == 0 && tmp_num == 0) {
    result++;
  }

  if (spec->space || spec->plus || num < 0) {
    result++;
    spec->add_size = 1;
  }
  if ((s21_size_t)spec->width > result) result = spec->width;
  if ((s21_size_t)spec->accuracy > result) result = spec->accuracy;

  return result;
}

char *print_u(char *str, Spec *spec, char format, va_list *arguments) {
  unsigned long num = 0;
  if (format == 'l')
    num = (unsigned long)va_arg(*arguments, unsigned long int);

  else {
    num = (unsigned int)va_arg(*arguments, unsigned int);
  }
  s21_size_t size_to_num = get_buff_size_u_number(spec, num);
  char *buffer = malloc(sizeof(char) * size_to_num);
  if (buffer) {
    int i = unsigned_num_to_string(buffer, spec, num, size_to_num);
    for (int j = i - 1; j >= 0; j--) {
      *str = buffer[j];
      str++;
    }
    free(buffer);
  }
  return str;
}
s21_size_t get_buff_size_u_number(Spec *spec, long int num) {
  s21_size_t result = 0;
  unsigned long tmp_num = num;
  while (tmp_num) {
    tmp_num /= spec->numeral_system;
    result++;
  }
  if (result == 0) {
    result++;
  }
  if ((s21_size_t)spec->width > result) result = spec->width;
  if ((s21_size_t)spec->accuracy > result) result = spec->accuracy;

  if (spec->sharp && spec->numeral_system == 8) {
    result++;
  } else if (spec->sharp && spec->numeral_system == 16) {
    result += 2;
  }

  return result;
}

int unsigned_num_to_string(char *buffer, Spec *spec, unsigned long num,
                           s21_size_t number_size) {
  unsigned long tmp_num = num;
  s21_size_t tmp_size = number_size;
  int flag_minus = 0, i = 0;

  if ((!tmp_num && (spec->accuracy || spec->width || spec->space)) ||
      (!tmp_num && !spec->accuracy && !spec->width && !spec->dot &&
       !spec->space)) {
    char sym = tmp_num % 10 + '0';
    buffer[i++] = sym;
    tmp_size--;
    tmp_num /= 10;
  }
  while (tmp_num && buffer && tmp_size) {
    char sym = get_symbol(tmp_num % spec->numeral_system, spec->up_case);
    buffer[i++] = sym;
    tmp_size--;
    tmp_num /= spec->numeral_system;
  }
  //можем ли мы применить флаг 0
  if (spec->accuracy - i > 0) {  // если  точность больше ширины ставим флаг 0
    spec->accuracy -= i;
    spec->zero = 1;
  } else {
    flag_minus = 1;
    if (number_size == 1 && spec->zero == 1 &&
        spec->add_size == 1) {  //если не осталось место под 0
      spec->zero = 0;
    }
  }
  //обработка флага 0
  while (spec->zero && buffer && (tmp_size - spec->add_size > 0) &&
         (spec->accuracy || flag_minus)) {
    buffer[i++] = '0';
    tmp_size--;
    spec->accuracy--;
  }

  //обработка space/-/+/
  if (spec->sharp && spec->numeral_system == 8) {
    buffer[i++] = '0';
    tmp_size--;
  }
  if (spec->sharp && spec->numeral_system == 16 && spec->up_case) {
    buffer[i++] = 'X';
    buffer[i++] = '0';
    tmp_size -= 2;
  }
  if (spec->sharp && spec->numeral_system == 16 && !spec->up_case) {
    buffer[i++] = 'x';
    buffer[i++] = '0';
    tmp_size -= 2;
  }

  //обработка свободного места в строке
  if (tmp_size > 0 && !spec->minus) {
    while ((tmp_size > 0 && !spec->minus) && buffer) {
      buffer[i++] = ' ';
      tmp_size--;
    }
  }

  return i;
}

char *print_float_double(char *str, Spec *spec, const char *format,
                         va_list *arguments) {
  long double num = 0;
  int e = 0;
  if (*format == 'L') {
    num = va_arg(*arguments, long double);
  } else {
    num = (double)va_arg(*arguments, double);
  }

  if (spec->accuracy == 0) spec->accuracy = 6;
  s21_size_t num_size = get_size_float_double(spec, &num);
  char *buffer = malloc(sizeof(char) * num_size);
  if (buffer) {
    int i = float_double_to_string(buffer, spec, num, num_size, e);  //меееее
    for (int j = i - 1; j >= 0; j--) {
      *str = buffer[j];
      str++;
    }
    free(buffer);
  }
  return str;
}

int float_double_to_string(char *buffer, Spec *spec, long double num,
                           s21_size_t num_size_o, int e) {
  int flag = 0, i = 0, flag_to_dot = 0;
  s21_size_t num_size = num_size_o;
  long double tmp_num = num;
  if (tmp_num && !isnan(tmp_num) && !isinf(tmp_num)) {
    if (spec->e) print_e(e, &num_size, buffer, spec, &i);

    if (tmp_num < 0) {
      flag = 1;
      tmp_num = -tmp_num;
    }
    long double integer = tmp_num;
    int accuracy = spec->accuracy;
    long double fraction = modfl(tmp_num, &integer);
    long double tmp_fraction = fraction;

    //умножаем число на 10 пока не появится >= 1 или пока не будет 15 умножений
    for (int i = 0; i < 15 && (long)tmp_fraction == 0; i++, tmp_fraction *= 10)
      ;

    //обработка G и округление
    if ((long)tmp_fraction == 0 && spec->g) accuracy = 0;
    if (!accuracy && fraction * 10 > 4) integer++;
    while (accuracy) {
      fraction *= 10;
      accuracy--;
    }
    if (fmodl(fabsl(fraction) * 10, 10.0) > 4) fraction = roundl(fraction);
    //убираем лишние нули при флаге g
    if (spec->g) {
      while ((long)fraction % 10 == 0 && spec->accuracy > 0 &&
             (long)fraction != 0) {
        fraction /= 10;
        accuracy++;
      }
    }

    if ((long)fraction == 0) flag_to_dot = 1;
    while ((long)fraction) {
      buffer[i++] = (long)fraction % 10 + '0';
      num_size--;
      fraction /= 10;
    }
    if (!flag_to_dot) {
      buffer[i++] = '.';
      num_size--;
    }

    if (num_size_o != num_size && !((long)integer)) {
      buffer[i++] = '0';
      num_size--;
    }
    while ((long)integer != 0) {
      buffer[i++] = (long)integer % 10 + '0';
      num_size--;
      integer /= 10;
    }

    //можем ли мы применить флаг 0
    if (spec->accuracy - i > 0) {  // если  точность больше ширины ставим флаг 0
      spec->accuracy -= i;
      spec->zero = 1;
    } else {
      if (num_size == 1 && spec->zero == 1 &&
          spec->add_size == 1) {  //если не осталось место под 0
        spec->zero = 0;
      }
    }
    //обработка флага 0
    while (spec->zero && buffer && num_size != 0 && (spec->accuracy || flag)) {
      if (num_size && spec->add_size) {
        break;
      }
      buffer[i++] = '0';
      num_size--;
      spec->accuracy--;
    }

    //обработка space/-/+/
    if (flag && num_size) {
      buffer[i++] = '-';
      num_size--;
    }
    if (spec->space && tmp_num >= 0 && num_size) {
      buffer[i++] = ' ';
      num_size--;
    }
    if (num > 0 && spec->plus && num_size) {
      buffer[i++] = '+';
      num_size--;
    }

    //обработка свободного места в строке
    if (num_size > 0 && !spec->minus) {
      while ((num_size > 0 && !spec->minus) && (buffer + i)) {
        buffer[i++] = ' ';
        num_size--;
      }
    }
    if (!spec->minus && num_size > 0) {
      while (num_size - spec->add_size > 0 && (buffer + i)) {
        if (spec->g && spec->width < spec->accuracy) break;
        buffer[i++] = ' ';
        num_size--;
      }
    }
  } else {
    if (isnan(tmp_num)) {
      buffer = s21_memcpy(buffer, "nan", 3);
      i += 3;
    } else if (isinf(tmp_num)) {
      buffer = s21_memcpy(buffer, "fni", 3);
      i += 3;
    } else {
      buffer = s21_memcpy(buffer, "000000.0", 8);
      i += 8;
    }
  }
  return i;
}
s21_size_t get_size_float_double(Spec *spec, long double *num) {
  s21_size_t result = 0;
  long double tmp_num = *num;
  int i = 0, dot = 1;
  if (tmp_num && !isnan(tmp_num) && !isinf(tmp_num)) {
    long double integer = *num;
    long double fraction = modfl(*num, &integer);
    for (i = 0; i < spec->accuracy; i++) {
      if (fabsl(tmp_num - ((int)fraction + integer * powl(10, i))) <= 0.000001)
        break;
      result++;
      tmp_num *= 10;
      fraction *= 10;
    }
    if (!result) dot = 0;
    if ((s21_size_t)spec->accuracy > result) result = spec->accuracy;
    if (result && (long)integer == 0) result++;

    while ((long)integer) {
      result++;
      integer /= 10;
    }
    if ((s21_size_t)spec->width > result) result = spec->width;
    if ((s21_size_t)spec->accuracy > result) result = spec->accuracy;

    if (spec->space || spec->plus || *num < 0) {
      result++;
      spec->add_size = 1;
    }

  } else {
    if (isnan(tmp_num)) {
      result = 3;
    } else if (isinf(tmp_num)) {
      result = 3;
    } else {
      result = 8;
    }
    dot = 0;
  }
  return result + dot;
}