#include "tests.h"

START_TEST(positive_test) {
  s21_decimal src = {{12, 34, 56, 0}};
  s21_decimal dst = {0};

  int res = s21_negate(src, &dst);

  ck_assert_int_eq(res, 0);

  ck_assert_int_eq(src.bits[0], dst.bits[0]);
  ck_assert_int_eq(src.bits[1], dst.bits[1]);
  ck_assert_int_eq(src.bits[2], dst.bits[2]);
  ck_assert_int_eq(dst.bits[3], 0x80000000U);
}
END_TEST

START_TEST(negative_test) {
  s21_decimal src = {{34, 56, 78, 0x80000000U}};
  s21_decimal dst = {0};

  int res = s21_negate(src, &dst);

  ck_assert_int_eq(res, 0);

  ck_assert_int_eq(src.bits[0], dst.bits[0]);
  ck_assert_int_eq(src.bits[1], dst.bits[1]);
  ck_assert_int_eq(src.bits[2], dst.bits[2]);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(null_test) {
  s21_decimal src = {{12, 3, 4, 0}};

  int res = s21_negate(src, NULL);

  ck_assert_int_eq(res, 1);

  ck_assert_int_eq(src.bits[0], 12);
  ck_assert_int_eq(src.bits[1], 3);
  ck_assert_int_eq(src.bits[2], 4);
  ck_assert_int_eq(src.bits[3], 0);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s = suite_create("s21_negate");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, negative_test);
  tcase_add_test(tc, null_test);

  suite_add_tcase(s, tc);

  return s;
}