#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  *str = 0;
  va_list arg;
  va_start(arg, format);
  while (*format) {
    char *p = s21_strchr(format, '%');
    if (!p) {
      s21_strncat(str, format, s21_strlen(format));
      format += s21_strlen(format);
    } else {
      s21_strncat(str, format, p - format);
      format = p + 1;
      struct specification specification = {{0}, 0, -1, 0, 0};
      struct specification *spec = &specification;
      format += write_specification(spec, format, arg);
      char *arg_str = type_to_string(spec, arg);
      s21_strncat(str, arg_str, s21_strlen(arg_str));
      free(arg_str);
    }
  }
  va_end(arg);
  return s21_strlen(str);
}

int write_specification(struct specification *spec, const char *form,
                        va_list arg) {
  char flags[6] = "-+ #0";
  char length[6] = "hlL";
  const char *format = form;
  int i = 0;
  for (; s21_strchr(flags, *format); i++) spec->flag[i] = *(format++);
  spec->flag[i] = 0;
  if (is_digit(*format)) {
    spec->width = str_to_int(format, 0);
    while (is_digit(*format)) format++;
  } else if (*format == '*') {
    spec->width = va_arg(arg, int);
    if (spec->width < 0) {
      spec->flag[i++] = '-';
      spec->width *= -1;
      spec->flag[i] = 0;
    }
    format++;
  }
  if (*format == '.') {
    format++;
    if (is_digit(*format)) {
      spec->precision = str_to_int(format, 0);
      while (is_digit(*format)) format++;
    } else if (*format == '*') {
      spec->precision = va_arg(arg, int);
      format++;
    } else
      spec->precision = 0;
  }
  if (s21_strchr(length, *format)) spec->length = *(format++);
  if (find_specifier(*format)) spec->specifier = *(format++);
  return format - form;
}

char *type_to_string(struct specification *spec, va_list arg) {
  int mem = 100;
  if (spec->width > mem || spec->precision > mem) {
    if (spec->width > spec->precision)
      mem += spec->width;
    else
      mem += spec->precision;
  }
  char *buf = (char *)calloc(mem, sizeof(char));
  char *str = buf;
  switch (spec->specifier) {
    case 'c':
      *str++ = va_arg(arg, int);
      *str = 0;
      break;
    case 'd':
      num_to_string(get_int_arg(spec, arg), str, 10, 0);
      break;
    case 'u':
      long long int unum;
      if (spec->length == 'l')
        unum = (long long int)va_arg(arg, long unsigned int);
      else if (spec->length == 'h')
        unum = (long long int)((short unsigned int)va_arg(arg, unsigned int));
      else
        unum = (long long int)va_arg(arg, unsigned int);
      num_to_string(unum, str, 10, 0);
      break;
    case 'p':
    case 'x':
    case 'X':
      if (spec->specifier == 'p') spec->length = 'l';
      long long int xnum = get_int_arg(spec, arg);
      if (spec->specifier == 'X')
        num_to_string(xnum, str, 16, 1);
      else
        num_to_string(xnum, str, 16, 0);
      break;
    case 'o':
      num_to_string(get_int_arg(spec, arg), str, 8, 0);
      break;
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f':
      float_represent(str, spec, arg);
      break;
    case 's':
      char *arg_str = va_arg(arg, char *);
      if (s21_strlen(arg_str) >= (s21_size_t)mem) {
        free(buf);
        buf = (char *)calloc(s21_strlen(arg_str) + 1, sizeof(char));
        str = buf;
      }
      s21_strncpy(str, arg_str, s21_strlen(arg_str));
      break;
    case '%':
      s21_strncpy(str, "%%", 1);
      break;
  }
  str = buf;
  string_format(str, spec);
  return buf;
}

void float_represent(char *str, struct specification *spec, va_list arg) {
  long double fnum;
  int point = (s21_strchr(spec->flag, '#')) ? 1 : 0;
  if (spec->length == 'L')
    fnum = va_arg(arg, long double);
  else
    fnum = (long double)va_arg(arg, double);
  if (spec->specifier == 'e' || spec->specifier == 'E') {
    num_to_e_notation(fnum, str, spec->specifier, spec->precision, point);
  } else if (spec->specifier == 'g' || spec->specifier == 'G') {
    g_num_conversion(fnum, str, spec->specifier, spec->precision, point);
  } else
    float_to_string(fnum, str, spec->precision, point);
}

