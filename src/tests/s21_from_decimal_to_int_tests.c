#include "tests.h"

START_TEST(null_int) {
  s21_decimal num_96 = {.bits = {987, 0, 0, 0}};

  int result = s21_from_decimal_to_int(num_96, S21_NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(zero_number) {
  s21_decimal num_96 = {.bits = {0, 0, 0, 0}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, 0);
}
END_TEST

START_TEST(positive_32_bit_number_without_scale) {
  s21_decimal num_96 = {.bits = {123, 0, 0, 0}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, 123);
}
END_TEST

START_TEST(negative_32_bit_number_without_scale) {
  s21_decimal num_96 = {.bits = {456, 0, 0, 0x80000000U}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, -456);
}
END_TEST

START_TEST(positive_32_bit_number_with_scale) {
  s21_decimal num_96 = {.bits = {12345, 0, 0, 0x00030000U}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, 12);
}
END_TEST

START_TEST(negative_32_bit_number_with_scale) {
  s21_decimal num_96 = {.bits = {45678, 0, 0, 0x80030000U}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, -45);
}
END_TEST

START_TEST(positive_64_bit_number) {
  s21_decimal num_96 = {.bits = {123, 456, 0, 0}};
  int num_32;

  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(negative_64_bit_number) {
  s21_decimal num_96 = {.bits = {987, 654, 0, 0x80000000U}};
  int num_32;

  int result = s21_from_decimal_to_int(num_96, &num_32);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(positive_96_bit_number) {
  s21_decimal num_96 = {.bits = {123, 0, 456, 0}};
  int num_32;

  int result = s21_from_decimal_to_int(num_96, &num_32);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(negative_96_bit_number) {
  s21_decimal num_96 = {.bits = {987, 0, 654, 0x80000000U}};
  int num_32;

  int result = s21_from_decimal_to_int(num_96, &num_32);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(min_32_bit_number) {
  s21_decimal num_96 = {.bits = {2147483648U, 0, 0, 0x80000000U}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, INT_MIN);
}
END_TEST

START_TEST(max_32_bit_number) {
  s21_decimal num_96 = {.bits = {2147483647, 0, 0, 0}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(num_32, INT_MAX);
}
END_TEST

START_TEST(overflow_32_bit_number) {
  s21_decimal num_96 = {.bits = {2147483648U, 0, 0, 0}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(overflow_scale_large) {
  s21_decimal num_96 = {.bits = {345, 0, 0, 0x001D0000}};
  int num_32;
  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(overflow_scale) {
  s21_decimal num_96 = {.bits = {345, 0, 0, 0x001D0000}};
  int num_32 = 123;

  int result = s21_from_decimal_to_int(num_96, &num_32);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(num_32, 123);
}
END_TEST

Suite* s21_from_decimal_to_int_suite() {
  Suite* s = suite_create("s21_from_decimal_to_int");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, null_int);
  tcase_add_test(tc, zero_number);

  tcase_add_test(tc, positive_32_bit_number_without_scale);
  tcase_add_test(tc, negative_32_bit_number_without_scale);
  tcase_add_test(tc, positive_32_bit_number_with_scale);
  tcase_add_test(tc, negative_32_bit_number_with_scale);

  tcase_add_test(tc, positive_64_bit_number);
  tcase_add_test(tc, negative_64_bit_number);

  tcase_add_test(tc, positive_96_bit_number);
  tcase_add_test(tc, negative_96_bit_number);

  tcase_add_test(tc, min_32_bit_number);
  tcase_add_test(tc, max_32_bit_number);

  tcase_add_test(tc, overflow_32_bit_number);
  tcase_add_test(tc, overflow_scale_large);
  tcase_add_test(tc, overflow_scale);

  suite_add_tcase(s, tc);

  return s;
}