#include "./../s21_decimal.h"

// Приводит big_decimal к формату decimal:
// уменьшает scale делением на 10, выполняет banker’s rounding
// и возвращает статус переполнения.
int s21_fit_big_into_decimal(big_decimal* value, int* scale) {
  int status = 0;
  int remainder = 0;
  int sticky = 0;

  while (*scale > 28) {
    remainder = s21_big_div_by_10(value);
    if (remainder != 0) sticky = 1;
    (*scale)--;
  }

  // Пока число не помещается в decimal, уменьшаем scale
  while (!s21_big_fits_decimal(value) && *scale > 0) {
    int current_remainder = s21_big_div_by_10(value);
    if (current_remainder != 0) sticky = 1;
    remainder = current_remainder;
    (*scale)--;
  }

  // Если всё равно не помещается — overflow
  if (!s21_big_fits_decimal(value)) {
    status = 1;
  } else {
    // banker’s rounding
    int need_round = 0;

    if (remainder > 5) {
      need_round = 1;
    } else if (remainder == 5) {
      if (sticky || (value->bits[0] & 1)) {
        need_round = 1;
      }
    }

    if (need_round) {
      big_decimal one = {0};
      one.bits[0] = 1;
      s21_add_bits(value, &one, value);

      // если после округления снова не помещается
      if (!s21_big_fits_decimal(value)) {
        if (*scale > 0) {
          s21_big_div_by_10(value);
          (*scale)--;
        }
        if (!s21_big_fits_decimal(value)) {
          status = 1;
        }
      }
    }
  }

  return status;
}