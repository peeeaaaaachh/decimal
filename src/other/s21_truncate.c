#include "./../s21_decimal.h"

// Отбрасывание дробной части
int s21_truncate(s21_decimal value, s21_decimal* result) {
  int res = 0;
  int scale = s21_get_scale(value);

  if (scale > 28 || scale < 0 || result == S21_NULL) {
    res = 1;
  } else if (scale == 0) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3];
  } else {
    s21_decimal tmp = value;

    while (scale--) {
      s21_div_by_10(&tmp);
    }

    int sign = s21_get_sign(value);

    result->bits[0] = tmp.bits[0];
    result->bits[1] = tmp.bits[1];
    result->bits[2] = tmp.bits[2];
    result->bits[3] = sign ? 0x80000000U : 0;
  }
  return res;
}