//
// Created by ahoma on 21/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <gtest/gtest.h>
#include <number_theory.h>

const int kMaxValue = 1000;

TEST(KaratsubaTest, CorrectWork) {
  NumberTheory numb;
  mpz_t result, true_result, left_m, right_m;
  mpz_inits(result, true_result, left_m, right_m, nullptr);

  for (int first_value = -kMaxValue; first_value <= kMaxValue; first_value++) {
    mpz_set_si(left_m, first_value);
    for (int second_value = -kMaxValue; second_value <= kMaxValue; second_value++) {
      mpz_set_si(right_m, second_value);
      numb.KaratsubaMultiplication(result, left_m, right_m);
      mpz_mul(true_result, left_m, right_m);
      ASSERT_EQ(0, mpz_cmp(true_result, result));
    }
  }

  mpz_clears(result, true_result, left_m, right_m, nullptr);
}
