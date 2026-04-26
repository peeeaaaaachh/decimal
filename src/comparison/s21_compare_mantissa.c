#include "./../s21_decimal.h"

// Сравнения мантиссы без учета знака
int s21_compare_mantissa(s21_decimal a, s21_decimal b) {
  int result = 0;

  int num_size = 3;
  while (result == 0 && num_size-- != 0) {
    result = (a.bits[num_size] < b.bits[num_size])    ? -1
             : (a.bits[num_size] == b.bits[num_size]) ? 0
                                                      : 1;
  }
  return result;
}