long long int get_int_arg(struct specification *spec, va_list arg) {
  long long int num;
  if (spec->length == 'l')
    num = (long long int)va_arg(arg, long int);
  else if (spec->length == 'h')
    num = (long long int)((short int)va_arg(arg, int));
  else
    num = (long long int)va_arg(arg, int);
  return num;
}

void num_to_string(long long int num, char *str, int base, int is_cap) {
  char small[] = "0123456789abcdef";
  char capital[] = "0123456789ABCDEF";
  if (num < 0) *str++ = '-';
  num = (num < 0) ? (0 - num) : num;
  char s[50];
  int i = 0;
  do {
    if (is_cap)
      s[i++] = capital[num % base];
    else
      s[i++] = small[num % base];
    num /= base;
  } while (num);
  for (i -= 1; i >= 0; i--) *str++ = s[i];
  *str++ = 0;
}

void float_to_string(long double num, char *str, int precision, int point) {
  if (num < 0) *str++ = '-';
  num = (num < 0) ? (0 - num) : num;
  if (precision == -1) precision = 6;
  num = round_num(num, precision);
  char s[50 + precision];
  num_to_string((long long int)num, s, 10, 0);
  for (int i = 0; s[i]; i++) *str++ = s[i];
  if (precision) {
    *str++ = '.';
    num = (long double)num - (long long int)num;
    long double del = 10.0;
    for (int i = 0; i < precision; i++) del *= 10;
    long double close_to_zero;
    for (int u = 0; u < precision; u++) {
      close_to_zero = (1.0 / (del * 10)) * 1.5;
      if ((long double)num - (long long int)num > 1.0 - close_to_zero ||
          (long double)num - (long long int)num < close_to_zero)
        *str++ = '0';
      else {
        num *= 10;
        *str++ = ((long long int)(num + close_to_zero) % 10) + '0';
        del /= 10;
      }
    }
  } else if (point)
    *str++ = '.';
  *str++ = 0;
}

void num_to_e_notation(long double num, char *str, char e, int precision,
                       int point) {
  int power = 0;
  if (num != 0) {
    while ((long long int)num == 0 || (long long int)num > 9 ||
           (long long int)num < -9) {
      if ((long long int)num == 0) {
        num *= (long double)10.0;
        power--;
      } else if ((long long int)num > 9 || (long long int)num < -9) {
        num /= (long double)10.0;
        power++;
      }
    }
  }
  float_to_string(num, str, precision, point);

  if (((*str == '1' && str[1] == '0') ||
       ((*str == '-' || *str == '+') && str[1] == '1' && str[2] == '0'))) {
    power++;
    if (s21_strchr(str, '.')) {
      str[1] = '.';
      for (int i = 2; i <= precision + 1; i++) {
        str[i] = '0';
      }
      str[precision + 2] = 0;
    } else
      str[1] = 0;
  }
  if (e == 'g' || e == 'G') {
    if (s21_strchr(str, '.') && !point) {
      str += s21_strlen(str) - 1;
      char zero = *str--;
      while (zero == '0') zero = *str--;
      if (*(str + 1) == '.')
        str += 1;
      else
        str += 2;
    } else
      str += s21_strlen(str);
    if (e == 'g')
      e = 'e';
    else
      e = 'E';
  } else
    str += s21_strlen(str);
  *str++ = e;
  if (power < 0) {
    *str++ = '-';
    power = 0 - power;
  } else
    *str++ = '+';
  s21_sprintf(str, "%02d", power);
}

void g_num_conversion(long double num, char *str, char g, int precision,
                      int point) {
  int P = precision;
  if (!precision)
    P = 1;
  else if (precision == -1)
    P = 6;
  num_to_e_notation(num, str, g, precision, point);

  int X = str_to_int(str + s21_strlen(str) - 2, 1);
  if ((long long int)num == 0) X *= -1;
  if (P > X && X >= -4) {
    P = P - X - 1;
    float_to_string(num, str, P, point);
    if (s21_strchr(str, '.') && !point) {
      str += s21_strlen(str) - 1;
      char zero = *str--;
      while (zero == '0') zero = *str--;
      if (*(str + 1) == '.')
        *(str + 1) = 0;
      else
        *(str + 2) = 0;
    } else {
      str += s21_strlen(str);
      *str++ = 0;
    }
  } else {
    P--;
    num_to_e_notation(num, str, g, P, point);
  }
}

