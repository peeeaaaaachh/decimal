#include "tests.h"

START_TEST(test_get_sign_1) {
  s21_decimal bits = {{0, 0, 0, SIGN}};
  ck_assert_int_eq(s21_get_sign(bits), 1);
}
END_TEST

START_TEST(test_get_sign_2) {
  s21_decimal bits = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_get_sign(bits), 1);
}
END_TEST

START_TEST(test_get_sign_3) {
  s21_decimal bits = {{0, 0, 0, ~SIGN}};
  ck_assert_int_eq(s21_get_sign(bits), 0);
}
END_TEST

START_TEST(test_get_sign_4) {
  s21_decimal bits = {{0, 1, 0, ~SIGN}};
  ck_assert_int_eq(s21_get_sign(bits), 0);
}
END_TEST

START_TEST(test_get_sign_5) {
  s21_decimal bits = {0};
  ck_assert_int_eq(s21_get_sign(bits), 0);
}
END_TEST

Suite* s21_get_sign_suite(void) {
  Suite* s = suite_create("s21_get_sign");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_get_sign_1);
  tcase_add_test(tc_core, test_get_sign_2);
  tcase_add_test(tc_core, test_get_sign_3);
  tcase_add_test(tc_core, test_get_sign_4);
  tcase_add_test(tc_core, test_get_sign_5);

  suite_add_tcase(s, tc_core);
  return s;
}