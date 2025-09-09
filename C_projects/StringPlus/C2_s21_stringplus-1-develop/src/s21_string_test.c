#include "s21_string.h"

#include "s21_sprintf.h"
#include "s21_string_test.h"

START_TEST(s21_sprintf_unsigned_integers_test) {
  char format[100];
  char buffer[100];
  char buffer_cpy[100];
  char len = '\0';
  int flag, wid, prec, spec;
  unsigned int uint[10] = {5200000, 60,    10, 20,       40,
                           52,      10000, 15, RAND_MAX, 12};
  const char flags[5] = "-0# +";
  const char int_spec[4] = "uxXo";
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        for (int n = 1; n < 12; n++) {
          for (int l = 1; l < 12; l++) {
            flag = flags[j];
            wid = n;
            prec = l;
            spec = int_spec[k];
            len = '\0';
            if (uint[i] < 1000)
              len = 'h';
            else if (uint[i] > 200000000)
              len = 'l';
            if (len)
              sprintf(format, "%%%c%d.%d%c%c", flag, wid, prec, len, spec);
            else
              sprintf(format, "%%%c%d.%d%c", flag, wid, prec, spec);
            sprintf(buffer, format, uint[i]);
            s21_sprintf(buffer_cpy, format, uint[i]);
            ck_assert_str_eq(buffer, buffer_cpy);
          }
        }
      }
    }
  }
}
END_TEST

START_TEST(s21_sprintf_float_int_integers_test) {
  char format[100];
  char buffer[100];
  char buffer_cpy[100];
  long double doubl[10] = {0.9999,  1.56, 25.6, 0.15678, 100.1543,
                           0.00009, 8.93, 5.2,  22.8,    0.512323};
  int flag, wid, prec, spec;
  const char flags[5] = "-0# +";
  const char float_spec[6] = "feEdgG";
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 13; l++) {
          for (int n = 0; n < 10; n++) {
            spec = float_spec[j];
            flag = flags[k];
            wid = l;
            prec = n;
            if (((flag == ' ') && (wid == 0) && (prec == 0)) ||
                ((flag == '+') && (prec == 0)))
              continue;
            sprintf(format, "%%%c%d.%d%c", flag, wid, prec, spec);
            if (spec == 'd') {
              sprintf(buffer, format, (int)doubl[i]);
              s21_sprintf(buffer_cpy, format, (int)doubl[i]);
            } else {
              sprintf(buffer, format, (double)doubl[i]);
              s21_sprintf(buffer_cpy, format, (double)doubl[i]);
            }
            ck_assert_str_eq(buffer, buffer_cpy);
          }
        }
      }
    }
  }
  sprintf(buffer, "%f, next: %f", 3.123242, -3.231141);
  s21_sprintf(buffer_cpy, "%f, next: %f", 3.123242, -3.231141);
  ck_assert_str_eq(buffer, buffer_cpy);
}
END_TEST

START_TEST(s21_sprintf_string_char_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  char buffer[100];
  char buffer_cpy[100];
  char format[100];
  int wid, prec, spec;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 1; k < 10; k++) {
        wid = j;
        prec = k;
        if (j % 2 == 0)
          spec = 's';
        else
          spec = 'c';
        sprintf(format, "%%%d.%d%c", wid, prec, spec);
        if (spec == 'c') {
          sprintf(buffer, format, tests[i][0]);
          s21_sprintf(buffer_cpy, format, tests[i][0]);
        } else {
          sprintf(buffer, format, tests[i]);
          s21_sprintf(buffer_cpy, format, tests[i]);
        }
        ck_assert_str_eq(buffer, buffer_cpy);
      }
    }
  }
}
END_TEST

START_TEST(s21_sprintf_pointer_test) {
  char format[100];
  char buffer[100];
  char buffer_cpy[100];
  char *s;
  int wid;
  for (int j = 0; j < 50; j++) {
    s = malloc(rand() % 500 + 1);
    wid = rand() % 30;
    if (j % 5 == 0)
      sprintf(format, "%%-%dp", wid);
    else
      sprintf(format, "%%%dp", wid);
    sprintf(buffer, format, s);
    s21_sprintf(buffer_cpy, format, s);
    ck_assert_str_eq(buffer, buffer_cpy);
    free(s);
  }
}
END_TEST

