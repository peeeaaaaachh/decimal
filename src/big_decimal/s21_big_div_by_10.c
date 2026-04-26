#include "./../s21_decimal.h"

// Делит big_decimal на 10, изменяя число и возвращая остаток деления
int s21_big_div_by_10(big_decimal* value) {
  uint64_t remainder = 0;

  for (int i = 6; i >= 0; i--) {
    uint64_t current = (remainder << 32) | value->bits[i];

    value->bits[i] = (uint32_t)(current / 10);
    remainder = current % 10;
  }

  return (int)remainder;
}