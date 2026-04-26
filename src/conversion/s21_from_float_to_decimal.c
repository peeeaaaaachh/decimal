#include "./../s21_decimal.h"

static int s21_multiply_by_10(big_decimal *num) {
  unsigned long long carry = 0;
  for (int i = 0; i < 7; i++) {  // обрабатываем все 7 элементов
    unsigned long long temp = (unsigned long long)num->bits[i] * 10ull + carry;
    num->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    carry = temp >> 32;
  }
  return (carry != 0)
             ? 1
             : 0;  // если перенос после 7 элементов — ошибка (не должно быть)
}

static void shift_right(big_decimal *num, int bits) {
  if (bits <= 0) return;
  unsigned int carry = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned long long val = ((unsigned long long)carry << 32) | num->bits[i];
    num->bits[i] = (unsigned int)(val >> bits);
    carry = (unsigned int)(val & ((1ULL << bits) - 1));
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  double max_dec = 79228162514264337593543950335.0;

  if (dst == S21_NULL) return 1;
  if (isinf(src) || isnan(src) || fabs((double)src) > max_dec) return 1;

  if (src == 0.0f) {
    s21_from_int_to_decimal(0, dst);

  } else if (fabs(src) > 0.0 && fabs(src) < 1e-28) {
    s21_from_int_to_decimal(0, dst);
    res = 1;
  } else {
    union {
      float float_bits;
      unsigned int int_bits;
    } converter;

    converter.float_bits = src;
    int src_sign = converter.int_bits >> 31 & 1;
    int src_exponent = converter.int_bits >> 23 & 0xff;
    unsigned int src_mantissa = converter.int_bits & 0x7fffff;

    if (src_exponent > 0 && src_exponent < 255) {
      int real_exponent = src_exponent - 127;
      unsigned int full_mantissa = (1U << 23) | src_mantissa;
      int shift = real_exponent - 23;

      big_decimal mantissa = {0};
      mantissa.bits[0] = full_mantissa;

      if (shift >= 0) {
        // Умножение на 2^shift
        for (int i = 0; i < shift && !res; i++) {
          if (s21_multiply_by_2(&mantissa)) {
            res = 1;
          }
        }

        if (!res) {
          s21_set_decimal_result(&mantissa, dst, 0, src_sign);
        }

      } else {
        int steps = -shift;

        for (int i = 0; i < steps && !res; i++) {
          if (s21_multiply_by_10(&mantissa)) {
            res = 1;
          }
        }

        if (!res) {
          // Компенсируем лишние множители 2: делим на 2^steps
          shift_right(&mantissa, steps);
          int scale = steps;

          if (scale > 28) {
            res = 1;
          } else {
            // Подсчитываем количество значащих цифр
            int digits = s21_count_digits(&mantissa);

            s21_bank_round(&mantissa, &scale, digits);

            if (scale > 28 || scale < 0) {
              res = 1;
            } else if (s21_set_decimal_result(&mantissa, dst, scale,
                                              src_sign)) {
              res = 1;
            }
          }
        }
      }
    }
  }

  return res;
}

// 0 — OK;
// 1 — ошибка конвертации.