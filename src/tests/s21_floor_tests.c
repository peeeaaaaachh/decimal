#include "tests.h"

START_TEST(null1) {
  s21_decimal a = {{15, 0, 0, 0}};
  int status = s21_floor(a, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(basic_floor1) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 1);
  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_floor2) {
  s21_decimal compare = {{2000, 0, 0, 0}};
  s21_decimal a = {{2000, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_floor3) {
  s21_decimal compare = {{0, 0, 0, 0}};
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_floor4) {
  s21_decimal compare = {{7, 0, 0, 0}};
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_sign(&compare, 1);

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_floor5) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{249, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 2);
  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(basic_floor6) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{250, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_scale(&a, 2);
  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(negative_floor1) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(negative_floor2) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(negative_floor3) {
  s21_decimal compare = {{1, 0, 0, 0}};
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(negative_floor4) {
  s21_decimal compare = {{2, 0, 0, 0}};
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&a, 1);
  s21_set_scale(&a, 1);
  s21_set_sign(&compare, 1);

  s21_floor(a, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_max_int) {
  s21_decimal value = {{2147483647, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{2147483647, 0, 0, 0}};

  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_large_with_scale) {
  s21_decimal value = {{2147483647, 0, 0, 0}};  // 214748364.7
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{214748364, 0, 0, 0}};

  s21_set_scale(&value, 1);
  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_large_negative) {
  s21_decimal value = {{2147483647, 0, 0, 0}};  // -214748364.7
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{214748365, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 1);
  s21_set_sign(&compare, 1);

  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_almost_integer) {
  s21_decimal value = {{1999999, 0, 0, 0}};  // 1.999999
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{1, 0, 0, 0}};

  s21_set_scale(&value, 6);
  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_almost_integer_negative) {
  s21_decimal value = {{1999999, 0, 0, 0}};  // -1.999999
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{2, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 6);
  s21_set_sign(&compare, 1);

  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_small_fraction) {
  s21_decimal value = {{1, 0, 0, 0}};  // 0.0000001
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{0, 0, 0, 0}};

  s21_set_scale(&value, 7);
  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_small_fraction_negative) {
  s21_decimal value = {{1, 0, 0, 0}};  // -0.0000001
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal compare = {{1, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 7);
  s21_set_sign(&compare, 1);

  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], compare.bits[0]);
  ck_assert_int_eq(res.bits[1], compare.bits[1]);
  ck_assert_int_eq(res.bits[2], compare.bits[2]);
  ck_assert_int_eq(res.bits[3], compare.bits[3]);
}
END_TEST

START_TEST(edge_zero_negative) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  s21_set_sign(&value, 1);

  s21_floor(value, &res);

  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

Suite* s21_floor_suite(void) {
  Suite* s = suite_create("s21_floor");
  TCase* tc = tcase_create("floor");

  tcase_add_test(tc, null1);
  tcase_add_test(tc, basic_floor1);
  tcase_add_test(tc, basic_floor2);
  tcase_add_test(tc, basic_floor3);
  tcase_add_test(tc, basic_floor4);
  tcase_add_test(tc, basic_floor5);
  tcase_add_test(tc, basic_floor6);

  tcase_add_test(tc, negative_floor1);
  tcase_add_test(tc, negative_floor2);
  tcase_add_test(tc, negative_floor3);
  tcase_add_test(tc, negative_floor4);

  tcase_add_test(tc, edge_max_int);
  tcase_add_test(tc, edge_large_with_scale);
  tcase_add_test(tc, edge_large_negative);
  tcase_add_test(tc, edge_almost_integer);
  tcase_add_test(tc, edge_almost_integer_negative);
  tcase_add_test(tc, edge_small_fraction);
  tcase_add_test(tc, edge_small_fraction_negative);
  tcase_add_test(tc, edge_zero_negative);

  suite_add_tcase(s, tc);
  return s;
}