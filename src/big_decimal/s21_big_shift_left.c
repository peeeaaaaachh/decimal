#include "./../s21_decimal.h"
// функция для сдвига влево на n-ое количество битов

int s21_big_shift_left(big_decimal* decimal, int n) {
  int i = 0;
  int flag = 0;

  if (n >= 224 || n < 0) {
    flag = 1;
  }

  while (i < n && flag == 0) {
    int bit = 0;
    for (int j = 0; j < 6; j++) {
      if (decimal->bits[5] & SIGN) {
        flag = 1;
      }
      int new_bit = (decimal->bits[j] & SIGN) ? 1 : 0;
      decimal->bits[j] = decimal->bits[j] << 1;
      decimal->bits[j] |= bit;
      bit = new_bit;
    }

    i++;
  }

  return flag;
}