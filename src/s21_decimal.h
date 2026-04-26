#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define S21_NULL (void*)(0)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} big_decimal;

// Decimal values
s21_decimal s21_decimal_get_zero(void);
s21_decimal s21_decimal_get_one(void);
s21_decimal s21_decimal_get_05(void);

// Convertors and other:
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_floor(s21_decimal value, s21_decimal* result);
void s21_bank_round(big_decimal *mantissa, int *scale, int digits);

// Comparison Operators:
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_compare_mantissa(s21_decimal a, s21_decimal b);
int s21_base_compare(s21_decimal a, s21_decimal b);

// Arithmetic Operators:
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int mul_bits(big_decimal a, big_decimal b, big_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_add(s21_decimal a, s21_decimal b, s21_decimal* result);
int s21_add_bits(big_decimal* a, big_decimal* b, big_decimal* result);
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal* result);
int s21_mul_by_10(s21_decimal* x);
int s21_div_by_10(s21_decimal* dividend);
int s21_multiply_by_2(big_decimal *num);

// big_decimal functions:
int s21_fit_big_into_decimal(big_decimal* value, int* scale);
void s21_big_to_decimal(big_decimal* src, s21_decimal* dst);
void s21_decimal_to_big(s21_decimal src, big_decimal* dst);
int s21_big_div_by_10(big_decimal* value);
int s21_big_fits_decimal(const big_decimal* value);
int s21_big_sub(const big_decimal* a, const big_decimal* b, big_decimal* res);
int s21_big_compare(const big_decimal* a, const big_decimal* b);
int s21_big_shift_right(big_decimal* decimal, int n);
int s21_big_shift_left(big_decimal* decimal, int n);
int s21_big_fits_decimal(const big_decimal* v);
int s21_big_mul_by_10(big_decimal* x);
void s21_big_set_bits(big_decimal* decimal, int bit);
int s21_big_is_zero(big_decimal d);
int s21_big_div(big_decimal big_a, big_decimal big_b, big_decimal* big_res,
                int* new_scale);
int s21_big_from_int_to_decimal(int src, big_decimal* dst);

// Helpers:
int s21_normalize(s21_decimal* a, s21_decimal* b);
int s21_get_bits(big_decimal big_decimal, int bit);
void s21_clear_decimal(s21_decimal* res);
int s21_get_sign(s21_decimal decimal);
void s21_set_sign(s21_decimal* value, int sign);
int s21_get_scale(s21_decimal decimal);
void s21_set_scale(s21_decimal* decimal, int scale);
void s21_absolute_value(s21_decimal* decimal);
int s21_is_zero(s21_decimal d);
void s21_canonize_zero(s21_decimal* d);
int s21_count_digits(const big_decimal *num);
int s21_set_decimal_result(big_decimal *src, s21_decimal *dst, int scale,
                                  int sign);

#define SIGN 0x80000000U
#define SCALE 0x00ff0000

#define TOTAL_BITS 96
#define PRECISION 7

#endif