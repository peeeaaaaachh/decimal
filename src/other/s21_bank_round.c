#include "../s21_decimal.h"

void s21_bank_round(big_decimal *mantissa, int *scale, int digits) {
  if (digits <= PRECISION) return;

  int extra = digits - PRECISION;
  unsigned int last_remainder = 0;
  big_decimal temp = *mantissa;

  for (int i = 0; i < extra; i++) {
    last_remainder = s21_big_div_by_10(&temp);
  }

  unsigned int last_digit = temp.bits[0] % 10;

  int round_up = 0;

  if (last_remainder > 5) {
    round_up = 1;
  } else if (last_remainder == 5) {
    // Банковское округление: если последняя цифра нечётная, округляем вверх
    if (last_digit % 2 != 0) {
      round_up = 1;
    }
  }

  if (round_up) {
    // Увеличиваем temp на 1
    unsigned long long carry = 1;
    for (int i = 0; i < 3 && carry > 0; i++) {
      unsigned long long sum = (unsigned long long)temp.bits[i] + carry;
      temp.bits[i] = (unsigned int)(sum & 0xFFFFFFFF);
      carry = sum >> 32;
    }

    if (carry > 0) {
      // Переполнение при округлении — число стало на 1 разряд больше
      *scale += 1;
      s21_big_div_by_10(&temp);
    }
  }

  // Записываем округлённое значение обратно в mantissa
  mantissa->bits[0] = temp.bits[0];
  mantissa->bits[1] = temp.bits[1];
  mantissa->bits[2] = temp.bits[2];

  // Уменьшаем scale на extra
  *scale -= extra;
}