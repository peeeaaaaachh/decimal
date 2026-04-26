#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "./../s21_decimal.h"

// Helper functions:
Suite *s21_get_bits_suite(void);
Suite *s21_get_sign_suite(void);
Suite *s21_get_scale_suite(void);
Suite *s21_set_scale_suite(void);
Suite *s21_big_shift_left_suite(void);
Suite *s21_big_shift_right_suite(void);
Suite *s21_get_bits_suite(void);
Suite *s21_get_sign_suite(void);
Suite *s21_get_scale_suite(void);
Suite *s21_set_scale_suite(void);

// Convertors and parsers:
Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_decimal_to_float_suite(void);

// Arithmetic Operators:
Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);

// Comparison Operators:
Suite *s21_is_less_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_less_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_not_equal_suite(void);

// Other
Suite *s21_round_suite(void);
Suite *s21_floor_suite(void);
Suite *s21_fit_big_into_decimal_suite(void);
Suite *s21_negate_suite(void);

#endif