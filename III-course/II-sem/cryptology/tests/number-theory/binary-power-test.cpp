//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <gtest/gtest.h>
#include <number_theory.h>

const int kMaxVal = 1000;
const int kModulo = 1000000007;

TEST(BinaryPower, CorrectWork) {
  NumberTheory numb;
  mpz_t base, power, result, mod, true_result;
  mpz_inits(result, power, base, mod, true_result, nullptr);

  mpz_set_ui(mod, kModulo);
  for (int cur_value = -kMaxVal; cur_value <= kMaxVal; cur_value++) {
    mpz_init_set_si(base, cur_value);
    for (int cur_power = 0; cur_power <= kMaxVal; cur_power++) {
      mpz_init_set_si(power, cur_power);
      mpz_powm(true_result, base, power, mod);
      numb.Power(result, base, power, mod);
      GTEST_ASSERT_EQ(0, mpz_cmp(result, true_result));
    }
  }

  mpz_clears(result, power, base, mod, true_result, nullptr);
}

TEST(BinaryPower, PowerSmallerZero) {
  NumberTheory numb;
  mpz_t base, power, mod, result;
  mpz_inits(result, power, base, mod, nullptr);

  mpz_set_ui(base, 2);
  mpz_set_si(power, -1);
  mpz_set_si(mod, 2);

  ASSERT_THROW(numb.Power(result, base, power, mod), std::invalid_argument);

  mpz_clears(result, power, base, nullptr);
}

TEST(BinaryPower, ModEqualZero) {
  NumberTheory numb;
  mpz_t base, power, mod, result;
  mpz_inits(result, power, base, mod, nullptr);

  mpz_set_ui(base, 2);
  mpz_set_si(power, 1);
  mpz_set_si(mod, 0);

  ASSERT_THROW(numb.Power(result, base, power, mod), std::invalid_argument);

  mpz_clears(result, power, base, nullptr);
}

