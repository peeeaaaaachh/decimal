#include <check.h>

#include "../s21_decimal.h"
#include "tests.h"

s21_decimal decimal(int value, int scale, int sign) {
  s21_decimal d = {0};
  d.bits[0] = value;
  s21_set_scale(&d, scale);
  s21_set_sign(&d, sign);
  return d;
}

START_TEST(test_div_small_1) {
  // 100 / 50 = 2
  s21_decimal decimal1 = decimal(100, 0, 0);
  s21_decimal decimal2 = decimal(50, 0, 0);
  s21_decimal expected = decimal(2, 0, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_2) {
  // 25 / 4 = 6.25
  s21_decimal decimal1 = decimal(25, 0, 0);
  s21_decimal decimal2 = decimal(4, 0, 0);
  s21_decimal expected = decimal(625, 2, 0);  // 6.25
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_3) {
  // 7 / 3 = 3,5
  s21_decimal decimal1 = decimal(7, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 0);
  s21_decimal expected = decimal(35, 1, 0);  // 3.5
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_4) {
  // 1 / 10 = 0.1
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(10, 0, 0);
  s21_decimal expected = decimal(1, 1, 0);  // 0.1
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_5) {
  // 1 / 100 = 0.01
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(100, 0, 0);
  s21_decimal expected = decimal(1, 2, 0);  // 0.01
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_6) {
  // 15 / 4 = 3.75
  s21_decimal decimal1 = decimal(15, 0, 0);
  s21_decimal decimal2 = decimal(4, 0, 0);
  s21_decimal expected = decimal(375, 2, 0);  // 3.75
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_7) {
  // 1 / 8 = 0.125
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(8, 0, 0);
  s21_decimal expected = decimal(125, 3, 0);  // 0.125
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_negative_1) {
  // 10 / -2 = -5
  s21_decimal decimal1 = decimal(10, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 1);  // -2
  s21_decimal expected = decimal(5, 0, 1);  // -5
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_negative_2) {
  // -10 / -2 = 5
  s21_decimal decimal1 = decimal(10, 0, 1);  // -10
  s21_decimal decimal2 = decimal(2, 0, 1);   // -2
  s21_decimal expected = decimal(5, 0, 0);   // 5
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_negative_3) {
  // -10 / 2 = -5
  s21_decimal decimal1 = decimal(10, 0, 1);  // -10
  s21_decimal decimal2 = decimal(2, 0, 0);   // 2
  s21_decimal expected = decimal(5, 0, 1);   // -5
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_1) {
  // 1.5 / 0.5 = 3
  s21_decimal decimal1 = decimal(15, 1, 0);  // 1.5
  s21_decimal decimal2 = decimal(5, 1, 0);   // 0.5
  s21_decimal expected = decimal(3, 0, 0);   // 3
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_2) {
  // 0.75 / 0.25 = 3
  s21_decimal decimal1 = decimal(75, 2, 0);  // 0.75
  s21_decimal decimal2 = decimal(25, 2, 0);  // 0.25
  s21_decimal expected = decimal(3, 0, 0);   // 3
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_3) {
  // 0.2 / 0.1 = 2
  s21_decimal decimal1 = decimal(2, 1, 0);  // 0.2
  s21_decimal decimal2 = decimal(1, 1, 0);  // 0.1
  s21_decimal expected = decimal(2, 0, 0);  // 2
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_4) {
  // 2.5 / 0.5 = 5
  s21_decimal decimal1 = decimal(25, 1, 0);  // 2.5
  s21_decimal decimal2 = decimal(5, 1, 0);   // 0.5
  s21_decimal expected = decimal(5, 0, 0);   // 5
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_5) {
  // 0.125 / 0.5 = 0.25
  s21_decimal decimal1 = decimal(125, 3, 0);  // 0.125
  s21_decimal decimal2 = decimal(5, 1, 0);    // 0.5
  s21_decimal expected = decimal(25, 2, 0);   // 0.25
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_6) {
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 0);

  s21_decimal expected = decimal(5, 1, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}

START_TEST(test_div_small_with_scale_7) {
  s21_decimal decimal1 = decimal(15, 0, 0);
  s21_decimal decimal2 = decimal(4, 0, 0);
  s21_decimal expected = decimal(375, 2, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_with_scale_8) {
  s21_decimal decimal1 = decimal(7, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 0);
  s21_decimal expected = decimal(35, 1, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_overflow_1) {
  s21_decimal a = {0};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;  // MAX_DECIMAL

  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_set_scale(&b, 1);

  s21_decimal res;
  int err = s21_div(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_div_overflow_2) {
  s21_decimal a = {0};
  a.bits[0] = 0x6DF37F67;
  a.bits[1] = 0x8CB89C2A;
  a.bits[2] = 0x5AF3107A;  // примерно 10^28

  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_set_scale(&b, 28);  // 0.000...001 (28 нулей после запятой)

  s21_decimal res;
  int err = s21_div(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_div_overflow_3) {
  s21_decimal a = {0};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;

  s21_decimal b = {0};
  b.bits[0] = 9;
  s21_set_scale(&b, 1);  // 0.9

  s21_decimal res;
  int err = s21_div(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_div_overflow_4) {
  s21_decimal a = {0};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;

  s21_decimal b = {0};
  b.bits[0] = 5;
  s21_set_scale(&b, 1);  // 0.5

  s21_decimal res;
  int err = s21_div(a, b, &res);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_div_overflow_5) {
  s21_decimal a = {0};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;  // MAX_DECIMAL

  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_set_scale(&b, 1);  // 0.1

  s21_decimal res;
  int err = s21_div(a, b, &res);

  ck_assert_int_eq(err, 1);  // Ожидаем переполнение
}
END_TEST

START_TEST(test_div_overflow_6) {
  s21_decimal a = {0};
  // 79228162514264337593543950335 (MAX_DECIMAL)
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);

  s21_decimal b = {0};
  b.bits[0] = 1;
  s21_set_scale(&b, 28);

  s21_decimal res;
  int err = s21_div(a, b, &res);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_div1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal expected = {{0xA, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal expected = {{0xA, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 3
  s21_decimal expected = {{0x3, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal expected = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999998915797827
  s21_decimal expected = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999998915797827
  s21_decimal expected = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div10) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div11) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x80190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div12) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div13) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x80190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div14) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div15) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -0.0000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x80190000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div16) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 0.000000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x1B0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div17) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -0.000000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x801B0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div18) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x1C0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div19) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x801C0000}};
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_bankers_5) {
  // 1 / 6 = 0.1666666666666666666666666667 (28 знаков, банковское округление)
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(6, 0, 0);

  s21_decimal expected = {{0x82AAAAAB, 0x0A5B8065, 0x0562A265, 0x001C0000}};

  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_bankers_6) {
  // 5 / 2 = 2.5 → округление к чётному = 2
  s21_decimal decimal1 = decimal(5, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 0);
  s21_decimal expected = decimal(25, 1, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_bankers_7) {
  s21_decimal decimal1 = decimal(7, 0, 0);
  s21_decimal decimal2 = decimal(2, 0, 0);
  s21_decimal expected = decimal(35, 1, 0);
  s21_decimal result = {0};

  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_bankers_8) {
  s21_decimal decimal1 = decimal(1, 0, 0);
  s21_decimal decimal2 = decimal(3, 0, 0);

  // 0.3333333333333333333333333333 (28 знаков, округлено)
  s21_decimal expected = {{0x05555555, 0x14B700CB, 0x0AC544CA, 0x001C0000}};
  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  END_TEST
}

START_TEST(test_div_bankers_9) {
  // -5 / 2 = -2.5 → округление к чётному = -2
  s21_decimal decimal1 = decimal(5, 0, 1);  // -5
  s21_decimal decimal2 = decimal(2, 0, 0);

  s21_decimal expected = decimal(25, 1, 1);
  s21_set_sign(&expected, 1);

  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  END_TEST
}

START_TEST(test_div20) {
  // 10
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // 10000
  s21_decimal expected = {{0x2710, 0x0, 0x0, 0x0}};
  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  END_TEST
}

START_TEST(test_div21) {
  // 10
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // -10000
  s21_decimal expected = {{0x2710, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  END_TEST
}

START_TEST(test_div22) {
  // 10
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // 526.31578947368421052631578947
  s21_decimal expected = {{0xA50D7943, 0xCDD0426A, 0xAA0FD25B, 0x1A0000}};

  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  END_TEST
}

START_TEST(test_div23) {
  // 10
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  s21_decimal result = {0};
  int err = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 3);
  END_TEST
}

START_TEST(test_div24) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x10000}};

  s21_decimal result = {0};
  int err = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(err, 0);
  END_TEST
}

