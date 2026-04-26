#include "./../s21_decimal.h"
// функция для того чтобы узнать положительное или отриц число

int s21_get_sign(s21_decimal decimal) {
  return (decimal.bits[3] & SIGN) ? 1 : 0;
}