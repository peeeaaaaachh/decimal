#include "tests.h"

START_TEST(positive_number) {
  float num_32 = 3.14;
  s21_decimal num_96 = {0};
  float num_back;

  int result = s21_from_float_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  result = s21_from_decimal_to_float(num_96, &num_back);
  ck_assert_int_eq(result, 0);

  // Сравниваем с погрешностью float
  ck_assert_float_eq_tol(num_32, num_back, 1e-6);
}
END_TEST

START_TEST(negative_number) {
  float num_32 = -3.14;
  s21_decimal num_96 = {0};
  float num_back;

  int result = s21_from_float_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  result = s21_from_decimal_to_float(num_96, &num_back);
  ck_assert_int_eq(result, 0);

  // Сравниваем с погрешностью float
  ck_assert_float_eq_tol(num_32, num_back, 1e-6);
}
END_TEST

START_TEST(max_number) {
  float num_32 = 437637469437985798465.0000000000000000009;
  s21_decimal num_96 = {0};
  float num_back;

  int result = s21_from_float_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  result = s21_from_decimal_to_float(num_96, &num_back);
  ck_assert_int_eq(result, 0);

  // Сравниваем с погрешностью float
  ck_assert_float_eq_tol(num_32, num_back, 1e-6);
}
END_TEST

START_TEST(zero_number) {
  float num_32 = 0.0;
  s21_decimal num_96 = {0};
  float num_back;

  int result = s21_from_float_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  result = s21_from_decimal_to_float(num_96, &num_back);
  ck_assert_int_eq(result, 0);

  // Сравниваем с погрешностью float
  ck_assert_float_eq_tol(num_32, num_back, 1e-6);
}
END_TEST

START_TEST(null_decimal) {
  float num_32 = 0.0;

  int result = s21_from_float_to_decimal(num_32, S21_NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(bank_round) {
  float num_32 = 2.546789;
  s21_decimal num_96 = {0};
  float num_back;

  int result = s21_from_float_to_decimal(num_32, &num_96);
  ck_assert_int_eq(result, 0);

  result = s21_from_decimal_to_float(num_96, &num_back);
  ck_assert_int_eq(result, 0);

  // Сравниваем с погрешностью float
  ck_assert_float_eq_tol(num_32, num_back, 1e-6);
}
END_TEST

Suite *s21_from_float_to_decimal_suite() {
  Suite *s = suite_create("s21_from_float_to_decimal");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, positive_number);
  tcase_add_test(tc, negative_number);
  tcase_add_test(tc, bank_round);
  tcase_add_test(tc, max_number);
  tcase_add_test(tc, zero_number);
  tcase_add_test(tc, null_decimal);

  suite_add_tcase(s, tc);

  return s;
}