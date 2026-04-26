#include "./../s21_decimal.h"

int s21_multiply_by_2(big_decimal *num) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long temp = (unsigned long long)num->bits[i] * 2ull + carry;
    num->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    carry = temp >> 32;
  }
  return (carry != 0) ? 1 : 0;
}