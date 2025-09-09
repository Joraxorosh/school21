#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

struct specification {
  char flag[6];
  int width;
  int precision;
  char length;
  char specifier;
};

int s21_sprintf(char *str, const char *format, ...);
int write_specification(struct specification *spec, const char *format,
                        va_list arg);
char *type_to_string(struct specification *spec, va_list arg);
void float_represent(char *str, struct specification *spec, va_list arg);
void g_num_conversion(long double num, char *str, char g, int precision,
                      int point);
void string_format(char *str, struct specification *spec);
void num_to_string(long long int num, char *str, int base, int is_cap);
void float_to_string(long double num, char *str, int precision, int point);
long long int get_int_arg(struct specification *spec, va_list arg);
int is_digit(char ch);
void add_leading_char(char *str, char ch);
int find_specifier(char ch);
int str_to_int(const char *str, int negative);
void num_to_e_notation(long double num, char *str, char e, int precision,
                       int point);
long double round_num(long double num, int precision);
void print(struct specification *spec);
int eq_zero(char *str);

#endif
