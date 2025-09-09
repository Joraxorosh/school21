#include "s21_sprintf_test.h"
START_TEST(sprintf_noflag_width_5_no_precision_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%5d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_precision_3_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%5.3d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_flag_width_5_no_precision_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%+5d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%-5d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%05d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_space_flag_width_5_no_precision_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|% 5d|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_s) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *x = "hello";
  char *format = "|%5s|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_precision_3_s) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *x = "hello";
  char *format = "|%5.3s|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_s) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *x = "hello";
  char *format = "|%-5s|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_s) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *x = "hello";
  char *format = "|%05s|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_10_precision_3_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double x = 123.456;
  char *format = "|%10.3f|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_flag_width_10_precision_3_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double x = 123.456;
  char *format = "|%+10.3f|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_10_precision_3_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double x = 123.456;
  char *format = "|%-10.3f|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_10_precision_3_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double x = 123.456;
  char *format = "|%010.3f|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_x) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%5x|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_precision_3_x) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%5.3x|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_flag_width_5_no_precision_x) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%+5x|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_x) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%-5x|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_x) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%05x|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_X) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%5X|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_precision_3_X) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%5.3X|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_flag_width_5_no_precision_X) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%+5X|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_X) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%-5X|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_X) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int x = 123;
  char *format = "|%05X|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_c) {
  char str1[1024] = "";
  char str2[1024] = "";
  char x = 'A';
  char *format = "|%5c|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_c) {
  char str1[1024] = "";
  char str2[1024] = "";
  char x = 'A';
  char *format = "|%-5c|\n";
  int res1 = s21_sprintf(str1, format, x);
  int res2 = sprintf(str2, format, x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST
extern int clown;
START_TEST(sprintf_noflag_width_10_precision_3_p) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%10.3p|\n";
  int res1 = s21_sprintf(str1, format, &x);
  int res2 = sprintf(str2, format, &x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_10_precision_3_p) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%-10.3p|\n";
  int res1 = s21_sprintf(str1, format, &x);
  int res2 = sprintf(str2, format, &x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_10_precision_3_p) {
  char str1[1024] = "";
  char str2[1024] = "";
  int x = 123;
  char *format = "|%010.3p|\n";
  int res1 = s21_sprintf(str1, format, &x);
  int res2 = sprintf(str2, format, &x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_u) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int u = 123;
  char *format = "|%5u|\n";
  int res1 = s21_sprintf(str1, format, u);
  int res2 = sprintf(str2, format, u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_u) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int u = 123;
  char *format = "|%-5u|\n";
  int res1 = s21_sprintf(str1, format, u);
  int res2 = sprintf(str2, format, u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_u) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int u = 123;
  char *format = "|%05u|\n";
  int res1 = s21_sprintf(str1, format, u);
  int res2 = sprintf(str2, format, u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_5_no_precision_o) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int o = 123;
  char *format = "|%5o|\n";
  int res1 = s21_sprintf(str1, format, o);
  int res2 = sprintf(str2, format, o);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_5_no_precision_o) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int o = 123;
  char *format = "|%-5o|\n";
  int res1 = s21_sprintf(str1, format, o);
  int res2 = sprintf(str2, format, o);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_5_no_precision_o) {
  char str1[1024] = "";
  char str2[1024] = "";
  unsigned int o = 123;
  char *format = "|%05o|\n";
  int res1 = s21_sprintf(str1, format, o);
  int res2 = sprintf(str2, format, o);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_10_precision_2_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double f = 123.456;
  char *format = "|%10.2f|\n";
  int res1 = s21_sprintf(str1, format, f);
  int res2 = sprintf(str2, format, f);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_10_precision_2_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double f = 123.456;
  char *format = "|%-10.2f|\n";
  int res1 = s21_sprintf(str1, format, f);
  int res2 = sprintf(str2, format, f);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_10_precision_2_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  double f = 123.456;
  char *format = "|%010.2f|\n";
  int res1 = s21_sprintf(str1, format, f);
  int res2 = sprintf(str2, format, f);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_10_precision_2_e) {
  char str1[1024] = "";
  char str2[1024] = "";
  double e = 123.456;
  char *format = "|%10.2e|\n";
  int res1 = s21_sprintf(str1, format, e);
  int res2 = sprintf(str2, format, e);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_10_precision_2_e) {
  char str1[1024] = "";
  char str2[1024] = "";
  double e = 123.456;
  char *format = "|%-10.2e|\n";
  int res1 = s21_sprintf(str1, format, e);
  int res2 = sprintf(str2, format, e);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_10_precision_2_e) {
  char str1[1024] = "";
  char str2[1024] = "";
  double e = 123.456;
  char *format = "|%010.2e|\n";
  int res1 = s21_sprintf(str1, format, e);
  int res2 = sprintf(str2, format, e);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_noflag_width_10_precision_2_g) {
  char str1[1024] = "";
  char str2[1024] = "";
  double g = 123.456;
  char *format = "|%10.2g|\n";
  int res1 = s21_sprintf(str1, format, g);
  int res2 = sprintf(str2, format, g);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_flag_width_10_precision_2_g) {
  char str1[1024] = "";
  char str2[1024] = "";
  double g = 123.456;
  char *format = "|%-10.2g|\n";
  int res1 = s21_sprintf(str1, format, g);
  int res2 = sprintf(str2, format, g);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_flag_width_10_precision_2_g) {
  char str1[1024] = "";
  char str2[1024] = "";
  double g = 123.456;
  char *format = "|%010.2g|\n";
  int res1 = s21_sprintf(str1, format, g);
  int res2 = sprintf(str2, format, g);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_s_flag) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *g = "Hello World";
  char *format = "|%s|\n";
  int res1 = s21_sprintf(str1, format, g);
  int res2 = sprintf(str2, format, g);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_width) {
  char str1[1024] = "";
  char str2[1024] = "";
  int width = 10;
  int num = 123;

  int res1 = s21_sprintf(str1, "|%*d|", width, num);
  int res2 = sprintf(str2, "|%*d|", width, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_precision) {
  char str1[1024] = "";
  char str2[1024] = "";
  int precision = 5;
  double num = 123.456;

  int res1 = s21_sprintf(str1, "|%.*f|", precision, num);
  int res2 = sprintf(str2, "|%.*f|", precision, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_width_and_precision) {
  char str1[1024] = "";
  char str2[1024] = "";
  int width = 10;
  int precision = 3;
  double num = 123.456;

  int res1 = s21_sprintf(str1, "|%*.*f|", width, precision, num);
  int res2 = sprintf(str2, "|%*.*f|", width, precision, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_negative_width) {
  char str1[1024] = "";
  char str2[1024] = "";
  int width = -10;
  int num = 123;

  int res1 = s21_sprintf(str1, "|%*d|", width, num);
  int res2 = sprintf(str2, "|%*d|", width, num);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *sprintf_suite() {
  Suite *s1 = suite_create("sprintf");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_d);
  tcase_add_test(tc_core, sprintf_noflag_width_5_precision_3_d);
  tcase_add_test(tc_core, sprintf_plus_flag_width_5_no_precision_d);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_d);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_d);
  tcase_add_test(tc_core, sprintf_space_flag_width_5_no_precision_d);

  tcase_add_test(tc_core, sprintf_noflag_width_5_precision_3_s);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_s);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_s);
  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_s);
  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_d);

  tcase_add_test(tc_core, sprintf_noflag_width_10_precision_3_f);
  tcase_add_test(tc_core, sprintf_plus_flag_width_10_precision_3_f);
  tcase_add_test(tc_core, sprintf_minus_flag_width_10_precision_3_f);
  tcase_add_test(tc_core, sprintf_zero_flag_width_10_precision_3_f);

  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_x);
  tcase_add_test(tc_core, sprintf_noflag_width_5_precision_3_x);
  tcase_add_test(tc_core, sprintf_plus_flag_width_5_no_precision_x);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_x);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_x);
  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_X);
  tcase_add_test(tc_core, sprintf_noflag_width_5_precision_3_X);
  tcase_add_test(tc_core, sprintf_plus_flag_width_5_no_precision_X);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_X);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_X);
  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_c);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_c);
  tcase_add_test(tc_core, sprintf_noflag_width_10_precision_3_p);
  tcase_add_test(tc_core, sprintf_minus_flag_width_10_precision_3_p);
  tcase_add_test(tc_core, sprintf_zero_flag_width_10_precision_3_p);

  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_u);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_u);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_u);
  tcase_add_test(tc_core, sprintf_noflag_width_5_no_precision_o);
  tcase_add_test(tc_core, sprintf_minus_flag_width_5_no_precision_o);
  tcase_add_test(tc_core, sprintf_zero_flag_width_5_no_precision_o);
  tcase_add_test(tc_core, sprintf_noflag_width_10_precision_2_f);
  tcase_add_test(tc_core, sprintf_minus_flag_width_10_precision_2_f);
  tcase_add_test(tc_core, sprintf_zero_flag_width_10_precision_2_f);
  tcase_add_test(tc_core, sprintf_noflag_width_10_precision_2_e);
  tcase_add_test(tc_core, sprintf_minus_flag_width_10_precision_2_e);
  tcase_add_test(tc_core, sprintf_zero_flag_width_10_precision_2_e);
  tcase_add_test(tc_core, sprintf_noflag_width_10_precision_2_g);
  tcase_add_test(tc_core, sprintf_minus_flag_width_10_precision_2_g);
  tcase_add_test(tc_core, sprintf_zero_flag_width_10_precision_2_g);
  tcase_add_test(tc_core, sprintf_s_flag);

  tcase_add_test(tc_core, sprintf_star_width);
  tcase_add_test(tc_core, sprintf_star_precision);
  tcase_add_test(tc_core, sprintf_star_width_and_precision);
  tcase_add_test(tc_core, sprintf_star_negative_width);
  suite_add_tcase(s1, tc_core);
  return s1;
}
