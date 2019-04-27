//
// Created by ahoma on 23/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef CRYPTOLOGY_NUMBER_THEORY_INCLUDE_MONTGOMERY_ARITHMETIC_H_
#define CRYPTOLOGY_NUMBER_THEORY_INCLUDE_MONTGOMERY_ARITHMETIC_H_

#include <gmpxx.h>
#include <cstdint>
#include <csignal>

class MontgomeryArithmetic {
 public:
  void Addition(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo);

  void Subtraction(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo);

  void Multiplication(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo);

  void Inversion(mpz_t &result, const mpz_t &src, const mpz_t &modulo);

  void Division(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo);

  void Power(mpz_t &result, const mpz_t &base, const mpz_t &power, const mpz_t &modulo);

 private:
  struct sigaction act_{}, previous_act_{};

  void HandleSIGSEGV();

  void MishandleSIGSEGV();
};

#endif //CRYPTOLOGY_NUMBER_THEORY_INCLUDE_MONTGOMERY_ARITHMETIC_H_
