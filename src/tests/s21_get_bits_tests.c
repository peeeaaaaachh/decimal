#include "tests.h"

START_TEST(test_get_bits_1) {
  big_decimal bits = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_get_bits(bits, 0), 1);
}
END_TEST

START_TEST(test_get_bits_2) {
  big_decimal bits = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_get_bits(bits, 1), 0);
}
END_TEST

START_TEST(test_get_bits_3) {
  big_decimal bits = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_get_bits(bits, 1), 0);
}
END_TEST

START_TEST(test_get_bits_4) {
  big_decimal bits = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_get_bits(bits, 32), 1);
}
END_TEST

START_TEST(test_get_bits_5) {
  big_decimal bits = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_get_bits(bits, 33), 0);
}
END_TEST

START_TEST(test_get_bits_autotest_1) {
  big_decimal bits = {{0xFFFFFFFF, 0, 0, 0}};
  for (int i = 0; i < 32; i++) {
    ck_assert_int_eq(s21_get_bits(bits, i), 1);
  }
}
END_TEST

START_TEST(test_get_bits_autotest_2) {
  big_decimal bits = {{0xFFFFFFFF, 0, 0, 0}};
  for (int i = 32; i < 128; i++) {
    ck_assert_int_eq(s21_get_bits(bits, i), 0);
  }
}
END_TEST

Suite* s21_get_bits_suite(void) {
  Suite* s = suite_create("s21_get_bits");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_get_bits_1);
  tcase_add_test(tc_core, test_get_bits_2);
  tcase_add_test(tc_core, test_get_bits_3);
  tcase_add_test(tc_core, test_get_bits_4);
  tcase_add_test(tc_core, test_get_bits_5);
  tcase_add_test(tc_core, test_get_bits_autotest_1);
  tcase_add_test(tc_core, test_get_bits_autotest_2);

  suite_add_tcase(s, tc_core);
  return s;
}