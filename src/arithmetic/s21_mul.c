#include "./../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (!result) return 1;

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

  // очистка битов с sign/scale
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;

  big_decimal a = {0};
  big_decimal b = {0};

  s21_decimal_to_big(value_1, &a);
  s21_decimal_to_big(value_2, &b);

  big_decimal mul_result = {0};
  /*if (mul_bits(a, b, &mul_result))
    return 1;*/
  mul_bits(a, b, &mul_result);

  // подготовка результата
  if (s21_fit_big_into_decimal(&mul_result, &scale)) return 1;
  s21_big_to_decimal(&mul_result, result);
  s21_set_sign(result, sign1 ^ sign2);
  s21_set_scale(result, scale);

  return 0;
}

int mul_bits(big_decimal a, big_decimal b, big_decimal* result) {
  big_decimal res = {0};

  for (int i = 0; i < 224; i++) {
    if (s21_get_bits(b, i)) {
      big_decimal temp = a;
      s21_big_shift_left(&temp, i);
      s21_add_bits(&res, &temp, &res);
      /*if (s21_add_bits(&res, &temp, &res))
        return 1;*/
    }
  }
  *result = res;
  return 0;
}