void string_format(char *str, struct specification *spec) {
  char before[3] = {0, 0, 0};
  if (find_specifier(spec->specifier) == 2 || spec->specifier == 'd') {
    if (s21_strchr(spec->flag, '+')) {
      if (*str != '-' && *str) before[0] = '+';
    } else if (s21_strchr(spec->flag, ' ')) {
      if (*str != '-' && *str != '+' && *str) before[0] = ' ';
    }
  }
  if (s21_strchr(spec->flag, '#') || spec->specifier == 'p') {
    if (spec->specifier == 'o') before[0] = '0';
    if (!eq_zero(str)) {
      if (spec->specifier == 'x' || spec->specifier == 'p') {
        before[0] = 'x';
        before[1] = '0';
      } else if (spec->specifier == 'X') {
        before[0] = 'X';
        before[1] = '0';
      }
    }
  }
  int flag_0 = 0;
  int left = 0;
  int empty = 0;
  if (s21_strchr(spec->flag, '-')) left = 1;
  int have_precision = 0;
  if (spec->precision != -1) {
    if (find_specifier(spec->specifier) == 2) {
      spec->precision = -1;
    } else if (find_specifier(spec->specifier) == 1) {
      if (!spec->precision && eq_zero(str))
        empty = 1;
      else
        have_precision = 1;
    } else if (spec->specifier == 's') {
      if (s21_strlen(str) > (size_t)spec->precision) str[spec->precision] = 0;
    }
  }
  if ((have_precision && spec->precision) ||
      (s21_strchr(spec->flag, '0') && (int)s21_strlen(str) < spec->width &&
       !left && spec->precision == -1 && !empty && spec->specifier != 's')) {
    flag_0 = 1;
    if ((find_specifier(spec->specifier) == 2 || spec->specifier == 'd') &&
        *str == '-') {
      before[0] = '-';
      *str = '0';
    }
    int first_chars = s21_strlen(before);
    int wid_or_prec = (size_t)spec->width - first_chars;
    if (have_precision) {
      if (before[0] == '0')
        wid_or_prec = (size_t)spec->precision - first_chars;
      else
        wid_or_prec = (size_t)spec->precision;
    }
    while ((int)s21_strlen(str) < wid_or_prec) add_leading_char(str, '0');
    if (first_chars) {
      add_leading_char(str, before[0]);
      if (first_chars == 2) add_leading_char(str, before[1]);
    }
  }
  if (empty) *str = 0;
  if (!flag_0) {
    if (s21_strlen(before)) {
      if ((empty && spec->specifier == 'o') || !empty) {
        add_leading_char(str, before[0]);
        if (s21_strlen(before) == 2) add_leading_char(str, before[1]);
      }
    }
  }
  char space = ' ';
  if (spec->specifier == 's' && s21_strchr(spec->flag, '0')) space = '0';
  while ((int)s21_strlen(str) < spec->width)
    if (left)
      s21_strncat(str, " ", 1);
    else
      add_leading_char(str, space);
}

void add_leading_char(char *str, char ch) {
  size_t len = s21_strlen(str);
  if (!len)
    *str++ = ch;
  else
    for (int i = s21_strlen(str) - 1; i >= 0; i--) {
      str[i + 1] = str[i];
      if (i == 0) str[i] = ch;
    }
  str[len + 1] = 0;
}

int find_specifier(char ch) {
  char int_spec[7] = "duxXo";
  char float_spec[6] = "fgGeE";
  int res = 0;
  if (s21_strchr(int_spec, ch))
    res = 1;
  else if (s21_strchr(float_spec, ch))
    res = 2;
  else if (ch == 'p')
    res = 3;
  else
    res = 4;
  return res;
}

int is_digit(char ch) { return (ch >= '0' && ch <= '9') ? 1 : 0; }

int str_to_int(const char *str, int negative) {
  int res = 0;
  int num = 0;
  int dec = 10;
  const char *s = str;
  if (negative && *s == '-') {
    negative = 3;
    s++;
  }
  while (is_digit(*s++)) num++;
  for (int i = num - 1; i >= 0; i--) {
    if (i == num - 1)
      res += str[i] - '0';
    else {
      res += (str[i] - '0') * dec;
      dec *= 10;
    }
  }
  if (negative == 3) res = 0 - res;
  return res;
}

int eq_zero(char *str) {
  int not_zero = 0;
  while (*str) {
    if (!(*str == '0') && !(*str == '.')) not_zero = 1;
    str++;
  }
  return (not_zero) ? 0 : 1;
}

long double round_num(long double num, int precision) {
  for (int i = 0; i < precision; i++) num *= (long double)10.0;
  if ((long long int)(num * 10) % 10 == 5 &&
      ((long long int)(num * 100) % 10 == 0))
    num += 0.5;
  num = roundl(num);
  for (int i = 0; i < precision; i++) num /= (long double)10.0;
  return num;
}
