#include "./../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  int res = (result == S21_NULL) ? 1 : 0;

  if (!res) {
    *result = value;
    result->bits[3] ^= 0x80000000U;
  }

  return res;
}