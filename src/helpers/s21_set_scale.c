#include "./../s21_decimal.h"
// фнукиця чтобы поставить нужную ширину

void s21_set_scale(s21_decimal* decimal, int scale) {
  decimal->bits[3] &= ~SCALE;
  decimal->bits[3] |= (scale << 16) & SCALE;
}