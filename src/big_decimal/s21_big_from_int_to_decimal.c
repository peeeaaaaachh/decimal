#include "./../s21_decimal.h"

int s21_big_from_int_to_decimal(int src, big_decimal* dst) {
  int res = 0;

  if (dst) {
    if (src == INT_MIN) {
      dst->bits[0] = 0x80000000U;
    } else {
      dst->bits[0] = (src < 0) ? -src : src;
    }

    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    dst->bits[4] = 0;
    dst->bits[5] = 0;
    dst->bits[6] = (src < 0) ? 0x80000000U : 0;

  } else {
    res = 1;
  }

  return res;
}