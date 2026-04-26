#include "./../s21_decimal.h"

void s21_decimal_to_big(s21_decimal src, big_decimal* dst) {
  for (int i = 0; i < 7; i++) {
    dst->bits[i] = 0;
  }

  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
}