#include "./../s21_decimal.h"

int s21_add(s21_decimal a, s21_decimal b, s21_decimal* result) {
  int status = 0;

  if (!result) return 1;

  s21_clear_decimal(result);

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  status = s21_normalize(&a, &b);
  int scale = s21_get_scale(a);

  if (!status) {
    big_decimal A = {0};
    big_decimal B = {0};
    big_decimal R = {0};

    s21_decimal_to_big(a, &A);
    s21_decimal_to_big(b, &B);

    int result_sign = 0;

    if (sign_a == sign_b) {
      s21_add_bits(&A, &B, &R);
      result_sign = sign_a;
    } else {
      int cmp = s21_big_compare(&A, &B);

      if (cmp >= 0) {
        s21_big_sub(&A, &B, &R);
        result_sign = sign_a;
      } else {
        s21_big_sub(&B, &A, &R);
        result_sign = sign_b;
      }
    }

    status = s21_fit_big_into_decimal(&R, &scale);

    if (status) {
      status = result_sign ? 2 : 1;
    } else {
      s21_big_to_decimal(&R, result);
      s21_set_scale(result, scale);
      s21_set_sign(result, result_sign);
      s21_canonize_zero(result);
    }
  }

  return status;
}