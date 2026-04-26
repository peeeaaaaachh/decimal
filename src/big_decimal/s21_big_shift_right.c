#include "./../s21_decimal.h"
// функция для сдвига вправо на n-ое количество битов

int s21_big_shift_right(big_decimal* decimal, int n) {
  int i = 0;
  int flag = 0;
  if (n >= 224 || n < 0) {
    flag = 1;
  }
  while (i < n && flag == 0) {
    int bit = 0;
    for (int j = 6; j >= 0; j--) {
      int new_bit = decimal->bits[j] & 1;
      decimal->bits[j] = decimal->bits[j] >> 1;
      decimal->bits[j] |= ((unsigned int)bit << 31);
      bit = new_bit;
    }
    i++;
  }
  return flag;
}