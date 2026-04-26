#include "tests.h"

START_TEST(test_set_scale_1) {
  s21_decimal bits = {{0, 1, 0, 28}};
  s21_set_scale(&bits, 0);
  ck_assert_int_eq(s21_get_scale(bits), 0);
}
END_TEST

START_TEST(test_set_scale_2) {
  s21_decimal bits = {{0, 1, 0, 0}};
  s21_set_scale(&bits, 25);
  ck_assert_int_eq(s21_get_scale(bits), 25);
}
END_TEST

START_TEST(test_set_scale_3) {
  s21_decimal bits = {{36, 0, 0, 0}};
  s21_set_scale(&bits, 136);
  ck_assert_int_eq(s21_get_scale(bits), 136);
}
END_TEST

START_TEST(test_set_scale_4) {
  s21_decimal bits = {{0, 0, 0, 0x00880000}};
  s21_set_scale(&bits, 300);
  ck_assert_int_eq(s21_get_scale(bits), 44);
}
END_TEST

START_TEST(test_set_scale_5) {
  s21_decimal bits = {{0, 0, 0, 0x00800000}};
  s21_set_scale(&bits, 83);
  ck_assert_int_eq(s21_get_scale(bits), 83);
}
END_TEST

START_TEST(test_set_scale_autotest_1) {
  for (int scale = 0; scale <= 28; scale++) {
    s21_decimal bits = {{0}};
    s21_set_scale(&bits, scale);
    ck_assert_int_eq(s21_get_scale(bits), scale);
  }
}
END_TEST

Suite* s21_set_scale_suite(void) {
  Suite* s = suite_create("s21_set_scale");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_set_scale_1);
  tcase_add_test(tc_core, test_set_scale_2);
  tcase_add_test(tc_core, test_set_scale_3);
  tcase_add_test(tc_core, test_set_scale_4);
  tcase_add_test(tc_core, test_set_scale_5);
  tcase_add_test(tc_core, test_set_scale_autotest_1);

  suite_add_tcase(s, tc_core);
  return s;
}