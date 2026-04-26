#include "./../s21_decimal.h"

// Базовое сравнение с учетом знака
int s21_base_compare(s21_decimal a, s21_decimal b) {
  int result = 0;

  if (s21_normalize(&a, &b) == 0) {
    int a_sign = s21_get_sign(a);
    int b_sign = s21_get_sign(b);

    if (a_sign != b_sign) {
      result = (a_sign == 1 && b_sign == 0)   ? -1
               : (a_sign == 0 && b_sign == 1) ? 1
                                              : 0;
    } else {
      result = s21_compare_mantissa(a, b);
      result *= a_sign ? -1 : 1;
    }
  } else {
    int scale_a = s21_get_scale(a);
    int scale_b = s21_get_scale(b);
    int scale_diff =
        (scale_a > scale_b) ? scale_a - scale_b : scale_b - scale_a;
    s21_decimal tmp = scale_a > scale_b ? a : b;

    int has_remainder = 0;

    while (scale_diff--) {
      if (s21_div_by_10(&tmp) != 0) {
        has_remainder = 1;
      }
    }

    if (scale_a > scale_b) {
      int tmp_res = s21_compare_mantissa(tmp, b);
      if (tmp_res != 0) {
        result = tmp_res;
      } else {
        result = has_remainder ? 1 : 0;
      }
    } else {
      int tmp_res = s21_compare_mantissa(tmp, a);
      if (tmp_res != 0) {
        result = -tmp_res;
      } else {
        result = has_remainder ? -1 : 0;
      }
    }
  }
  return result;
}

// Возвращаемое значение:
// -1 если a  < b
//  0 если a == b
//  1 если a  > b