//
// Created by ahoma on 23/04/19.
//

#include <gtest/gtest.h>
#include <montgomery_arithmetic.h>

const int kMaxValue = 100;
const int kModulo = 1000000007;

TEST(MontgomeryArithmeticTest, CorrectWork) {
  MontgomeryArithmetic arithmetic;
  mpz_t result, true_result, lhs, rhs, rhs_inverted, true_rhs_inverted, mod;
  mpz_inits(result, true_result, lhs, rhs,
            rhs_inverted, true_rhs_inverted, mod, nullptr);

  for (int modulo = 1; modulo <= kMaxValue; modulo++) {
    mpz_set_si(mod, modulo);
    for (int first_value = 0; first_value < modulo; first_value++) {
      mpz_set_si(lhs, first_value);
      for (int second_value = 0; second_value < modulo; second_value++) {
        mpz_set_si(rhs, second_value);
        // Addition
        arithmetic.Addition(result, lhs, rhs, mod);
        mpz_add(true_result, lhs, rhs);
        mpz_mod(true_result, true_result, mod);
        ASSERT_EQ(0, mpz_cmp(true_result, result));

        // Subtraction
        arithmetic.Subtraction(result, lhs, rhs, mod);
        mpz_sub(true_result, lhs, rhs);
        mpz_mod(true_result, true_result, mod);
        ASSERT_EQ(0, mpz_cmp(true_result, result));

        if (modulo <= 2 || modulo % 2) {
          // Multiplication
          arithmetic.Multiplication(result, lhs, rhs, mod);
          mpz_mul(true_result, lhs, rhs);
          mpz_mod(true_result, true_result, mod);
          ASSERT_EQ(0, mpz_cmp(true_result, result));

          if (second_value) {
            // Inversion
            if (mpz_invert(true_rhs_inverted, rhs, mod)) {
              arithmetic.Inversion(rhs_inverted, rhs, mod);
              ASSERT_EQ(0, mpz_cmp(true_rhs_inverted, rhs_inverted));

              // Division
              arithmetic.Division(result, lhs, rhs, mod);
              mpz_mul(true_result, lhs, true_rhs_inverted);
              mpz_mod(true_result, true_result, mod);
              ASSERT_EQ(0, mpz_cmp(true_result, result));
            }
          }
        }
      }
    }
  }

  mpz_clears(result, true_result, lhs, rhs,
             rhs_inverted, true_rhs_inverted, mod, nullptr);
}

TEST(MontgomeryArithmeticTest, IncorrectParametrs) {
  MontgomeryArithmetic arithmetic;

  mpz_t mod, incorrect_mod, correct_value, incorrect_value, res;
  mpz_inits(mod, incorrect_mod, correct_value, incorrect_value, res, nullptr);

  mpz_set_si(incorrect_value, -1);
  mpz_set_ui(correct_value, 1);
  mpz_set_ui(mod, 4);
  mpz_set_si(incorrect_mod, -1);

  // Incorrect mod
  ASSERT_THROW(arithmetic.Subtraction(res, correct_value, correct_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Addition(res, correct_value, correct_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Division(res, correct_value, correct_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Division(res, correct_value, correct_value, mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Inversion(res, correct_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Inversion(res, correct_value, mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Multiplication(res, correct_value, correct_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Multiplication(res, correct_value, correct_value, mod), std::invalid_argument);

  // Incorrect values
  ASSERT_THROW(arithmetic.Addition(res, correct_value, incorrect_value, mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Subtraction(res, correct_value, incorrect_value, mod), std::invalid_argument);

  ASSERT_THROW(arithmetic.Addition(res, incorrect_value, correct_value, mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Subtraction(res, incorrect_value, correct_value, mod), std::invalid_argument);

  ASSERT_THROW(arithmetic.Addition(res, incorrect_value, incorrect_value, mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Subtraction(res, incorrect_value, incorrect_value, mod), std::invalid_argument);

  mpz_set_si(incorrect_value, 3);
  mpz_set_si(incorrect_mod, 9);
  ASSERT_THROW(arithmetic.Inversion(res, incorrect_value, incorrect_mod), std::invalid_argument);
  ASSERT_THROW(arithmetic.Division(res, correct_value, incorrect_value, incorrect_mod), std::invalid_argument);

  mpz_clears(mod, incorrect_mod, correct_value, incorrect_value, res, nullptr);
}

const int kPowMaxValue = 1000;

TEST(MontgomeryPowerTest, CorrectWork) {
  MontgomeryArithmetic arithmetic;
  mpz_t base, power, result, mod, true_result;
  mpz_inits(result, power, base, mod, true_result, nullptr);

  mpz_set_ui(mod, kModulo);
  for (int cur_value = 0; cur_value <= kPowMaxValue; cur_value++) {
    mpz_init_set_ui(base, cur_value);
    for (int cur_power = 0; cur_power <= kPowMaxValue; cur_power++) {
      mpz_init_set_ui(power, cur_power);
      mpz_powm(true_result, base, power, mod);
      arithmetic.Power(result, base, power, mod);
      GTEST_ASSERT_EQ(0, mpz_cmp(result, true_result));
    }
  }

  mpz_clears(result, power, base, mod, true_result, nullptr);
}

TEST(MontgomeryPowerTest, PowerSmallerZero) {
  MontgomeryArithmetic arithmetic;
  mpz_t base, power, mod, result;
  mpz_inits(result, power, base, mod, nullptr);

  mpz_set_ui(base, 2);
  mpz_set_si(power, -1);
  mpz_set_si(mod, 2);

  ASSERT_THROW(arithmetic.Power(result, base, power, mod), std::invalid_argument);

  mpz_clears(result, power, base, nullptr);
}

TEST(MontgomeryPowerTest, IncorrectModulo) {
  MontgomeryArithmetic arithmetic;
  mpz_t base, power, mod, result;
  mpz_inits(result, power, base, mod, nullptr);

  mpz_set_ui(base, 2);
  mpz_set_si(power, 1);
  mpz_set_si(mod, 0);
  ASSERT_THROW(arithmetic.Power(result, base, power, mod), std::invalid_argument);
  mpz_set_si(mod, 4);
  ASSERT_THROW(arithmetic.Power(result, base, power, mod), std::invalid_argument);

  mpz_clears(result, power, base, nullptr);
}

