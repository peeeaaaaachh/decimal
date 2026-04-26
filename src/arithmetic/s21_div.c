#include "./../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);

  s21_decimal a = value_1;
  s21_decimal b = value_2;
  s21_absolute_value(&a);
  s21_absolute_value(&b);

  big_decimal big_a = {0};
  big_decimal big_b = {0};
  big_decimal big_res = {0};

  int flag = 0;
  s21_clear_decimal(result);
  int new_scale = scale1 - scale2;
  s21_decimal_to_big(a, &big_a);
  s21_decimal_to_big(b, &big_b);
  if (new_scale < 0) {
    for (int i = 0; i < -new_scale; i++) {
      s21_big_mul_by_10(&big_a);
    }
    new_scale = 0;
  }
  if (s21_is_zero(value_2)) {
    flag = 3;
  }

  if (!flag) {
    s21_big_div(big_a, big_b, &big_res, &new_scale);
  }

  if (s21_fit_big_into_decimal(&big_res, &new_scale)) {
    return 1;
  }

  s21_big_to_decimal(&big_res, result);
  s21_set_sign(result, sign1 ^ sign2);
  s21_set_scale(result, new_scale);
  return flag;
}

// работа с big decimal
int s21_big_div(big_decimal big_a, big_decimal big_b, big_decimal* big_res,
                int* new_scale) {
  big_decimal big_tmp_res = {0};
  big_decimal big_tmp_int_b = big_b;
  //  для целой части (побитово)
  if (s21_big_compare(&big_a, &big_tmp_int_b) >= 0) {
    int shift = 0;
    while (s21_big_compare(&big_a, &big_tmp_int_b) >= 0) {
      s21_big_shift_left(&big_tmp_int_b, 1);
      shift++;
    }
    s21_big_shift_right(&big_tmp_int_b, 1);
    shift--;

    for (; shift >= 0; shift--) {
      if (s21_big_compare(&big_a, &big_tmp_int_b) >= 0) {
        s21_big_sub(&big_a, &big_tmp_int_b, &big_a);
        s21_big_set_bits(&big_tmp_res, shift);
      }
      s21_big_shift_right(&big_tmp_int_b, 1);
    }
  }

  // для дробной части (десятичные числа)
  big_decimal big_digit_dec = {0};
  while (!s21_big_is_zero(big_a) && *new_scale < 29) {
    s21_big_mul_by_10(&big_a);
    (*new_scale)++;
    int big_digit = 0;
    while (s21_big_compare(&big_a, &big_b) >= 0) {
      s21_big_sub(&big_a, &big_b, &big_a);
      big_digit++;
    }
    s21_big_mul_by_10(&big_tmp_res);
    s21_big_from_int_to_decimal(big_digit, &big_digit_dec);
    s21_add_bits(&big_tmp_res, &big_digit_dec, &big_tmp_res);
  }

  *big_res = big_tmp_res;

  return 0;
}
