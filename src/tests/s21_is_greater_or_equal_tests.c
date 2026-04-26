#include "tests.h"

START_TEST(negative_zero_a_and_positive_zero_b) {
  // отрицательный 0 и положительный 0
  s21_decimal a = {.bits = {0, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_32_bit_a_is_greater_or_equal_then_positive_32_bit_b) {
  // a > b
  s21_decimal a = {.bits = {456, 0, 0, 0}};
  s21_decimal b = {.bits = {123, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_32_bit_b_is_greater_or_equal_then_positive_32_bit_a) {
  // a < b
  s21_decimal a = {.bits = {456, 0, 0, 0}};
  s21_decimal b = {.bits = {789, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_32_bit_a_is_greater_or_equal_then_positive_32_bit_b) {
  // -a >= b? Нет, отрицательное всегда меньше положительного
  s21_decimal a = {.bits = {1230, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_32_bit_b_is_greater_or_equal_then_positive_32_bit_a) {
  // a >= -b? Да, положительное всегда больше отрицательного
  s21_decimal a = {.bits = {789, 0, 0, 0}};
  s21_decimal b = {.bits = {4560, 0, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_32_bit_a_is_greater_or_equal_then_negative_32_bit_b) {
  // -a >= -b? -654 >= -235? Нет, -654 меньше
  s21_decimal a = {.bits = {654, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 0, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_32_bit_b_is_greater_or_equal_then_negative_32_bit_a) {
  // -b >= -a? -235 >= -654? Да
  s21_decimal a = {.bits = {654, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 0, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(b, a);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_32_bit_a_equal_positive_32_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 0, 0, 0}};
  s21_decimal b = {.bits = {789, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_32_bit_a_equal_negative_32_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 0, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 0, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_64_bit_a_is_greater_or_equal_then_positive_64_bit_b) {
  // a > b
  s21_decimal a = {.bits = {456, 64, 0, 0}};
  s21_decimal b = {.bits = {123, 25, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_64_bit_b_is_greater_or_equal_then_positive_64_bit_a) {
  // a < b
  s21_decimal a = {.bits = {456, 987, 0, 0}};
  s21_decimal b = {.bits = {789, 1245, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_64_bit_a_is_greater_or_equal_then_positive_64_bit_b) {
  // -a >= b? Нет
  s21_decimal a = {.bits = {1230, 789, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 95, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_64_bit_b_is_greater_or_equal_then_positive_64_bit_a) {
  // a >= -b? Да
  s21_decimal a = {.bits = {789, 18, 0, 0}};
  s21_decimal b = {.bits = {4560, 324, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_64_bit_a_is_greater_or_equal_then_negative_64_bit_b) {
  // -a >= -b? -654 >= -235? Нет
  s21_decimal a = {.bits = {654, 6475, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_64_bit_b_is_greater_or_equal_then_negative_64_bit_a) {
  // -b >= -a? -235 >= -654? Да
  s21_decimal a = {.bits = {654, 6475, 0, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(b, a);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_64_bit_a_equal_positive_64_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 984, 0, 0}};
  s21_decimal b = {.bits = {789, 984, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_64_bit_a_equal_negative_64_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 321, 0, 0x80000000U}};
  s21_decimal b = {.bits = {456, 321, 0, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_96_bit_a_is_greater_or_equal_then_positive_96_bit_b) {
  // a > b
  s21_decimal a = {.bits = {456, 64, 9, 0}};
  s21_decimal b = {.bits = {123, 25, 2, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_96_bit_b_is_greater_or_equal_then_positive_96_bit_a) {
  // a < b
  s21_decimal a = {.bits = {456, 987, 15, 0}};
  s21_decimal b = {.bits = {789, 1245, 87, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_96_bit_a_is_greater_or_equal_then_positive_96_bit_b) {
  // -a >= b? Нет
  s21_decimal a = {.bits = {1230, 789, 25, 0x80000000U}};
  s21_decimal b = {.bits = {456, 95, 3, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_96_bit_b_is_greater_or_equal_then_positive_96_bit_a) {
  // a >= -b? Да
  s21_decimal a = {.bits = {789, 18, 8, 0}};
  s21_decimal b = {.bits = {4560, 324, 12, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_96_bit_a_is_greater_or_equal_then_negative_96_bit_b) {
  // -a >= -b? -654 >= -235? Нет
  s21_decimal a = {.bits = {654, 6475, 87654, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 12345, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST;

START_TEST(negative_96_bit_b_is_greater_or_equal_then_negative_96_bit_a) {
  // -b >= -a? -235 >= -654? Да
  s21_decimal a = {.bits = {654, 6475, 87654, 0x80000000U}};
  s21_decimal b = {.bits = {235, 5178, 12345, 0x80000000U}};

  int result = s21_is_greater_or_equal(b, a);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(positive_96_bit_a_equal_positive_96_bit_b) {
  // a == b
  s21_decimal a = {.bits = {789, 984, 150, 0}};
  s21_decimal b = {.bits = {789, 984, 150, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(negative_96_bit_a_equal_negative_96_bit_b) {
  // -a == -b
  s21_decimal a = {.bits = {456, 321, 65, 0x80000000U}};
  s21_decimal b = {.bits = {456, 321, 65, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST;

START_TEST(greater_or_equal_with_scale_same_number) {
  // 1.25 vs 1.23 (одинаковый масштаб)
  s21_decimal a = {.bits = {125, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {123, 0, 0, 2 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_with_different_scale) {
  // 1.2 vs 1.23 (разный масштаб)
  s21_decimal a = {.bits = {12, 0, 0, 1 << 16}};
  s21_decimal b = {.bits = {123, 0, 0, 2 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(greater_or_equal_with_scale_edge) {
  // 1 vs 1.00 (scale 0 vs scale 2)
  s21_decimal a = {.bits = {1, 0, 0, 0}};
  s21_decimal b = {.bits = {100, 0, 0, 2 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_max_decimal_vs_max_minus_one) {
  // Максимальное decimal число
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_min_decimal_vs_min_plus_one) {
  // Минимальное decimal (максимальное отрицательное)
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};
  s21_decimal b = {.bits = {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(greater_or_equal_zero_with_different_scales) {
  // 0.00 vs 0.000
  s21_decimal a = {.bits = {0, 0, 0, 2 << 16}};
  s21_decimal b = {.bits = {0, 0, 0, 3 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_numbers_need_normalization) {
  // Числа, которые требуют приведения к общему масштабу
  s21_decimal a = {.bits = {1, 0, 0, 0}};
  s21_decimal b = {.bits = {1, 0, 0, 28 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_negative_with_scale) {
  // -1.23 vs -1.25
  s21_decimal a = {.bits = {123, 0, 0, 2 << 16 | 0x80000000U}};
  s21_decimal b = {.bits = {125, 0, 0, 2 << 16 | 0x80000000U}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_normalization_overflow) {
  // Число, которое при нормализации может переполниться
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};
  s21_decimal b = {.bits = {1, 0, 0, 0}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(greater_or_equal_max_with_scale_vs_max) {
  // Максимальное число с масштабом 1 vs максимальное без масштаба
  s21_decimal a = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 16}};

  int result = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite* s21_is_greater_or_equal_suite() {
  Suite* s = suite_create("s21_is_greater_or_equal");

  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, negative_zero_a_and_positive_zero_b);
  tcase_add_test(tc,
                 positive_32_bit_a_is_greater_or_equal_then_positive_32_bit_b);
  tcase_add_test(tc,
                 positive_32_bit_b_is_greater_or_equal_then_positive_32_bit_a);
  tcase_add_test(tc,
                 negative_32_bit_a_is_greater_or_equal_then_positive_32_bit_b);
  tcase_add_test(tc,
                 negative_32_bit_b_is_greater_or_equal_then_positive_32_bit_a);
  tcase_add_test(tc,
                 negative_32_bit_a_is_greater_or_equal_then_negative_32_bit_b);
  tcase_add_test(tc,
                 negative_32_bit_b_is_greater_or_equal_then_negative_32_bit_a);
  tcase_add_test(tc, positive_32_bit_a_equal_positive_32_bit_b);
  tcase_add_test(tc, negative_32_bit_a_equal_negative_32_bit_b);

  tcase_add_test(tc,
                 positive_64_bit_a_is_greater_or_equal_then_positive_64_bit_b);
  tcase_add_test(tc,
                 positive_64_bit_b_is_greater_or_equal_then_positive_64_bit_a);
  tcase_add_test(tc,
                 negative_64_bit_a_is_greater_or_equal_then_positive_64_bit_b);
  tcase_add_test(tc,
                 negative_64_bit_b_is_greater_or_equal_then_positive_64_bit_a);
  tcase_add_test(tc,
                 negative_64_bit_a_is_greater_or_equal_then_negative_64_bit_b);
  tcase_add_test(tc,
                 negative_64_bit_b_is_greater_or_equal_then_negative_64_bit_a);
  tcase_add_test(tc, positive_64_bit_a_equal_positive_64_bit_b);
  tcase_add_test(tc, negative_64_bit_a_equal_negative_64_bit_b);

  tcase_add_test(tc,
                 positive_96_bit_a_is_greater_or_equal_then_positive_96_bit_b);
  tcase_add_test(tc,
                 positive_96_bit_b_is_greater_or_equal_then_positive_96_bit_a);
  tcase_add_test(tc,
                 negative_96_bit_a_is_greater_or_equal_then_positive_96_bit_b);
  tcase_add_test(tc,
                 negative_96_bit_b_is_greater_or_equal_then_positive_96_bit_a);
  tcase_add_test(tc,
                 negative_96_bit_a_is_greater_or_equal_then_negative_96_bit_b);
  tcase_add_test(tc,
                 negative_96_bit_b_is_greater_or_equal_then_negative_96_bit_a);
  tcase_add_test(tc, positive_96_bit_a_equal_positive_96_bit_b);
  tcase_add_test(tc, negative_96_bit_a_equal_negative_96_bit_b);

  tcase_add_test(tc, greater_or_equal_with_scale_same_number);
  tcase_add_test(tc, greater_or_equal_with_different_scale);
  tcase_add_test(tc, greater_or_equal_with_scale_edge);
  tcase_add_test(tc, greater_or_equal_max_decimal_vs_max_minus_one);
  tcase_add_test(tc, greater_or_equal_min_decimal_vs_min_plus_one);
  tcase_add_test(tc, greater_or_equal_zero_with_different_scales);
  tcase_add_test(tc, greater_or_equal_numbers_need_normalization);
  tcase_add_test(tc, greater_or_equal_negative_with_scale);
  tcase_add_test(tc, greater_or_equal_normalization_overflow);
  tcase_add_test(tc, greater_or_equal_max_with_scale_vs_max);

  suite_add_tcase(s, tc);

  return s;
}