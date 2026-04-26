#include "./../s21_decimal.h"

// Проверяет, помещается ли big_decimal в 96-битную мантиссу decimal
int s21_big_fits_decimal(const big_decimal* value) {
  return value->bits[3] == 0 && value->bits[4] == 0 && value->bits[5] == 0 &&
         value->bits[6] == 0;
}