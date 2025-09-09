#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_sprintf_test.h"
#include "s21_string_test.h"

int main() {
  Suite* suites[2] = {sprintf_suite(), s21_string_suite()};
  SRunner* sr = srunner_create(suites[0]);
  for (long unsigned int i = 1; i < sizeof(suites) / sizeof(suites[0]); i++)
    srunner_add_suite(sr, suites[i]);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);
  int flag = EXIT_SUCCESS;
  if (failed_count != 0) {
    flag = EXIT_FAILURE;
  }
  return flag;
}