Suite* s21_div_suite(void) {
  Suite* s = suite_create("s21_div");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_div_small_1);
  tcase_add_test(tc_core, test_div_small_2);
  tcase_add_test(tc_core, test_div_small_3);
  tcase_add_test(tc_core, test_div_small_4);
  tcase_add_test(tc_core, test_div_small_5);
  tcase_add_test(tc_core, test_div_small_6);
  tcase_add_test(tc_core, test_div_small_7);

  tcase_add_test(tc_core, test_div_small_negative_1);
  tcase_add_test(tc_core, test_div_small_negative_2);
  tcase_add_test(tc_core, test_div_small_negative_3);

  tcase_add_test(tc_core, test_div_small_with_scale_1);
  tcase_add_test(tc_core, test_div_small_with_scale_2);
  tcase_add_test(tc_core, test_div_small_with_scale_3);
  tcase_add_test(tc_core, test_div_small_with_scale_4);
  tcase_add_test(tc_core, test_div_small_with_scale_5);
  tcase_add_test(tc_core, test_div_small_with_scale_6);
  tcase_add_test(tc_core, test_div_small_with_scale_7);
  tcase_add_test(tc_core, test_div_small_with_scale_8);

  tcase_add_test(tc_core, test_div_overflow_1);
  tcase_add_test(tc_core, test_div_overflow_2);
  tcase_add_test(tc_core, test_div_overflow_3);
  tcase_add_test(tc_core, test_div_overflow_4);
  tcase_add_test(tc_core, test_div_overflow_5);
  tcase_add_test(tc_core, test_div_overflow_6);

  tcase_add_test(tc_core, test_div1);
  tcase_add_test(tc_core, test_div2);
  tcase_add_test(tc_core, test_div3);
  tcase_add_test(tc_core, test_div4);
  tcase_add_test(tc_core, test_div5);
  tcase_add_test(tc_core, test_div6);
  tcase_add_test(tc_core, test_div7);
  tcase_add_test(tc_core, test_div8);
  tcase_add_test(tc_core, test_div9);
  tcase_add_test(tc_core, test_div10);
  tcase_add_test(tc_core, test_div11);
  tcase_add_test(tc_core, test_div12);
  tcase_add_test(tc_core, test_div13);
  tcase_add_test(tc_core, test_div14);
  tcase_add_test(tc_core, test_div15);
  tcase_add_test(tc_core, test_div16);
  tcase_add_test(tc_core, test_div17);
  tcase_add_test(tc_core, test_div18);
  tcase_add_test(tc_core, test_div19);

  tcase_add_test(tc_core, test_div_bankers_5);
  tcase_add_test(tc_core, test_div_bankers_6);
  tcase_add_test(tc_core, test_div_bankers_7);
  tcase_add_test(tc_core, test_div_bankers_8);
  tcase_add_test(tc_core, test_div_bankers_9);

  tcase_add_test(tc_core, test_div20);
  tcase_add_test(tc_core, test_div21);
  tcase_add_test(tc_core, test_div22);
  tcase_add_test(tc_core, test_div23);
  tcase_add_test(tc_core, test_div24);

  suite_add_tcase(s, tc_core);
  return s;
}
