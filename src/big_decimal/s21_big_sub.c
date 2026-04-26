#include "./../s21_decimal.h"

int s21_big_sub(const big_decimal* a, const big_decimal* b, big_decimal* res);

// Вычитает мантиссу b из a (a >= b) с учётом займа
int s21_big_sub(const big_decimal* a, const big_decimal* b, big_decimal* res) {
  uint64_t borrow = 0;

  for (int i = 0; i < 7; i++) {
    uint64_t av = (uint64_t)a->bits[i];
    uint64_t bv = (uint64_t)b->bits[i] + borrow;

    if (av >= bv) {
      res->bits[i] = (uint32_t)(av - bv);
      borrow = 0;
    } else {
      res->bits[i] = (uint32_t)((((uint64_t)1 << 32) + av) - bv);
      borrow = 1;
    }
  }

  return (int)borrow;
}