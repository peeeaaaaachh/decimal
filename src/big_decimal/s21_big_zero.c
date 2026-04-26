#include "./../s21_decimal.h"
// проверяем что все 224 бит равны нулю
int s21_big_is_zero(big_decimal d) {
  return !(d.bits[0] | d.bits[1] | d.bits[2] | d.bits[3] | d.bits[4] |
           d.bits[5] | d.bits[6]);
}