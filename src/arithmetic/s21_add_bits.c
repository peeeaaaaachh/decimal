#include "./../s21_decimal.h"

// складываем мантисы двух decimal чисел с учетом переноса разряда
int s21_add_bits(big_decimal* a, big_decimal* b, big_decimal* result) {
  uint64_t carry = 0;

  for (int i = 0; i < 6; i++) {
    uint64_t sum = (uint64_t)a->bits[i] + (uint64_t)b->bits[i] + carry;

    result->bits[i] = (uint32_t)sum;

    carry = sum >> 32;
  }

  return (int)carry;
}