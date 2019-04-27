//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef CRYPTOLOGY_NUMBER_THEORY_INCLUDE_NUMBER_THEORY_H_
#define CRYPTOLOGY_NUMBER_THEORY_INCLUDE_NUMBER_THEORY_H_

#include <gmpxx.h>
#include <cstdint>
#include <csignal>

class NumberTheory {
  const int kFermatTestsNumber = 1000;
  const int kMillerRabinTestsNumber = 100;

 public:
  void Power(mpz_t &result, const mpz_t &base, const mpz_t &power, const mpz_t &mod);

  bool FermatTest(const mpz_t &probable_prime);

  void KaratsubaMultiplication(mpz_t &result, const mpz_t &left_mul, const mpz_t &right_mul);

  void ExtendedEuclidean(mpz_t &gcd, mpz_t &x, mpz_t &y, const mpz_t &a, const mpz_t &b);

  bool MillerRabinTest(const mpz_t &probable_prime);

 private:
  struct sigaction act_{}, previous_act_{};

  void HandleSIGSEGV();

  void MishandleSIGSEGV();

  bool Witness(const mpz_t &a, const mpz_t &n);
};

#endif //CRYPTOLOGY_NUMBER_THEORY_INCLUDE_NUMBER_THEORY_H_
