#include "./../s21_decimal.h"
// функция для получения ширины числа

int s21_get_scale(s21_decimal decimal) {
  int scale = (decimal.bits[3] & SCALE) >> 16;
  return scale;
}