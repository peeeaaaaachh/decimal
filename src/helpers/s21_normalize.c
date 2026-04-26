#include "./../s21_decimal.h"

// функция нормализации числа
int s21_normalize(s21_decimal* a, s21_decimal* b) {
  s21_canonize_zero(a);
  s21_canonize_zero(b);

  int status = 0;

  int scale_a = s21_get_scale(*a);
  int scale_b = s21_get_scale(*b);

  while (!status && scale_a < scale_b) {
    status = s21_mul_by_10(a);
    if (!status) {
      scale_a++;
    }
  }

  while (!status && scale_b < scale_a) {
    status = s21_mul_by_10(b);
    if (!status) {
      scale_b++;
    }
  }

  if (!status) {
    s21_set_scale(a, scale_a);
    s21_set_scale(b, scale_b);
  }

  return status;
}