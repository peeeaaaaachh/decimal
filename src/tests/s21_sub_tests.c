#include <check.h>

#include "../s21_decimal.h"
#include "tests.h"

// Helper functions
static inline void test_make_decimal_u32(s21_decimal* dec, unsigned int value,
                                         int scale, int sign) {
  if (!dec) return;
  for (int i = 0; i < 4; i++) dec->bits[i] = 0;
  dec->bits[0] = value;
  dec->bits[3] = (scale << 16) | (sign ? (1u << 31) : 0);
}

static inline void test_make_decimal(s21_decimal* dec, unsigned int low,
                                     unsigned int mid, unsigned int high,
                                     int scale, int sign) {
  if (!dec) return;
  dec->bits[0] = low;
  dec->bits[1] = mid;
  dec->bits[2] = high;
  dec->bits[3] = (scale << 16) | (sign ? (1u << 31) : 0);
}

static inline void test_assert_decimal_equal(s21_decimal result,
                                             s21_decimal expected) {
  for (int i = 0; i < 4; i++) {
    ck_assert_msg(result.bits[i] == expected.bits[i],
                  "bits[%d] mismatch: got %u (0x%X), expected %u (0x%X)", i,
                  result.bits[i], result.bits[i], expected.bits[i],
                  expected.bits[i]);
  }
}

static void test_make_big_decimal(big_decimal* dst, unsigned int b0,
                                  unsigned int b1, unsigned int b2,
                                  unsigned int b3, unsigned int b4,
                                  unsigned int b5, unsigned int b6) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = 0u;
  }

  dst->bits[0] = b0;
  dst->bits[1] = b1;
  dst->bits[2] = b2;
  dst->bits[3] = b3;
  dst->bits[4] = b4;
  dst->bits[5] = b5;
  dst->bits[6] = b6;
}

START_TEST(test_sub_simple_positive) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 500u, 0, 0);
  test_make_decimal_u32(&b, 200u, 0, 0);
  test_make_decimal_u32(&expected, 300u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_simple_negative) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 200u, 0, 0);
  test_make_decimal_u32(&b, 500u, 0, 0);
  test_make_decimal_u32(&expected, 300u, 0, 1);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_negative_negative_result_positive) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 300u, 0, 1);
  test_make_decimal_u32(&b, 500u, 0, 1);
  test_make_decimal_u32(&expected, 200u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_negative_negative_result_negative) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 500u, 0, 1);
  test_make_decimal_u32(&b, 300u, 0, 1);
  test_make_decimal_u32(&expected, 200u, 0, 1);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_positive_negative) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 0, 0);
  test_make_decimal_u32(&b, 200u, 0, 1);
  test_make_decimal_u32(&expected, 300u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_negative_positive) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 0, 1);
  test_make_decimal_u32(&b, 200u, 0, 0);
  test_make_decimal_u32(&expected, 300u, 0, 1);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_zero) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 12345u, 2, 0);  // 123.45
  test_make_decimal_u32(&b, 0u, 0, 0);
  test_make_decimal_u32(&expected, 12345u, 2, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_result_zero) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 0, 0);
  test_make_decimal_u32(&b, 100u, 0, 0);
  test_make_decimal_u32(&expected, 0u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_different_scales) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 2, 0);         // 1.00
  test_make_decimal_u32(&b, 1u, 3, 0);           // 0.001
  test_make_decimal_u32(&expected, 999u, 3, 0);  // 0.999

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_equivalent_scales) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 5000u, 3, 0);         // 5.000
  test_make_decimal_u32(&b, 2u, 0, 0);            // 2
  test_make_decimal_u32(&expected, 3000u, 3, 0);  // 3.000

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_sub_borrow_from_bits1_to_bits0) {
  s21_decimal a, b, result, expected;

  test_make_decimal(&a, 0u, 1u, 0u, 0, 0);
  test_make_decimal_u32(&b, 1u, 0, 0);
  test_make_decimal(&expected, 0xFFFFFFFFu, 0u, 0u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], expected.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(s21_get_scale(result), 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_sub_borrow_from_bits2_to_bits1) {
  s21_decimal a, b, result, expected;

  test_make_decimal(&a, 0u, 0u, 1u, 0, 0);
  test_make_decimal(&b, 0u, 1u, 0u, 0, 0);
  test_make_decimal(&expected, 0u, 0xFFFFFFFFu, 0u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], expected.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(s21_get_scale(result), 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_sub_negative_overflow) {
  s21_decimal a, b, result;

  test_make_decimal(&a, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 1);
  test_make_decimal_u32(&b, 1u, 0, 0);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_sub_positive_overflow) {
  s21_decimal a, b, result;

  test_make_decimal(&a, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 0);
  test_make_decimal_u32(&b, 1u, 0, 1);

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_big_sub_simple) {
  big_decimal a, b, result, expected;

  test_make_big_decimal(&a, 5u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 2u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 3u, 0u, 0u, 0u, 0u, 0u, 0u);

  s21_big_sub(&a, &b, &result);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_sub_borrow_bits1_to_bits0) {
  big_decimal a, b, result, expected;

  test_make_big_decimal(&a, 0u, 1u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 1u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u);

  s21_big_sub(&a, &b, &result);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_sub_borrow_bits2_to_bits1) {
  big_decimal a, b, result, expected;

  test_make_big_decimal(&a, 0u, 0u, 1u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 0u, 1u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u);

  s21_big_sub(&a, &b, &result);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_sub_equal_numbers) {
  big_decimal a, b, result;

  test_make_big_decimal(&a, 123u, 456u, 789u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 123u, 456u, 789u, 0u, 0u, 0u, 0u);

  s21_big_sub(&a, &b, &result);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0u);
  }
}
END_TEST

START_TEST(test_s21_sub_null_result) {
  s21_decimal a = {0};
  s21_decimal b = {0};

  int res = s21_sub(a, b, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_sub_suite(void) {
  Suite* s = suite_create("s21_sub");
  TCase* tc = tcase_create("sub_core");

  tcase_add_test(tc, test_sub_simple_positive);
  tcase_add_test(tc, test_sub_simple_negative);
  tcase_add_test(tc, test_sub_negative_negative_result_positive);
  tcase_add_test(tc, test_sub_negative_negative_result_negative);
  tcase_add_test(tc, test_sub_positive_negative);
  tcase_add_test(tc, test_sub_negative_positive);
  tcase_add_test(tc, test_sub_zero);
  tcase_add_test(tc, test_sub_result_zero);
  tcase_add_test(tc, test_sub_different_scales);
  tcase_add_test(tc, test_sub_equivalent_scales);
  tcase_add_test(tc, test_sub_borrow_from_bits1_to_bits0);
  tcase_add_test(tc, test_sub_borrow_from_bits2_to_bits1);
  tcase_add_test(tc, test_sub_negative_overflow);
  tcase_add_test(tc, test_sub_positive_overflow);
  tcase_add_test(tc, test_big_sub_simple);
  tcase_add_test(tc, test_big_sub_borrow_bits1_to_bits0);
  tcase_add_test(tc, test_big_sub_borrow_bits2_to_bits1);
  tcase_add_test(tc, test_big_sub_equal_numbers);
  tcase_add_test(tc, test_s21_sub_null_result);

  suite_add_tcase(s, tc);
  return s;
}