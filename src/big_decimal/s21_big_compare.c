#include "./../s21_decimal.h"

int s21_big_compare(const big_decimal* a, const big_decimal* b) {
  int result = 0;

  for (int i = 6; i >= 0 && result == 0; i--) {
    result = (a->bits[i] > b->bits[i]) - (a->bits[i] < b->bits[i]);
  }

  return result;
}