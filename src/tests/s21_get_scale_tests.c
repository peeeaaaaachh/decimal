#include "tests.h"

START_TEST(test_get_scale_1) {
  s21_decimal bits = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_get_scale(bits), 0);
}
END_TEST

START_TEST(test_get_scale_2) {
  s21_decimal bits = {{0, 1, 0, 28 << 16}};
  ck_assert_int_eq(s21_get_scale(bits), 28);
}
END_TEST

START_TEST(test_get_scale_3) {
  s21_decimal bits = {{0, 0, 0, 0x00080000}};
  ck_assert_int_eq(s21_get_scale(bits), 8);
}
END_TEST

START_TEST(test_get_scale_4) {
  s21_decimal bits = {{0, 1, 0, 0x00880000}};
  ck_assert_int_eq(s21_get_scale(bits), 136);
}
END_TEST

START_TEST(test_get_scale_5) {
  s21_decimal bits = {{0, 1, 0, 300 << 16}};
  ck_assert_int_eq(s21_get_scale(bits), 44);
}
END_TEST

Suite* s21_get_scale_suite(void) {
  Suite* s = suite_create("s21_get_scale");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_get_scale_1);
  tcase_add_test(tc_core, test_get_scale_2);
  tcase_add_test(tc_core, test_get_scale_3);
  tcase_add_test(tc_core, test_get_scale_4);
  tcase_add_test(tc_core, test_get_scale_5);

  suite_add_tcase(s, tc_core);
  return s;
}