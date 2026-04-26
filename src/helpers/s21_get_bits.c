#include "./../s21_decimal.h"
// функция для получения нужного бита

int s21_get_bits(big_decimal big_decimal, int bit) {
  int index = bit / 32;
  int mask = 1 << (bit % 32);
  return (big_decimal.bits[index] & mask) ? 1 : 0;
}