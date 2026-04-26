#include "tests.h"

START_TEST(null_float) {
  s21_decimal num_96 = {.bits = {3, 0, 0, 0}};

  int result = s21_from_decimal_to_float(num_96, S21_NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite* s21_from_decimal_to_float_suite() {
  Suite* s = suite_create("s21_from_decimal_to_float");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, null_float);

  suite_add_tcase(s, tc);

  return s;
}