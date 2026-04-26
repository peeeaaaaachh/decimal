#include "./../s21_decimal.h"

// устанавливем или убираем знак числа
void s21_set_sign(s21_decimal* value, int sign) {
  if (sign) {
    value->bits[3] |= (1u << 31);
  } else {
    value->bits[3] &= ~(1u << 31);
  }
}