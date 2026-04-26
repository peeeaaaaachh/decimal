#include "./../s21_decimal.h"

// проверяем что все 96 бит равны нулю
int s21_is_zero(s21_decimal d) { return !(d.bits[0] | d.bits[1] | d.bits[2]); }