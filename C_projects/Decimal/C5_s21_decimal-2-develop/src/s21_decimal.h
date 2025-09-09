#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
typedef enum { SUCCESS,
               CONVERTING_ERROR } e_cast_code_t;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[6];
} s21_big_decimal;

enum { LOW,
       MID,
       HIGH,
       SCALE };
enum { s21_NORMAL_VALUE,
       s21_INFINITY,
       s21_NEGATIVE_INFINITY,
       s21_NAN };

void clean_decimal(s21_decimal *dec);
void copy_decimal(s21_decimal *dest, s21_decimal *src);
// bits
int get_bit(s21_decimal dec, int index);
int set_bit(s21_decimal *dec, int index);
int set_bit_to_int(int number, int index);
// sign
int get_scale(s21_decimal *dec);
void set_scale(s21_decimal *dec, int scale);
int get_sign(int val);
void set_sign(unsigned int *val);
void set_minus_sign(unsigned int *val);
int get_exp_float(float src);
s21_decimal negtive(s21_decimal dec);
// scale
void equal_scale(s21_decimal *dec1, s21_decimal *dec2);
void upper_scale(s21_decimal *dec);
void lower_scale(s21_decimal *dec);
//  конвертер
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void shift_left(s21_decimal *dec);
void shift_righ(s21_decimal *dec);
int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int check_decimal_on_null(s21_decimal *dec);
// сравнение
int s21_is_less(s21_decimal val_1, s21_decimal val_2);
int s21_is_greater(s21_decimal val_1, s21_decimal val_2);
int s21_is_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2);
int s21_is_greater_by_abc(s21_decimal val_1, s21_decimal val_2);
//  сложение и вычитание
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//  деление
s21_decimal div_no_scale(s21_decimal dividend, s21_decimal divisor);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//   округление
int check_zero(s21_decimal val);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
// big_decimal
void clean_big_decimal(s21_big_decimal *big);
void decimal_to_big_decimal(s21_big_decimal *dst, s21_decimal *src);
void big_to_decimal(s21_decimal *dst, s21_big_decimal *src);
int get_bit_big(s21_big_decimal big, int index);
void set_bit_big(s21_big_decimal *big, int index);
s21_big_decimal sum_big_decimal(s21_big_decimal big1, s21_big_decimal big2);
void shift_left_big(s21_big_decimal *big);
void shift_righ_big(s21_big_decimal *big);
s21_big_decimal div_big_on_ten(s21_big_decimal big1);
void copy_big(s21_big_decimal *big_dst, s21_big_decimal *big_src);
int is_greater_or_equal_big(s21_big_decimal big1, s21_big_decimal big2);
void big_dop_code(s21_big_decimal *big);
//  mod
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif  //  SRC_S21_DECIMAL_H_
