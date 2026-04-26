#include "./../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;

  if (dst == S21_NULL) {
    res = 1;
  } else {
    int sign = s21_get_sign(src);
    int scale = s21_get_scale(src);

    double tmp = (double)src.bits[0];
    tmp += ldexp((double)src.bits[1], 32);
    tmp += ldexp((double)src.bits[2], 64);

    for (int i = 0; i < scale; i++) {
      tmp /= 10;
    }

    if (tmp > 0.0 && tmp < 1e-28) {
      res = 1;
      *dst = 0.0f;
    } else {
      tmp *= sign ? -1 : 1;
      *dst = (float)tmp;
    }
  }
  return res;
}
