#include "tests.h"

void init_big(big_decimal* val, uint32_t b0, uint32_t b1, uint32_t b2,
              uint32_t b3, uint32_t b4, uint32_t b5) {
  val->bits[0] = b0;
  val->bits[1] = b1;
  val->bits[2] = b2;
  val->bits[3] = b3;
  val->bits[4] = b4;
  val->bits[5] = b5;
}

START_TEST(fit_scale_reduction_only) {
  big_decimal val = {0};
  int scale = 30;

  init_big(&val, 123, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(scale, 28);
}
END_TEST

START_TEST(fit_no_changes_needed) {
  big_decimal val = {0};
  int scale = 5;

  init_big(&val, 12345, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(scale, 5);
  ck_assert_uint_eq(val.bits[0], 12345);
}
END_TEST

START_TEST(fit_simple_division) {
  big_decimal val = {0};
  int scale = 2;

  init_big(&val, 1234567890, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(fit_overflow) {
  big_decimal val = {0};
  int scale = 0;

  init_big(&val, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
           0xFFFFFFFF);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 1);
}
END_TEST

/*
 * scale > 28:
 * 15 / 10 = 1 remainder 5
 * banker’s rounding: 1 -> 2, т.к. 1 нечётное
 */
START_TEST(fit_bankers_round_half_from_scale_cut) {
  big_decimal val = {0};
  int scale = 29;

  init_big(&val, 15, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(scale, 28);
  ck_assert_uint_eq(val.bits[0], 2);
}
END_TEST

/*
 * scale > 28:
 * 25 / 10 = 2 remainder 5
 * banker’s rounding: 2 остаётся 2, т.к. 2 чётное
 */

/*
 * scale > 28:
 * 16 / 10 = 1 remainder 6
 * remainder > 5 => round up
 */
START_TEST(fit_round_gt5_from_scale_cut) {
  big_decimal val = {0};
  int scale = 29;

  init_big(&val, 16, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(scale, 28);
  ck_assert_uint_eq(val.bits[0], 2);
}
END_TEST

/*
 * sticky branch:
 * 1555 with scale=3
 * при последовательных делениях будут отброшены ненулевые цифры
 */
START_TEST(fit_round_with_sticky) {
  big_decimal val = {0};
  int scale = 3;

  init_big(&val, 1555, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
}
END_TEST

/*
 * Дополнительная явная проверка sticky-сценария.
 */
START_TEST(fit_force_sticky_branch) {
  big_decimal val = {0};
  int scale = 3;

  init_big(&val, 1555, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
}
END_TEST

/*
 * 251, scale=2:
 * 251 / 10 = 25 rem 1  -> sticky = 1
 * 25 / 10 = 2 rem 5    -> remainder == 5 && sticky == 1 => round up
 */
START_TEST(fit_bankers_round_even_with_sticky) {
  big_decimal val = {0};
  int scale = 2;

  init_big(&val, 251, 0, 0, 0, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
}
END_TEST

/*
 * Берём value = MAX_96 * 10 + 6.
 * После деления получаем MAX_96 и remainder = 6.
 * Дальше округление вверх вызывает переполнение,
 * но scale ещё > 0, значит функция делает ещё одно деление на 10.
 */
START_TEST(fit_round_overflow_then_reduce_scale) {
  big_decimal val = {0};
  int scale = 2;

  init_big(&val, 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 9, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(scale, 0);

  ck_assert_uint_eq(val.bits[0], 2576980377U);
  ck_assert_uint_eq(val.bits[1], 2576980377U);
  ck_assert_uint_eq(val.bits[2], 429496729U);
}
END_TEST

/*
 * Тот же сценарий, но scale=1.
 * После overflow от banker’s rounding дополнительного scale уже нет,
 * значит status должен стать 1.
 */
START_TEST(fit_round_overflow_no_scale_left) {
  big_decimal val = {0};
  int scale = 1;

  init_big(&val, 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 9, 0, 0);

  int status = s21_fit_big_into_decimal(&val, &scale);

  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(scale, 0);
}
END_TEST

Suite* s21_fit_big_into_decimal_suite(void) {
  Suite* s = suite_create("s21_fit_big_into_decimal");
  TCase* tc = tcase_create("fit_big_into_decimal");

  tcase_add_test(tc, fit_scale_reduction_only);
  tcase_add_test(tc, fit_no_changes_needed);
  tcase_add_test(tc, fit_simple_division);
  tcase_add_test(tc, fit_overflow);

  tcase_add_test(tc, fit_bankers_round_half_from_scale_cut);
  tcase_add_test(tc, fit_round_gt5_from_scale_cut);

  tcase_add_test(tc, fit_round_with_sticky);
  tcase_add_test(tc, fit_force_sticky_branch);
  tcase_add_test(tc, fit_bankers_round_even_with_sticky);

  tcase_add_test(tc, fit_round_overflow_then_reduce_scale);
  tcase_add_test(tc, fit_round_overflow_no_scale_left);

  suite_add_tcase(s, tc);
  return s;
}