#include "./../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int res = (dst == S21_NULL) ? 1 : 0;
  int sign = s21_get_sign(src);
  int scale = s21_get_scale(src);

  if (scale >= 0 && scale <= 28 && !res) {
    s21_decimal truncated_mantissa;
    s21_truncate(src, &truncated_mantissa);

    if (truncated_mantissa.bits[1] == 0 && truncated_mantissa.bits[2] == 0) {
      if (((unsigned int)truncated_mantissa.bits[0] <= INT_MAX && !sign) ||
          ((unsigned int)truncated_mantissa.bits[0] <=
               (unsigned int)INT_MAX + 1 &&
           sign)) {
        *dst = sign ? -(int)truncated_mantissa.bits[0]
                    : (int)truncated_mantissa.bits[0];
      } else {
        res = 1;
      }

    } else {
      res = 1;
    }
  } else {
    res = 1;
  }

  return res;
}