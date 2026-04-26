#include "tests.h"

START_TEST(negative_zero_a_and_positive_zero_b) {
  // отрицательный 0 и положительный 0
  s21_decimal a = {.bits = {0, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_32_bit_a_equal_positive_32_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 0, 0, 0}};
  s21_decimal b = {.bits = {789, 0, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_32_bit_a_not_equal_positive_32_bit_b) {
  // a != b
  s21_decimal a = {.bits = {123, 0, 0, 0}};
  s21_decimal b = {.bits = {456, 0, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_32_bit_a_equal_negative_32_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 0, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_32_bit_a_not_equal_negative_32_bit_b) {
  // -a != -b
  s21_decimal a = {.bits = {654, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 0, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(positive_32_bit_a_not_equal_negative_32_bit_b) {
  // a != -b
  s21_decimal a = {.bits = {789, 0, 0, 0}};
  s21_decimal b = {.bits = {789, 0, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(positive_64_bit_a_equal_positive_64_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 984, 0, 0}};
  s21_decimal b = {.bits = {789, 984, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_64_bit_a_not_equal_positive_64_bit_b) {
  // a != b
  s21_decimal a = {.bits = {123, 25, 0, 0}};
  s21_decimal b = {.bits = {456, 64, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_64_bit_a_equal_negative_64_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 321, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 321, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_64_bit_a_not_equal_negative_64_bit_b) {
  // -a != -b
  s21_decimal a = {.bits = {654, 6475, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(positive_64_bit_a_not_equal_negative_64_bit_b) {
  // a != -b
  s21_decimal a = {.bits = {789, 984, 0, 0}};
  s21_decimal b = {.bits = {789, 984, 0, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(positive_96_bit_a_equal_positive_96_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 984, 150, 0}};
  s21_decimal b = {.bits = {789, 984, 150, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_96_bit_a_not_equal_positive_96_bit_b) {
  // a != b
  s21_decimal a = {.bits = {123, 25, 2, 0}};
  s21_decimal b = {.bits = {456, 64, 9, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_96_bit_a_equal_negative_96_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 321, 65, 0x80000000U}};
  s21_decimal b = {.bits = {456, 321, 65, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_96_bit_a_not_equal_negative_96_bit_b) {
  // -a != -b
  s21_decimal a = {.bits = {654, 6475, 87654, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 12345, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(positive_96_bit_a_not_equal_negative_96_bit_b) {
  // a != -b
  s21_decimal a = {.bits = {789, 984, 150, 0}};
  s21_decimal b = {.bits = {789, 984, 150, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(equal_with_scale_same_number) {
  // 1.23 vs 1.23 (одинаковый масштаб)
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {123, 0, 0, 2 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_with_different_scale_same_value) {
  // 1.23 vs 1.230 (разный масштаб, но одинаковое значение)
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16}};   // 1.23
  s21_decimal b = {.bits = {1230, 0, 0, 3 << 16}};  // 1.230

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_with_different_scale_different_value) {
  // 1.23 vs 1.24 (разный масштаб, разные значения)
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {124, 0, 0, 2 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(equal_with_scale_edge) {
  // 1.00 vs 1 (scale 2 vs scale 0)
  s21_decimal a = {.bits = {100, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {1, 0, 0, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_with_scale_edge_reverse) {
  // 1 vs 1.00 (scale 0 vs scale 2)
  s21_decimal a = {.bits = {1, 0, 0, 0}};
  s21_decimal b = {.bits = {100, 0, 0, 2 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_max_decimal_vs_max_decimal) {
  // Максимальное decimal число
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_max_decimal_vs_max_minus_one) {
  // Максимальное decimal число vs максимальное минус 1
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(equal_min_decimal_vs_min_decimal) {
  // Минимальное decimal (максимальное отрицательное)
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};
  s21_decimal b = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_min_decimal_vs_min_plus_one) {
  // Минимальное decimal vs минимальное плюс 1
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};
  s21_decimal b = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(equal_zero_with_different_scales) {
  // 0.00 vs 0.000
  s21_decimal a = {.bits = {0, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {0, 0, 0, 3 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_zero_with_different_scales_and_sign) {
  // -0.00 vs +0.000
  s21_decimal a = {.bits = {0, 0, 0, 2 << 16 | 0x80000000U}};
  s21_decimal b = {.bits = {0, 0, 0, 3 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_numbers_need_normalization) {
  // Числа, которые требуют приведения к общему масштабу
  s21_decimal a = {.bits = {1, 0, 0, 0}};
  s21_decimal b = {.bits = {1000, 0, 0, 3 << 16}};  // 1.000

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_negative_with_scale_same) {
  // -1.23 vs -1.23
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16 | 0x80000000U}};
  s21_decimal b = {.bits = {123, 0, 0, 2 << 16 | 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_negative_with_different_scale_same_value) {
  // -1.23 vs -1.230
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16 | 0x80000000U}};
  s21_decimal b = {.bits = {1230, 0, 0, 3 << 16 | 0x80000000U}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_normalization_overflow) {
  // Число, которое при нормализации может переполниться
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};
  s21_decimal b = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(equal_max_with_scale_vs_max) {
  // Максимальное число с масштабом 1 vs максимальное без масштаба
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 16}};
  s21_decimal b = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(equal_different_bits_same_value) {
  // Разные битовые представления одного числа
  s21_decimal a = {.bits = {12345, 0, 0, 0}};
  s21_decimal b = {.bits = {123450, 0, 0, 1 << 16}};

  int result = s21_is_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite* s21_is_equal_suite() {
  Suite* s = suite_create("s21_is_equal");

  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, negative_zero_a_and_positive_zero_b);

  // 32-bit тесты
  tcase_add_test(tc, positive_32_bit_a_equal_positive_32_bit_b);
  tcase_add_test(tc, positive_32_bit_a_not_equal_positive_32_bit_b);
  tcase_add_test(tc, negative_32_bit_a_equal_negative_32_bit_b);
  tcase_add_test(tc, negative_32_bit_a_not_equal_negative_32_bit_b);
  tcase_add_test(tc, positive_32_bit_a_not_equal_negative_32_bit_b);

  // 64-bit тесты
  tcase_add_test(tc, positive_64_bit_a_equal_positive_64_bit_b);
  tcase_add_test(tc, positive_64_bit_a_not_equal_positive_64_bit_b);
  tcase_add_test(tc, negative_64_bit_a_equal_negative_64_bit_b);
  tcase_add_test(tc, negative_64_bit_a_not_equal_negative_64_bit_b);
  tcase_add_test(tc, positive_64_bit_a_not_equal_negative_64_bit_b);

  // 96-bit тесты
  tcase_add_test(tc, positive_96_bit_a_equal_positive_96_bit_b);
  tcase_add_test(tc, positive_96_bit_a_not_equal_positive_96_bit_b);
  tcase_add_test(tc, negative_96_bit_a_equal_negative_96_bit_b);
  tcase_add_test(tc, negative_96_bit_a_not_equal_negative_96_bit_b);
  tcase_add_test(tc, positive_96_bit_a_not_equal_negative_96_bit_b);

  // Тесты с масштабом
  tcase_add_test(tc, equal_with_scale_same_number);
  tcase_add_test(tc, equal_with_different_scale_same_value);
  tcase_add_test(tc, equal_with_different_scale_different_value);
  tcase_add_test(tc, equal_with_scale_edge);
  tcase_add_test(tc, equal_with_scale_edge_reverse);

  // Граничные значения
  tcase_add_test(tc, equal_max_decimal_vs_max_decimal);
  tcase_add_test(tc, equal_max_decimal_vs_max_minus_one);
  tcase_add_test(tc, equal_min_decimal_vs_min_decimal);
  tcase_add_test(tc, equal_min_decimal_vs_min_plus_one);

  // Ноль с разными масштабами и знаками
  tcase_add_test(tc, equal_zero_with_different_scales);
  tcase_add_test(tc, equal_zero_with_different_scales_and_sign);

  // Нормализация
  tcase_add_test(tc, equal_numbers_need_normalization);

  // Отрицательные с масштабом
  tcase_add_test(tc, equal_negative_with_scale_same);
  tcase_add_test(tc, equal_negative_with_different_scale_same_value);

  // Переполнение и граничные случаи
  tcase_add_test(tc, equal_normalization_overflow);
  tcase_add_test(tc, equal_max_with_scale_vs_max);
  tcase_add_test(tc, equal_different_bits_same_value);

  suite_add_tcase(s, tc);

  return s;
}