START_TEST(s21_strchr_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(strchr(tests[i], 'H'), s21_strchr(tests[i], 'H'));
  }
}
END_TEST

START_TEST(s21_strrchr_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(strrchr(tests[i], 'H'), s21_strrchr(tests[i], 'H'));
  }
}
END_TEST

START_TEST(s21_strlen_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(strlen(tests[i]), s21_strlen(tests[i]));
  }
}
END_TEST

START_TEST(s21_strtok_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    char tmp1[100];
    char tmp2[100];
    char *str1;
    char *str2;
    strcpy(tmp1, tests[i]);
    strcpy(tmp2, tests[i]);
    while ((str1 = s21_strtok(tmp1, "o")) && (str2 = strtok(tmp2, "o"))) {
      ck_assert_str_eq(str1, str2);
    }
  }
}
END_TEST

START_TEST(s21_strpbrk_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(s21_strpbrk(tests[i], "lo"), strpbrk(tests[i], "lo"));
  }
}
END_TEST

START_TEST(s21_strcspn_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(s21_strcspn(tests[i], "lo"), strcspn(tests[i], "lo"));
  }
}
END_TEST

START_TEST(s21_strncmp_tests) {
  char *t_set1[48] = {"Hello world", "Hello world\n", "HELLO",       "WoRlD",
                      "\n",          "Hello\0World",  "hello world", "Q!W~E"};
  char *t_set2[48] = {"Hello world", "Hello world", "HELLO ",      "WoRlD",
                      "\n\n",        "Hello World", "hello world", "Q!W~E"};
  for (int i = 0; i < 7; i++) {
    for (int k = 0; k < 10; k++) {
      ck_assert_int_eq(strncmp(t_set1[i], t_set2[i], k) < 0,
                       s21_strncmp(t_set1[i], t_set2[i], k) < 0);
    }
  }
}
END_TEST

START_TEST(s21_strncpy_tests) {
  char *test_dest1 = (char *)calloc(128, sizeof(char));
  char *test_dest2 = (char *)calloc(128, sizeof(char));
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 12; i++) {
    test_dest1 = strncpy(test_dest1, tests[1], i);
    test_dest2 = s21_strncpy(test_dest2, tests[1], i);
    ck_assert_str_eq(test_dest1, test_dest2);
  }
  free(test_dest1);
  free(test_dest2);
}
END_TEST

START_TEST(test_s21_memchr) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(memchr(tests[i], 'o', strlen(tests[i])),
                     s21_memchr(tests[i], 'o', s21_strlen(tests[i])));
    ck_assert_ptr_eq(memchr(tests[i], 'z', strlen(tests[i])),
                     s21_memchr(tests[i], 'z', s21_strlen(tests[i])));
    ck_assert_ptr_eq(memchr(tests[i], 'H', strlen(tests[i])),
                     s21_memchr(tests[i], 'H', s21_strlen(tests[i])));
  }
}
END_TEST

START_TEST(test_s21_memcmp) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      const char *str1 = tests[i];
      const char *str2 = tests[j];
      s21_size_t len = s21_strlen(str1);
      s21_size_t len1 = s21_strlen(str2);
      len = len < len1 ? len : len1;
      ck_assert_int_eq(memcmp(str1, str2, len) > 0,
                       s21_memcmp(str1, str2, len) > 0);
    }
  }
}
END_TEST

START_TEST(test_s21_memcpy) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  char dest1[100] = {0};
  char dest2[100] = {0};
  for (int i = 0; i < 7; i++) {
    const char *src = tests[i];
    s21_size_t len = s21_strlen(src);
    ck_assert_str_eq(memcpy(dest1, src, len), s21_memcpy(dest2, src, len));
  }
}
END_TEST

