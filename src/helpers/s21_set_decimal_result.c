#include "./../s21_decimal.h"

int s21_set_decimal_result(big_decimal *src, s21_decimal *dst, int scale,
                           int sign) {
  // Проверяем, что число помещается в 96 бит
  int res = 0;
  for (int i = 3; i < 7; i++) {
    if (src->bits[i] != 0) {
      res = 1;
    }
  }
  if (!res) {
    dst->bits[0] = src->bits[0];
    dst->bits[1] = src->bits[1];
    dst->bits[2] = src->bits[2];
    s21_set_scale(dst, scale);
    s21_set_sign(dst, sign);
  }
  return res;
}