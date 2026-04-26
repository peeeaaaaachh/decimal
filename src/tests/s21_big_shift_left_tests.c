#include "tests.h"

START_TEST(test_shift_left_1) {
  big_decimal bits = {{5, 0, 0, 0, 0, 0, 0}};
  s21_big_shift_left(&bits, 0);
  ck_assert_int_eq(bits.bits[0], 5);
  ck_assert_int_eq(bits.bits[1], 0);
  ck_assert_int_eq(bits.bits[2], 0);
  ck_assert_int_eq(bits.bits[3], 0);
  ck_assert_int_eq(bits.bits[4], 0);
  ck_assert_int_eq(bits.bits[5], 0);
  ck_assert_int_eq(bits.bits[6], 0);
}
END_TEST

START_TEST(test_shift_left_2) {
  big_decimal bits = {{1, 0, 0, 0, 0, 0, 0}};
  s21_big_shift_left(&bits, 3);

  ck_assert_int_eq(bits.bits[0], 8);
  ck_assert_int_eq(bits.bits[1], 0);
  ck_assert_int_eq(bits.bits[2], 0);
  ck_assert_int_eq(bits.bits[4], 0);
  ck_assert_int_eq(bits.bits[5], 0);
  ck_assert_int_eq(bits.bits[6], 0);
}
END_TEST

START_TEST(test_shift_left_3) {
  big_decimal bits = {{0x80000000, 0, 4, 0, 0, 0, 0}};
  s21_big_shift_left(&bits, 1);
  ck_assert_int_eq(bits.bits[0], 0);
  ck_assert_int_eq(bits.bits[1], 1);
  ck_assert_int_eq(bits.bits[2], 8);
  ck_assert_int_eq(bits.bits[3], 0);
  ck_assert_int_eq(bits.bits[4], 0);
  ck_assert_int_eq(bits.bits[5], 0);
  ck_assert_int_eq(bits.bits[6], 0);
}
END_TEST

START_TEST(test_shift_left_4) {
  big_decimal bits = {{10, 0, 0, 0, 0, 0, 0}};
  s21_big_shift_left(&bits, 1);
  ck_assert_int_eq(bits.bits[0], 20);
  ck_assert_int_eq(bits.bits[1], 0);
  ck_assert_int_eq(bits.bits[2], 0);
  ck_assert_int_eq(bits.bits[4], 0);
  ck_assert_int_eq(bits.bits[5], 0);
  ck_assert_int_eq(bits.bits[6], 0);
}
END_TEST

START_TEST(test_shift_left_5) {
  big_decimal bits = {{10, 4, 10, 0, 0, 0, 0}};
  s21_big_shift_left(&bits, 3);
  ck_assert_int_eq(bits.bits[0], 80);
  ck_assert_int_eq(bits.bits[1], 32);
  ck_assert_int_eq(bits.bits[2], 80);
  ck_assert_int_eq(bits.bits[4], 0);
  ck_assert_int_eq(bits.bits[5], 0);
  ck_assert_int_eq(bits.bits[6], 0);
}
END_TEST

START_TEST(test_shift_left_6) {
  big_decimal bits = {{5, 0, 0, 0, 0, 0, 0}};
  int result = s21_big_shift_left(&bits, -1);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(bits.bits[0], 5);
}
END_TEST

START_TEST(test_shift_left_7) {
  big_decimal bits = {{0, 0, 0, 0, 0, 0x80000000, 0}};

  int result = s21_big_shift_left(&bits, 1);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_shift_left_autotest_1) {
  for (int n = 0; n < 10; n++) {
    big_decimal bits = {{1, 0, 0, 0, 0, 0, 0}};
    s21_big_shift_left(&bits, n);
    int expected = 1 << n;
    ck_assert_int_eq(bits.bits[0], expected);
  }
}
END_TEST

Suite* s21_big_shift_left_suite(void) {
  Suite* s = suite_create("s21_shift_left");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_shift_left_1);
  tcase_add_test(tc_core, test_shift_left_2);
  tcase_add_test(tc_core, test_shift_left_3);
  tcase_add_test(tc_core, test_shift_left_4);
  tcase_add_test(tc_core, test_shift_left_5);
  tcase_add_test(tc_core, test_shift_left_6);
  tcase_add_test(tc_core, test_shift_left_7);
  tcase_add_test(tc_core, test_shift_left_autotest_1);

  suite_add_tcase(s, tc_core);
  return s;
}
