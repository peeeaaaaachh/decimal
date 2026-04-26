#include "./../s21_decimal.h"

// функция для того чтобы поставить нужный бит
void s21_big_set_bits(big_decimal* decimal, int bit) {
  int index = bit / 32;
  int mask = 1 << (bit % 32);
  decimal->bits[index] |= mask;
}
