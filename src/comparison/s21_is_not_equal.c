#include "./../s21_decimal.h"

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return (s21_base_compare(a, b) != 0) ? 1 : 0;
}

// Возвращаемое значение:
// 0 если a == b
// 1 если a != b