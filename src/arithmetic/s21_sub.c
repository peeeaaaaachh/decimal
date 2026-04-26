#include "./../s21_decimal.h"

// выполняет вычитание через сложение, меняя знак второго числа

int s21_sub(s21_decimal a, s21_decimal b, s21_decimal* result) {
  if (!result) return 1;

  s21_decimal neg_b = b;

  s21_set_sign(&neg_b, !s21_get_sign(neg_b));

  return s21_add(a, neg_b, result);
}