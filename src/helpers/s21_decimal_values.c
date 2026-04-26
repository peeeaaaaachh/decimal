#include "./../s21_decimal.h"

s21_decimal s21_decimal_get_zero(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  return result;
}

s21_decimal s21_decimal_get_one(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  result.bits[0] = 1;
  return result;
}

s21_decimal s21_decimal_get_05(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  result.bits[0] = 5;
  s21_set_scale(&result, 1);
  return result;
}