#include "tests.h"

int main() {
  int number_failed = 0;
  SRunner* sr;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, s21_get_bits_suite());
  srunner_add_suite(sr, s21_get_sign_suite());
  srunner_add_suite(sr, s21_get_scale_suite());
  srunner_add_suite(sr, s21_big_shift_left_suite());
  srunner_add_suite(sr, s21_set_scale_suite());
  srunner_add_suite(sr, s21_from_int_to_decimal_suite());
  srunner_add_suite(sr, s21_from_decimal_to_int_suite());
  srunner_add_suite(sr, s21_from_float_to_decimal_suite());
  srunner_add_suite(sr, s21_from_decimal_to_float_suite());

  srunner_add_suite(sr, s21_sub_suite());
  srunner_add_suite(sr, s21_add_suite());

  srunner_add_suite(sr, s21_mul_suite());
  srunner_add_suite(sr, s21_div_suite());

  srunner_add_suite(sr, s21_is_less_suite());
  srunner_add_suite(sr, s21_is_less_or_equal_suite());
  srunner_add_suite(sr, s21_is_greater_suite());
  srunner_add_suite(sr, s21_is_greater_or_equal_suite());
  srunner_add_suite(sr, s21_is_equal_suite());
  srunner_add_suite(sr, s21_is_not_equal_suite());

  srunner_add_suite(sr, s21_div_suite());
  srunner_add_suite(sr, s21_big_shift_right_suite());
  srunner_add_suite(sr, s21_big_shift_left_suite());

  srunner_add_suite(sr, s21_round_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_fit_big_into_decimal_suite());
  srunner_add_suite(sr, s21_negate_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed ? 1 : 0;
}