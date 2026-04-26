#include "tests.h"

START_TEST(positive_number) {
  int num_32 = 123;
  s21_decimal num_96;

  int result = s21_from_int_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(num_96.bits[0], 123);
  ck_assert_int_eq(num_96.bits[1], 0);
  ck_assert_int_eq(num_96.bits[2], 0);
  ck_assert_int_eq(num_96.bits[3], 0);
}
END_TEST

START_TEST(negative_number) {
  int num_32 = -456;
  s21_decimal num_96;

  int result = s21_from_int_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(num_96.bits[0], 456);
  ck_assert_int_eq(num_96.bits[1], 0);
  ck_assert_int_eq(num_96.bits[2], 0);
  ck_assert_int_eq(num_96.bits[3], 0x80000000U);
}
END_TEST

START_TEST(min_number) {
  int num_32 = INT_MIN;  //-2147483648
  s21_decimal num_96;

  int result = s21_from_int_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(num_96.bits[0], 2147483648U);
  ck_assert_int_eq(num_96.bits[1], 0);
  ck_assert_int_eq(num_96.bits[2], 0);
  ck_assert_int_eq(num_96.bits[3], 0x80000000U);
}
END_TEST

START_TEST(max_number) {
  int num_32 = INT_MAX;  // 2147483647
  s21_decimal num_96;

  int result = s21_from_int_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(num_96.bits[0], 2147483647);
  ck_assert_int_eq(num_96.bits[1], 0);
  ck_assert_int_eq(num_96.bits[2], 0);
  ck_assert_int_eq(num_96.bits[3], 0);
}
END_TEST

START_TEST(zero_number) {
  int num_32 = 0;
  s21_decimal num_96;

  int result = s21_from_int_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(num_96.bits[0], 0);
  ck_assert_int_eq(num_96.bits[1], 0);
  ck_assert_int_eq(num_96.bits[2], 0);
  ck_assert_int_eq(num_96.bits[3], 0);
}
END_TEST

START_TEST(null_decimal) {
  int num_32 = 25;

  int result = s21_from_int_to_decimal(num_32, S21_NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite* s21_from_int_to_decimal_suite() {
  Suite* s = suite_create("s21_from_int_to_decimal");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, positive_number);
  tcase_add_test(tc, negative_number);
  tcase_add_test(tc, min_number);
  tcase_add_test(tc, max_number);
  tcase_add_test(tc, zero_number);
  tcase_add_test(tc, null_decimal);

  suite_add_tcase(s, tc);

  return s;
}