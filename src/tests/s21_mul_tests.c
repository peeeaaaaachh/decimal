#include "tests.h"

START_TEST(mul_null) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};

  int err = s21_mul(a, b, NULL);

  ck_assert_int_ne(err, 0);
}
END_TEST

START_TEST(mul_basic1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res = {0};

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(s21_get_scale(res), 0);
}
END_TEST

START_TEST(mul_basic2) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal res = {0};

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 50);
}
END_TEST

START_TEST(mul_fraction) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res;

  s21_set_scale(&a, 1);  // 0.1
  s21_set_scale(&b, 1);  // 0.2

  s21_mul(a, b, &res);

  // ожидаем 0.02 → mantissa = 2, scale = 2
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(s21_get_scale(res), 2);
}
END_TEST

START_TEST(mul_zero_1) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  s21_decimal res = {0};

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(mul_zero_2) {
  s21_decimal a = {{987654, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res = {0};

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(mul_sign_1) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  s21_set_sign(&a, 1);

  s21_mul(a, b, &res);

  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(mul_sign_2) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  s21_set_sign(&b, 1);

  s21_mul(a, b, &res);

  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(mul_sign_3) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  s21_mul(a, b, &res);

  ck_assert_int_eq(s21_get_sign(res), 0);
}
END_TEST

START_TEST(mul_scale_1) {
  s21_decimal a = {{25, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  s21_set_scale(&a, 1);

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 50);
  ck_assert_int_eq(s21_get_scale(res), 1);
}
END_TEST

START_TEST(mul_scale_2) {
  s21_decimal a = {{25, 0, 0, 0}};
  s21_decimal b = {{30, 0, 0, 0}};
  s21_decimal res = {0};

  s21_set_scale(&a, 30);
  s21_set_scale(&b, 3);
  s21_mul(a, b, &res);

  ck_assert_int_eq(s21_get_scale(res), 28);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(mul_big_1) {
  s21_decimal a = {{100000, 0, 0, 0}};
  s21_decimal b = {{3000, 0, 0, 0}};
  s21_decimal res = {0};

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 300000000);
}
END_TEST

START_TEST(mul_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(res.bits[1], 1);
}
END_TEST

START_TEST(mul_overflow_1) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(res.bits[0], a.bits[0]);
  ck_assert_int_eq(res.bits[1], a.bits[1]);
  ck_assert_int_eq(res.bits[2], a.bits[2]);
}
END_TEST

START_TEST(mul_overflow_2) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res = {0};

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(mul_scale_overflow) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);

  s21_mul(a, b, &res);

  ck_assert_int_le(s21_get_scale(res), 28);
}
END_TEST

START_TEST(mul_precision) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  s21_set_scale(&b, 1);  // * 0.1

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(mul_tiny) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  s21_set_scale(&a, 28);
  s21_set_scale(&b, 1);

  s21_mul(a, b, &res);

  ck_assert_int_le(s21_get_scale(res), 28);
}
END_TEST

START_TEST(mul_max_by_max) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res;

  int err = s21_mul(a, a, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(mul_max_by_minus_one) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  s21_set_sign(&b, 1);

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(mul_min_by_one) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res;

  s21_set_sign(&a, 1);  // отрицательный max

  s21_decimal b = {{1, 0, 0, 0}};

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(mul_min_by_min) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res;

  s21_set_sign(&a, 1);

  int err = s21_mul(a, a, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(mul_almost_max) {
  s21_decimal a = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal res;

  int err = s21_mul(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

Suite* s21_mul_suite(void) {
  Suite* s = suite_create("s21_mul");
  TCase* tc = tcase_create("mul");

  tcase_add_test(tc, mul_null);

  tcase_add_test(tc, mul_basic1);
  tcase_add_test(tc, mul_basic2);
  tcase_add_test(tc, mul_fraction);

  tcase_add_test(tc, mul_zero_1);
  tcase_add_test(tc, mul_zero_2);

  tcase_add_test(tc, mul_sign_1);
  tcase_add_test(tc, mul_sign_2);
  tcase_add_test(tc, mul_sign_3);

  tcase_add_test(tc, mul_scale_1);
  tcase_add_test(tc, mul_scale_2);

  tcase_add_test(tc, mul_big_1);
  tcase_add_test(tc, mul_carry);

  tcase_add_test(tc, mul_overflow_1);
  tcase_add_test(tc, mul_overflow_2);
  tcase_add_test(tc, mul_scale_overflow);
  tcase_add_test(tc, mul_precision);
  tcase_add_test(tc, mul_tiny);
  tcase_add_test(tc, mul_max_by_max);
  tcase_add_test(tc, mul_max_by_minus_one);
  tcase_add_test(tc, mul_min_by_one);
  tcase_add_test(tc, mul_min_by_min);
  tcase_add_test(tc, mul_almost_max);

  suite_add_tcase(s, tc);

  return s;
}