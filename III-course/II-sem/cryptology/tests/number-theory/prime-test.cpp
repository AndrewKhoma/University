//
// Created by ahoma on 21/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <gtest/gtest.h>
#include <number_theory.h>

const int kPrimeIterationNumb = 10000;

TEST(PrimeTests, CorrectWork) {
  NumberTheory numb;
  mpz_t prev_prime, cur_prime, cur_non_prime;
  mpz_inits(cur_prime, cur_non_prime, nullptr);
  mpz_init_set_ui(prev_prime, 1000000007);

  for (int t = 0; t < kPrimeIterationNumb; t++) {
    mpz_nextprime(cur_prime, prev_prime);
    mpz_add_ui(cur_non_prime, cur_prime, 1);

    ASSERT_TRUE(numb.FermatTest(cur_prime));
    ASSERT_FALSE(numb.FermatTest(cur_non_prime));

    ASSERT_TRUE(numb.MillerRabinTest(cur_prime));
    ASSERT_FALSE(numb.MillerRabinTest(cur_non_prime));

    mpz_set(prev_prime, cur_prime);
  }

  mpz_clears(prev_prime, cur_prime, nullptr);
}

TEST(PrimeTests, PrimeSmallerThanTwo) {
  NumberTheory numb;
  mpz_t numb_0, numb_1, numb_minus_1;
  mpz_inits(numb_0, numb_1, numb_minus_1, nullptr);

  mpz_set_ui(numb_1, 1);
  mpz_set_si(numb_0, 0);
  mpz_set_si(numb_minus_1, -1);

  ASSERT_THROW(numb.FermatTest(numb_1), std::invalid_argument);
  ASSERT_THROW(numb.FermatTest(numb_0), std::invalid_argument);
  ASSERT_THROW(numb.FermatTest(numb_minus_1), std::invalid_argument);

  ASSERT_THROW(numb.MillerRabinTest(numb_1), std::invalid_argument);
  ASSERT_THROW(numb.MillerRabinTest(numb_0), std::invalid_argument);
  ASSERT_THROW(numb.MillerRabinTest(numb_minus_1), std::invalid_argument);

  mpz_clears(numb_0, numb_1, numb_minus_1, nullptr);
}

