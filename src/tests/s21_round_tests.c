#include "tests.h"

START_TEST(null1) {
  s21_decimal a = {{15, 0, 0, 0}};

  int status = s21_round(a, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(basic_round1) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 1);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_round2) {
  s21_decimal compare = {{2000, 0, 0, 0}};
  s21_decimal a = {{2000, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_round3) {
  s21_decimal compare = {{0, 0, 0, 0}};
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_round4) {
  s21_decimal compare = {{7, 0, 0, 0}};
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_sign(&compare, 1);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_round5) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{249, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 2);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_round6) {
  s21_decimal compare = {{3, 0, 0, 0}};
  s21_decimal a = {{250, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 2);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_negative_round7) {
  s21_decimal compare = {{0, 0, 0, 0}};
  s21_decimal a = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_negative_round8) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_negative_round9) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_negative_round10) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(scale_test1) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{1234, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 3);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(scale_test2) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{1500, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 3);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(scale_test3) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{1245, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 3);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(scale_test4) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{1246, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 3);

  s21_set_sign(&compare, 1);

  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(round_accuracy1) {
  s21_decimal compare = {{3, 0, 0, 0}};
  s21_decimal a = {{25000001, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 7);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(round_accuracy2) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{24999999, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 7);
  s21_round(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(angle_extreme_small_positive) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{0, 0, 0, 0}};

  s21_set_scale(&value, 7);
  s21_round(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(angle_extreme_small_negative) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{0, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 7);
  s21_round(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(angle_large_number) {
  s21_decimal value = {{2147483647, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{2147483647, 0, 0, 0}};

  s21_round(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(angle_large_number_half) {
  s21_decimal value = {{2147483645, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{214748365, 0, 0, 0}};

  s21_set_scale(&value, 1);
  s21_round(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

Suite* s21_round_suite(void) {
  Suite* s = suite_create("s21_round");
  TCase* tc = tcase_create("round");

  tcase_add_test(tc, null1);
  tcase_add_test(tc, basic_round1);
  tcase_add_test(tc, basic_round2);
  tcase_add_test(tc, basic_round3);
  tcase_add_test(tc, basic_round3);
  tcase_add_test(tc, basic_round4);
  tcase_add_test(tc, basic_round5);
  tcase_add_test(tc, basic_round6);

  tcase_add_test(tc, basic_negative_round7);
  tcase_add_test(tc, basic_negative_round8);
  tcase_add_test(tc, basic_negative_round9);
  tcase_add_test(tc, basic_negative_round10);

  tcase_add_test(tc, scale_test1);
  tcase_add_test(tc, scale_test2);
  tcase_add_test(tc, scale_test3);
  tcase_add_test(tc, scale_test4);

  tcase_add_test(tc, round_accuracy1);
  tcase_add_test(tc, round_accuracy2);

  tcase_add_test(tc, angle_extreme_small_positive);
  tcase_add_test(tc, angle_extreme_small_negative);
  tcase_add_test(tc, angle_large_number);
  tcase_add_test(tc, angle_large_number_half);

  suite_add_tcase(s, tc);

  return s;
}