START_TEST(test_s21_memset) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  char dest1[100] = {0};
  char dest2[100] = {0};
  for (int i = 0; i < 7; i++) {
    s21_size_t len = s21_strlen(tests[i]);
    dest1[len] = '\0';
    dest2[len] = '\0';
    ck_assert_mem_eq(memset(dest1, 'a', len), s21_memset(dest2, 'a', len), len);
    ck_assert_str_eq(memset(dest1, 'a', len), s21_memset(dest2, 'a', len));
  }
}
END_TEST

START_TEST(test_s21_strncat) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  char dest1[100] = {0};
  char dest2[100] = {0};
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      const char *src = tests[j];
      strcpy(dest1, tests[i]);
      strcpy(dest2, tests[i]);
      s21_size_t len = s21_strlen(src);
      ck_assert_str_eq(strncat(dest1, src, len + 10),
                       s21_strncat(dest2, src, len + 10));
    }
  }
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = 0; i < 100; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(test_s21_strstr) {
  char dest1[100] = {0};
  char dest2[100] = {0};
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      const char *src = tests[i];
      strcpy(dest1, tests[i]);
      strcpy(dest2, tests[i]);
      ck_assert_str_eq(strstr(dest1, src), s21_strstr(dest2, src));

      int index = strlen(src) / 2;
      strcpy(dest1, tests[i]);
      strcpy(dest2, tests[i]);
      char mid_char[2] = {0};
      sprintf(mid_char, "%c", src[index]);
      ck_assert_str_eq(strstr(dest1, mid_char), s21_strstr(dest2, mid_char));

      index = strlen(src) - 2;
      strcpy(dest1, tests[i]);
      strcpy(dest2, tests[i]);
      char end_char[2] = {0};
      sprintf(end_char, "%c", src[index]);
      if (strstr(dest1, end_char))
        ck_assert_str_eq(strstr(dest1, end_char), s21_strstr(dest2, end_char));
      else
        ck_assert_ptr_eq(strstr(dest1, end_char), s21_strstr(dest2, end_char));
      if (strlen(src) > 1) {
        strcpy(dest1, tests[i]);
        strcpy(dest2, tests[i]);
        char end_char[2] = {0};
        sprintf(end_char, "%c", src[1]);
        ck_assert_str_eq(strstr(dest1, end_char), s21_strstr(dest2, end_char));
      }
    }
  }
}
END_TEST

