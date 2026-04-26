#include "./../s21_decimal.h"

// Округляет Decimal до ближайшего целого числа

int s21_round(s21_decimal value, s21_decimal* result) {
  if (!result) return 1;
  int sign = s21_get_sign(value);
  int scale = s21_get_scale(value);

  // если число уже целое
  if (scale == 0) {
    *result = value;
    return 0;
  }

  s21_decimal value_truncated;
  s21_decimal value_frac;
  s21_decimal abs_value = value;

  // получаем модуль числа
  s21_absolute_value(&abs_value);
  // получаем число без дроби
  s21_truncate(abs_value, &value_truncated);
  // получаем дробyню часть
  s21_sub(abs_value, value_truncated, &value_frac);

  // округляю в большую сторону если дробная часть >=5
  if (s21_is_greater_or_equal(value_frac, s21_decimal_get_05())) {
    s21_add(value_truncated, s21_decimal_get_one(), &value_truncated);
  }

  *result = value_truncated;
  s21_set_sign(result, sign);
  s21_set_scale(result, 0);

  if (s21_is_zero(*result)) {
    s21_set_sign(result, 0);
    s21_set_scale(result, 0);
  }
  return 0;
}