#include "./../s21_decimal.h"

void s21_absolute_value(s21_decimal* decimal) { decimal->bits[3] &= ~SIGN; }