START_TEST(s21_sprintf_int_test) {
  for (int j = 0; j < 100; j++) {
    char buffer[100];
    char buffer_cpy[100];
    int i = rand() - RAND_MAX / 2;
    sprintf(buffer, "%d", i);
    s21_sprintf(buffer_cpy, "%d", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_double_test) {
  for (int j = 0; j < 100; j++) {
    char buffer[100];
    char buffer_cpy[100];
    double i = (-RAND_MAX + round(2 * rand())) * pow(10, 6) / pow(10, 6);
    sprintf(buffer, "%f", i);
    s21_sprintf(buffer_cpy, "%f", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_PERCENT_test) {
  char buffer[32];
  char buffer_cpy[32];
  sprintf(buffer, "%%");
  s21_sprintf(buffer_cpy, "%%");
  ck_assert_str_eq(buffer, buffer_cpy);
}
END_TEST

START_TEST(s21_sprintf_char_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (char i = -127; i < 127; i++) {
    sprintf(buffer, "%c", i);
    s21_sprintf(buffer_cpy, "%c", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_string_test) {
  const char *tests[7] = {
      "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n", "\0"};
  for (int i = 0; i < 7; i++) {
    char buffer[1000];
    char buffer_cpy[1000];
    sprintf(buffer, "%s", tests[i]);
    s21_sprintf(buffer_cpy, "%s", tests[i]);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_unsigned_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    unsigned int i = j + rand();
    sprintf(buffer, "%u", i);
    s21_sprintf(buffer_cpy, "%u", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_space_flag_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    int i = rand() - RAND_MAX / 2;
    sprintf(buffer, "% d", i);
    s21_sprintf(buffer_cpy, "% d", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_minus_flag_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    int i = rand() - RAND_MAX / 2;
    sprintf(buffer, "%-15d", i);
    s21_sprintf(buffer_cpy, "%-15d", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_plus_flag_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    int i = rand() - RAND_MAX / 2;
    sprintf(buffer, "%+d", i);
    s21_sprintf(buffer_cpy, "%+d", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_width_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    int i = rand() % 1000000 / pow(10, rand() % 3);
    sprintf(buffer, "%10d", i);
    s21_sprintf(buffer_cpy, "%10d", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_precision_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    double i = (rand() % 100000000) / pow(10, rand() % 8) * pow(10, rand() % 3);
    sprintf(buffer, "%.5f", i);
    s21_sprintf(buffer_cpy, "%.5f", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_h_flag_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    short int i = rand() % 10000;
    sprintf(buffer, "%hd", i);
    s21_sprintf(buffer_cpy, "%hd", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(s21_sprintf_l_flag_test) {
  char buffer[100];
  char buffer_cpy[100];
  for (int j = 0; j < 100; j++) {
    long double i = rand() / pow(10, rand() % 8) * pow(10, rand() % 3);
    sprintf(buffer, "%Lf", i);
    s21_sprintf(buffer_cpy, "%Lf", i);

    ck_assert_str_eq(buffer, buffer_cpy);
  }
}
END_TEST

START_TEST(test_s21_sprintf_INTEGER_formats_Jeff) {
  char std_buffer[512] = {0};
  char custom_buffer[512] = {0};

  const char *formats[] = {"%*d", "%+*d", "%0*d", "%-*d", "%*c", "%*u"};

  int int_values[] = {5, 1, -1, 42, -42, 12345, -12345};

  for (size_t i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
    const char *format = formats[i];

    for (size_t j = 0; j < sizeof(int_values) / sizeof(int_values[0]); j++) {
      memset(std_buffer, 0, sizeof(std_buffer));
      memset(custom_buffer, 0, sizeof(custom_buffer));
      sprintf(std_buffer, format, 2, int_values[j]);
      s21_sprintf(custom_buffer, format, 2, int_values[j]);
      ck_assert_str_eq(std_buffer, custom_buffer);
    }
  }
}
END_TEST

START_TEST(test_s21_sprintf_FLOAT_formats_Jeff) {
  char std_buffer[512] = {0};
  char custom_buffer[512] = {0};

  const char *formats[] = {"%*f",  "%.*f", "%*.2f", "%*e",
                           "%.*E", "%*g",  "%.*G"};

  double double_values[] = {0, 1.1, -1.4, 42.24, -42.10, 12345.1, -12345.1};

  for (size_t i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
    const char *format = formats[i];

    for (size_t j = 0; j < sizeof(double_values) / sizeof(double_values[0]);
         j++) {
      memset(std_buffer, 0, sizeof(std_buffer));
      memset(custom_buffer, 0, sizeof(custom_buffer));
      sprintf(std_buffer, format, 2, double_values[j]);
      s21_sprintf(custom_buffer, format, 2, double_values[j]);
      ck_assert_str_eq(std_buffer, custom_buffer);
    }
  }
}
END_TEST

START_TEST(test_s21_sprintf_flags_x_o_p_prcnt) {
  char std_buffer[512] = {0};
  char custom_buffer[512] = {0};

  const char *formats[] = {
      "%x",   "%#x",  "%-x",    "%0x",  "%5x",   "%.x", "%.2x", "%5.2x",
      "%-5x", "%-#x", "%-5.2x", "%05x", "%-05x", "%#x", "%-#x", "%0#x",
      "%o",   "%#o",  "%-o",    "%0o",  "%5o",   "%.o", "%.2o", "%5.2o",
      "%-5o", "%-#o", "%-5.2o", "%05o", "%-05o", "%p",  "%-p",  "%5p"};

  unsigned int short_values[] = {2};

  for (size_t i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
    const char *format = formats[i];

    for (size_t j = 0; j < sizeof(short_values) / sizeof(short_values[0]);
         j++) {
      s21_memset(std_buffer, 0, sizeof(std_buffer));
      s21_memset(custom_buffer, 0, sizeof(custom_buffer));
      sprintf(std_buffer, format, short_values[j]);
      s21_sprintf(custom_buffer, format, short_values[j]);
      ck_assert_str_eq(std_buffer, custom_buffer);
    }
  }
}
END_TEST

START_TEST(test_s21_sprintf_flag_s) {
  char std_buffer[512] = {0};
  char custom_buffer[512] = {0};
  const char *formats[] = {"%s",   "%-s",  "%5s",   "%-5s",
                           "%.3s", "%.8s", "%8.3s", "%-8.3s"};

  const char *test_strings[] = {
      "", "A", "Test", "Hello world guys",
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod "
      "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
      "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
      "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "
      "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
      "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
      "mollit anim id est laborum. N more than 400 symbols"};

  for (size_t i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
    const char *format = formats[i];

    for (size_t j = 0; j < sizeof(test_strings) / sizeof(test_strings[0]);
         j++) {
      memset(std_buffer, 0, sizeof(std_buffer));
      memset(custom_buffer, 0, sizeof(custom_buffer));
      sprintf(std_buffer, format, test_strings[j]);
      s21_sprintf(custom_buffer, format, test_strings[j]);
      ck_assert_str_eq(std_buffer, custom_buffer);
    }
  }
  memset(std_buffer, 0, sizeof(std_buffer));
  memset(custom_buffer, 0, sizeof(custom_buffer));
  sprintf(std_buffer, "Hello");
  s21_sprintf(custom_buffer, "Hello");
  ck_assert_str_eq(std_buffer, custom_buffer);
}
END_TEST

START_TEST(test_s21_trim) {
  char trim_chars1[] = "ABC";
  char src1[] = "ABCDEsfgkajhfkjahkfhfhhef";
  char *res1 = s21_trim(src1, trim_chars1);
  ck_assert_str_eq(res1, "DEsfgkajhfkjahkfhfhhef");
  free(res1);

  char trim_chars2[] = "abc";
  char src2[] = "abc123abc";
  char *res2 = s21_trim(src2, trim_chars2);
  ck_assert_str_eq(res2, "123");
  free(res2);

  char trim_chars3[] = "abc";
  char src3[] = "a1bc123abc456a1bc";
  char *res3 = s21_trim(src3, trim_chars3);
  ck_assert_str_eq(res3, "1bc123abc456a1");
  free(res3);
}
END_TEST

START_TEST(test_s21_to_lower_classic) {
  char str[] = "HAPPY NEW YEAR";
  char expected[] = "happy new year";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, expected);
  free(res);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  char str[] = "";
  char expected[] = "";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, expected);
  free(res);
}
END_TEST

START_TEST(test_s21_to_lower_full_low) {
  char str[] = "happy new year";
  char expected[] = "happy new year";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, expected);
  free(res);
}
END_TEST

START_TEST(test_s21_to_upper_classic) {
  char str[] = "happy new year";
  char expected[] = "HAPPY NEW YEAR";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, expected);
  free(res);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  char str[] = "";
  char expected[] = "";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, expected);
  free(res);
}
END_TEST

START_TEST(s21_insert_first_test) {
  char *inserted;
  char *substr = "abc";
  char *str = "Mom";
  char *result = "Mabcom";
  inserted = s21_insert(str, substr, 1);
  ck_assert_str_eq(inserted, result);
  free(inserted);
}
END_TEST

START_TEST(s21_insert_second_test) {
  char *inserted;
  char *substr = "";
  char *str = "Mom";
  char *result = "Mom";
  inserted = s21_insert(str, substr, 2);
  ck_assert_str_eq(inserted, result);
  free(inserted);
}
END_TEST

START_TEST(s21_insert_third_test) {
  char *inserted;
  char *substr = "Mom";
  char *str = "";
  char *result = "Mom";
  inserted = s21_insert(str, substr, 0);
  ck_assert_str_eq(inserted, result);
  free(inserted);
}
END_TEST

Suite *s21_string_suite() {
  Suite *s;
  TCase *tc_core[45];
  s = suite_create("sprintf functions:");
  tc_core[0] = tcase_create("strchr");
  tcase_add_test(tc_core[0], s21_strchr_test);
  suite_add_tcase(s, tc_core[0]);
  tc_core[1] = tcase_create("strrchr");
  tcase_add_test(tc_core[1], s21_strrchr_test);
  suite_add_tcase(s, tc_core[1]);
  tc_core[2] = tcase_create("strlen");
  tcase_add_test(tc_core[2], s21_strlen_test);
  suite_add_tcase(s, tc_core[2]);
  tc_core[3] = tcase_create("strtok");
  tcase_add_test(tc_core[3], s21_strtok_test);
  suite_add_tcase(s, tc_core[3]);
  tc_core[4] = tcase_create("strpbrk");
  tcase_add_test(tc_core[4], s21_strpbrk_test);
  suite_add_tcase(s, tc_core[4]);
  tc_core[5] = tcase_create("strcspn");
  tcase_add_test(tc_core[5], s21_strcspn_test);
  suite_add_tcase(s, tc_core[5]);
  tc_core[6] = tcase_create("memchr");
  tcase_add_test(tc_core[6], test_s21_memchr);
  suite_add_tcase(s, tc_core[6]);
  tc_core[7] = tcase_create("memcmp");
  tcase_add_test(tc_core[7], test_s21_memcmp);
  suite_add_tcase(s, tc_core[7]);
  tc_core[8] = tcase_create("memcpy");
  tcase_add_test(tc_core[8], test_s21_memcpy);
  suite_add_tcase(s, tc_core[8]);
  tc_core[9] = tcase_create("memset");
  tcase_add_test(tc_core[9], test_s21_memset);
  suite_add_tcase(s, tc_core[9]);
  tc_core[10] = tcase_create("strncat");
  tcase_add_test(tc_core[10], test_s21_strncat);
  suite_add_tcase(s, tc_core[10]);
  tc_core[11] = tcase_create("strerror");
  tcase_add_test(tc_core[11], test_s21_strerror);
  suite_add_tcase(s, tc_core[11]);
  tc_core[12] = tcase_create("strncmp");
  tcase_add_test(tc_core[12], s21_strncmp_tests);
  suite_add_tcase(s, tc_core[12]);
  tc_core[13] = tcase_create("strncmp");
  tcase_add_test(tc_core[13], s21_strncpy_tests);
  suite_add_tcase(s, tc_core[13]);

  tc_core[14] = tcase_create("sprintf int");
  tcase_add_test(tc_core[14], s21_sprintf_int_test);
  suite_add_tcase(s, tc_core[14]);

  tc_core[15] = tcase_create("sprintf double");
  tcase_add_test(tc_core[15], s21_sprintf_double_test);
  suite_add_tcase(s, tc_core[15]);

  tc_core[16] = tcase_create("sprintf char");
  tcase_add_test(tc_core[16], s21_sprintf_char_test);
  suite_add_tcase(s, tc_core[16]);

  tc_core[17] = tcase_create("sprintf string");
  tcase_add_test(tc_core[17], s21_sprintf_string_test);
  suite_add_tcase(s, tc_core[17]);

  tc_core[18] = tcase_create("sprintf unsigned");
  tcase_add_test(tc_core[18], s21_sprintf_unsigned_test);
  suite_add_tcase(s, tc_core[18]);

  tc_core[19] = tcase_create("space flag");
  tcase_add_test(tc_core[19], s21_sprintf_space_flag_test);
  suite_add_tcase(s, tc_core[19]);

  tc_core[20] = tcase_create("minus flag");
  tcase_add_test(tc_core[20], s21_sprintf_minus_flag_test);
  suite_add_tcase(s, tc_core[20]);

  tc_core[21] = tcase_create("plus flag");
  tcase_add_test(tc_core[21], s21_sprintf_plus_flag_test);
  suite_add_tcase(s, tc_core[21]);

  tc_core[22] = tcase_create("width flag");
  tcase_add_test(tc_core[22], s21_sprintf_width_test);
  suite_add_tcase(s, tc_core[22]);

  tc_core[23] = tcase_create("precision flag");
  tcase_add_test(tc_core[23], s21_sprintf_precision_test);
  suite_add_tcase(s, tc_core[23]);

  tc_core[24] = tcase_create("h flag");
  tcase_add_test(tc_core[24], s21_sprintf_h_flag_test);
  suite_add_tcase(s, tc_core[24]);

  tc_core[25] = tcase_create("l flag");
  tcase_add_test(tc_core[25], s21_sprintf_l_flag_test);
  suite_add_tcase(s, tc_core[25]);

  tc_core[26] = tcase_create("test_s21_sprintf_FLOAT_formats_Jeff");
  tcase_add_test(tc_core[26], test_s21_sprintf_FLOAT_formats_Jeff);
  suite_add_tcase(s, tc_core[26]);

  tc_core[27] = tcase_create("test_s21_sprintf_INTEGER_formats_Jeff");
  tcase_add_test(tc_core[27], test_s21_sprintf_INTEGER_formats_Jeff);
  suite_add_tcase(s, tc_core[27]);

  tc_core[28] = tcase_create("s21_sprintf_PERCENT_test");
  tcase_add_test(tc_core[28], s21_sprintf_PERCENT_test);
  suite_add_tcase(s, tc_core[28]);

  tc_core[29] = tcase_create("test_s21_trim");
  tcase_add_test(tc_core[29], test_s21_trim);
  suite_add_tcase(s, tc_core[29]);

  tc_core[30] = tcase_create("test_s21_strstr");
  tcase_add_test(tc_core[30], test_s21_strstr);
  suite_add_tcase(s, tc_core[30]);

  tc_core[31] = tcase_create("test_s21_sprintf_flags_x_o_p_prcnt");
  tcase_add_test(tc_core[31], test_s21_sprintf_flags_x_o_p_prcnt);
  suite_add_tcase(s, tc_core[31]);

  tc_core[32] = tcase_create("test_s21_sprintf_flag_s");
  tcase_add_test(tc_core[32], test_s21_sprintf_flag_s);
  suite_add_tcase(s, tc_core[32]);

  tc_core[33] = tcase_create("test_s21_to_lower_classic");
  tcase_add_test(tc_core[33], test_s21_to_lower_classic);
  suite_add_tcase(s, tc_core[33]);

  tc_core[34] = tcase_create("test_s21_to_lower_empty");
  tcase_add_test(tc_core[34], test_s21_to_lower_empty);
  suite_add_tcase(s, tc_core[34]);

  tc_core[35] = tcase_create("test_s21_to_lower_full_low");
  tcase_add_test(tc_core[35], test_s21_to_lower_full_low);
  suite_add_tcase(s, tc_core[35]);

  tc_core[36] = tcase_create("test_s21_to_upper_classic");
  tcase_add_test(tc_core[36], test_s21_to_upper_classic);
  suite_add_tcase(s, tc_core[36]);

  tc_core[37] = tcase_create("test_s21_to_upper_empty");
  tcase_add_test(tc_core[37], test_s21_to_upper_empty);
  suite_add_tcase(s, tc_core[37]);

  tc_core[38] = tcase_create("s21_sprintf_unsigned_integers_test");
  tcase_add_test(tc_core[38], s21_sprintf_unsigned_integers_test);
  suite_add_tcase(s, tc_core[38]);

  tc_core[39] = tcase_create("s21_sprintf_float_int_integers_test");
  tcase_add_test(tc_core[39], s21_sprintf_float_int_integers_test);
  suite_add_tcase(s, tc_core[39]);

  tc_core[40] = tcase_create("s21_sprintf_string_char_test");
  tcase_add_test(tc_core[40], s21_sprintf_string_char_test);
  suite_add_tcase(s, tc_core[40]);

  tc_core[41] = tcase_create("s21_sprintf_pointer_test");
  tcase_add_test(tc_core[41], s21_sprintf_pointer_test);
  suite_add_tcase(s, tc_core[41]);

  tc_core[42] = tcase_create("s21_insert_test");
  tcase_add_test(tc_core[42], s21_insert_first_test);
  suite_add_tcase(s, tc_core[42]);

  tc_core[43] = tcase_create("s21_insert_test");
  tcase_add_test(tc_core[43], s21_insert_second_test);
  suite_add_tcase(s, tc_core[43]);

  tc_core[44] = tcase_create("s21_insert_test");
  tcase_add_test(tc_core[44], s21_insert_third_test);
  suite_add_tcase(s, tc_core[44]);
  return s;
}
