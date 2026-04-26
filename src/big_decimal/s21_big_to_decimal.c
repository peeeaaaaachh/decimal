#include "./../s21_decimal.h"

void s21_big_to_decimal(big_decimal* src, s21_decimal* dst) {
  s21_clear_decimal(dst);
  dst->bits[0] = src->bits[0];
  dst->bits[1] = src->bits[1];
  dst->bits[2] = src->bits[2];
}