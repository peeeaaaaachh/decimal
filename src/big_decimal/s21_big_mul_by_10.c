#include "./../s21_decimal.h"

int s21_big_mul_by_10(big_decimal* x) {
  // умножение мантисы на 10
  unsigned long long carry = 0;

  for (int i = 0; i < 6; i++) {
    unsigned long long sum = (unsigned long long)x->bits[i] * 10ull + carry;
    x->bits[i] = (unsigned int)sum;
    carry = sum >> 32;
  }
  return (carry > 0) ? 1 : 0;
}