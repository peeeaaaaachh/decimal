#include "./../s21_decimal.h"

void s21_clear_decimal(s21_decimal* res) {
  for (int i = 0; i < 4; i++) res->bits[i] = 0;
}