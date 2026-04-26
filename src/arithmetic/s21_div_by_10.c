#include "./../s21_decimal.h"

// Деление мантиссы на 10
int s21_div_by_10(s21_decimal* dividend) {
  int remainder = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long big_int =
        ((unsigned long long)remainder << 32) | dividend->bits[i];
    dividend->bits[i] = (unsigned int)(big_int / 10);
    remainder = (unsigned int)(big_int % 10);
  }
  return remainder;
}