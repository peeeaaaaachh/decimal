#include <check.h>

#include "../s21_decimal.h"
#include "tests.h"

// Helper functions (inline)
static inline void test_make_decimal_u32(s21_decimal* dec, unsigned int value,
                                         int scale, int sign) {
  if (!dec) return;

  for (int i = 0; i < 4; i++) {
    dec->bits[i] = 0;
  }

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

START_TEST(test_add_simple_positive) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 123u, 0, 0);
  test_make_decimal_u32(&b, 456u, 0, 0);
  test_make_decimal_u32(&expected, 579u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_different_scales) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 123u, 2, 0);          // 1.23
  test_make_decimal_u32(&b, 456u, 1, 0);          // 45.6
  test_make_decimal_u32(&expected, 4683u, 2, 0);  // 46.83

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_negative_negative) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 0, 1);
  test_make_decimal_u32(&b, 200u, 0, 1);
  test_make_decimal_u32(&expected, 300u, 0, 1);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_positive_negative_result_positive) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 500u, 0, 0);
  test_make_decimal_u32(&b, 300u, 0, 1);
  test_make_decimal_u32(&expected, 200u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_positive_negative_result_negative) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 200u, 0, 0);
  test_make_decimal_u32(&b, 500u, 0, 1);
  test_make_decimal_u32(&expected, 300u, 0, 1);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_zero) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 12345u, 3, 0);  // 12.345
  test_make_decimal_u32(&b, 0u, 0, 0);
  test_make_decimal_u32(&expected, 12345u, 3, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_result_zero) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 100u, 0, 0);
  test_make_decimal_u32(&b, 100u, 0, 1);
  test_make_decimal_u32(&expected, 0u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_positive_and_negative_zero) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 0u, 0, 0);
  test_make_decimal_u32(&b, 0u, 0, 1);
  test_make_decimal_u32(&expected, 0u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_equivalent_scales) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 10u, 1, 0);          // 1.0
  test_make_decimal_u32(&b, 200u, 2, 0);         // 2.00
  test_make_decimal_u32(&expected, 300u, 2, 0);  // 3.00

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_small_fractional_scales) {
  s21_decimal a, b, result, expected;

  test_make_decimal_u32(&a, 1u, 2, 0);           // 0.01
  test_make_decimal_u32(&b, 1u, 4, 0);           // 0.0001
  test_make_decimal_u32(&expected, 101u, 4, 0);  // 0.0101

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  test_assert_decimal_equal(result, expected);
}
END_TEST

START_TEST(test_add_carry_from_bits0_to_bits1) {
  s21_decimal a, b, result, expected;

  test_make_decimal(&a, 0xFFFFFFFFu, 0u, 0u, 0, 0);
  test_make_decimal_u32(&b, 1u, 0, 0);
  test_make_decimal(&expected, 0u, 1u, 0u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], expected.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(s21_get_scale(result), 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_add_carry_from_bits1_to_bits2) {
  s21_decimal a, b, result, expected;

  test_make_decimal(&a, 0u, 0xFFFFFFFFu, 0u, 0, 0);
  test_make_decimal(&b, 0u, 1u, 0u, 0, 0);
  test_make_decimal(&expected, 0u, 0u, 1u, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], expected.bits[0]);
  ck_assert_uint_eq(result.bits[1], expected.bits[1]);
  ck_assert_uint_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(s21_get_scale(result), 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_add_positive_overflow) {
  s21_decimal a, b, result;

  test_make_decimal(&a, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 0);
  test_make_decimal(&b, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 0);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_add_negative_overflow) {
  s21_decimal a, b, result;

  test_make_decimal(&a, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 1);
  test_make_decimal(&b, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0, 1);

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_add_null_result) {
  s21_decimal a, b;

  test_make_decimal_u32(&a, 10u, 0, 0);
  test_make_decimal_u32(&b, 20u, 0, 0);

  int status = s21_add(a, b, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_big_add_bits_simple) {
  big_decimal a = {0}, b = {0}, result = {0}, expected = {0};

  test_make_big_decimal(&a, 1u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 2u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 3u, 0u, 0u, 0u, 0u, 0u, 0u);

  int carry = s21_add_bits(&a, &b, &result);

  ck_assert_int_eq(carry, 0);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_add_bits_carry_bits0_to_bits1) {
  big_decimal a = {0}, b = {0}, result = {0}, expected = {0};

  test_make_big_decimal(&a, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 1u, 0u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 0u, 1u, 0u, 0u, 0u, 0u, 0u);

  int carry = s21_add_bits(&a, &b, &result);

  ck_assert_int_eq(carry, 0);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_add_bits_carry_bits1_to_bits2) {
  big_decimal a = {0}, b = {0}, result = {0}, expected = {0};

  test_make_big_decimal(&a, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&b, 0u, 1u, 0u, 0u, 0u, 0u, 0u);
  test_make_big_decimal(&expected, 0u, 0u, 1u, 0u, 0u, 0u, 0u);

  int carry = s21_add_bits(&a, &b, &result);

  ck_assert_int_eq(carry, 0);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_big_add_bits_full_overflow) {
  big_decimal a = {0}, b = {0}, result = {0};

  test_make_big_decimal(&a, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                        0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu);
  test_make_big_decimal(&b, 1u, 0u, 0u, 0u, 0u, 0u, 0u);

  int carry = s21_add_bits(&a, &b, &result);

  ck_assert_int_eq(carry, 1);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0u);
  }
}
END_TEST

Suite* s21_add_suite(void) {
  Suite* s = suite_create("s21_add");
  TCase* tc = tcase_create("add_core");

  tcase_add_test(tc, test_add_simple_positive);
  tcase_add_test(tc, test_add_different_scales);
  tcase_add_test(tc, test_add_negative_negative);
  tcase_add_test(tc, test_add_positive_negative_result_positive);
  tcase_add_test(tc, test_add_positive_negative_result_negative);
  tcase_add_test(tc, test_add_zero);
  tcase_add_test(tc, test_add_result_zero);
  tcase_add_test(tc, test_add_positive_and_negative_zero);
  tcase_add_test(tc, test_add_equivalent_scales);
  tcase_add_test(tc, test_add_small_fractional_scales);
  tcase_add_test(tc, test_add_carry_from_bits0_to_bits1);
  tcase_add_test(tc, test_add_carry_from_bits1_to_bits2);
  tcase_add_test(tc, test_add_positive_overflow);
  tcase_add_test(tc, test_add_negative_overflow);
  tcase_add_test(tc, test_add_null_result);
  tcase_add_test(tc, test_big_add_bits_simple);
  tcase_add_test(tc, test_big_add_bits_carry_bits0_to_bits1);
  tcase_add_test(tc, test_big_add_bits_carry_bits1_to_bits2);
  tcase_add_test(tc, test_big_add_bits_full_overflow);

  suite_add_tcase(s, tc);
  return s;
}