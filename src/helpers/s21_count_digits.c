#include "../s21_decimal.h"

int s21_count_digits(const big_decimal *num) {
  int count = 0;
  big_decimal temp = *num;

  do {
    s21_big_div_by_10(&temp);
    count++;
  } while (!(temp.bits[0] == 0 && temp.bits[1] == 0 && temp.bits[2] == 0));

  return count;
}