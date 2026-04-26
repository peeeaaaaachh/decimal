#include "./../s21_decimal.h"

// приводим ноль к кононичной форме "-0.0000  -  0"
void s21_canonize_zero(s21_decimal* d) {
  if (s21_is_zero(*d)) {
    s21_set_scale(d, 0);
    s21_set_sign(d, 0);
  }
}