//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include <number_theory.h>

void CatchUninitializedVariables(int) {
  throw std::invalid_argument("Uninitialized variables");
}

void NumberTheory::HandleSIGSEGV() {
  act_.sa_handler = CatchUninitializedVariables;
  sigemptyset(&act_.sa_mask);
  act_.sa_flags = 0;
  sigaction(SIGSEGV, &act_, &previous_act_);
}

void NumberTheory::MishandleSIGSEGV() {
  sigaction(SIGSEGV, &previous_act_, nullptr);
}

void NumberTheory::Power(mpz_t &result, const mpz_t &base, const mpz_t &power, const mpz_t &mod) {
  HandleSIGSEGV();

  if (mpz_sgn(power) < 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Power should be non-negative");
  }

  if (mpz_sgn(mod) == 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Modulo should not be zero");
  }

  mpz_t cur_base, cur_power;

  mpz_init_set(cur_base, base);
  mpz_init_set(cur_power, power);
  mpz_set_ui(result, 1);

  MishandleSIGSEGV();

  if (mpz_cmp(cur_base, mod) >= 0)
    mpz_mod(cur_base, cur_base, mod);

  while (mpz_cmp_si(cur_power, 0) > 0) {
    if (mpz_odd_p(cur_power)) {
      mpz_mul(result, result, cur_base);
      if (mpz_cmp(result, mod) >= 0)
        mpz_mod(result, result, mod);
    }

    mpz_mul(cur_base, cur_base, cur_base);
    if (mpz_cmp(cur_base, mod) >= 0)
      mpz_mod(cur_base, cur_base, mod);
    mpz_tdiv_q_2exp(cur_power, cur_power, 1);
  }

  mpz_clears(cur_base, cur_power, nullptr);
}

bool NumberTheory::FermatTest(const mpz_t &probable_prime) {
  HandleSIGSEGV();

  if (mpz_cmp_ui(probable_prime, 1) <= 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Prime number should be bigger be bigger than one");
  }

  if (mpz_cmp_ui(probable_prime, 2) == 0) {
    MishandleSIGSEGV();
    return true;
  }

  mpz_t cur_prime, check_number, reminder, power;
  mpz_inits(check_number, reminder, nullptr);
  mpz_init_set(cur_prime, probable_prime);
  mpz_init_set(power, probable_prime);
  mpz_sub_ui(power, power, 1);

  MishandleSIGSEGV();

  gmp_randstate_t random_state;
  gmp_randinit_mt(random_state);
  gmp_randseed_ui(random_state, static_cast<uint32_t>(time(nullptr)));

  bool result = true;

  for (int i = 0; i < kFermatTestsNumber && result; i++) {
    mpz_set_ui(check_number, 0);
    while (mpz_cmp_ui(check_number, 1) <= 0)
      mpz_urandomm(check_number, random_state, cur_prime);
    if (!i)
      mpz_set_ui(check_number, 2);

    Power(reminder, check_number, power, cur_prime);
    if (mpz_cmp_ui(reminder, 1) != 0)
      result = false;
  }

  gmp_randclear(random_state);
  mpz_clears(cur_prime, check_number, reminder, power, nullptr);

  return result;
}

void KaratsubaMultiplicationInitialized(mpz_t &result, const mpz_t &left_mul, const mpz_t &right_mul) {
  if (mpz_cmpabs_ui(left_mul, 2) < 0 || mpz_cmpabs_ui(right_mul, 2) < 0) {
    mpz_mul(result, left_mul, right_mul);
  } else {
    size_t m = std::min(mpz_sizeinbase(left_mul, 2), mpz_sizeinbase(right_mul, 2));
    m /= 2;

    mpz_t left_q, right_q, left_r, right_r, sum_left, sum_right, temp;
    mpz_inits(left_q, right_q, left_r, right_r, sum_left, sum_right, temp, nullptr);

    mpz_tdiv_q_2exp(left_q, left_mul, m);
    mpz_tdiv_r_2exp(left_r, left_mul, m);
    mpz_tdiv_q_2exp(right_q, right_mul, m);
    mpz_tdiv_r_2exp(right_r, right_mul, m);
    mpz_add(sum_left, left_q, left_r);
    mpz_add(sum_right, right_q, right_r);

    mpz_t z0, z1, z2;
    mpz_inits(z0, z1, z2, nullptr);

    KaratsubaMultiplicationInitialized(z0, left_r, right_r);
    KaratsubaMultiplicationInitialized(z1, sum_left, sum_right);
    KaratsubaMultiplicationInitialized(z2, left_q, right_q);

    mpz_mul_2exp(result, z2, 2 * m);
    mpz_sub(temp, z1, z2);
    mpz_sub(temp, temp, z0);
    mpz_mul_2exp(temp, temp, m);
    mpz_add(result, result, temp);
    mpz_add(result, result, z0);

    mpz_clears(z0, z1, z2, nullptr);
    mpz_clears(left_q, right_q, left_r, right_r, sum_left, sum_right, temp, nullptr);
  }
}

void NumberTheory::KaratsubaMultiplication(mpz_t &result, const mpz_t &left_mul, const mpz_t &right_mul) {
  HandleSIGSEGV();

  mpz_t lhs, rhs;
  mpz_init_set(lhs, left_mul);
  mpz_init_set(rhs, right_mul);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  KaratsubaMultiplicationInitialized(result, left_mul, right_mul);

  mpz_clears(lhs, rhs, nullptr);
}

void ExtendedEuclideanInitialized(mpz_t &gcd, mpz_t &x, mpz_t &y, const mpz_t &a, const mpz_t &b) {
  if (mpz_sgn(b) == 0) {
    mpz_set(gcd, a);
    mpz_set_ui(x, 1);
    mpz_set_ui(y, 0);
  } else {
    mpz_t q, r, cur_x, cur_y, temp;
    mpz_inits(q, r, cur_x, cur_y, temp, nullptr);
    mpz_tdiv_qr(q, r, a, b);

    ExtendedEuclideanInitialized(gcd, x, y, b, r);

    mpz_set(cur_x, y);
    mpz_mul(temp, q, y);
    mpz_sub(cur_y, x, temp);
    mpz_set(x, cur_x);
    mpz_set(y, cur_y);

    mpz_clears(q, r, cur_x, cur_y, temp, nullptr);
  }
}

void NumberTheory::ExtendedEuclidean(mpz_t &gcd, mpz_t &x, mpz_t &y, const mpz_t &a, const mpz_t &b) {
  HandleSIGSEGV();

  mpz_set_ui(gcd, 0);
  mpz_set_ui(x, 0);
  mpz_set_ui(y, 0);
  mpz_t init_a, init_b;
  mpz_init_set(init_a, a);
  mpz_init_set(init_b, b);

  MishandleSIGSEGV();

  ExtendedEuclideanInitialized(gcd, x, y, init_a, init_b);

  if (mpz_sgn(gcd) < 0) {
    mpz_neg(gcd, gcd);
    mpz_neg(x, x);
    mpz_neg(y, y);
  }

  mpz_clears(init_a, init_b, nullptr);
}

bool NumberTheory::Witness(const mpz_t &a, const mpz_t &n) {
  mpz_t n_minus_1, cur_value, prev_value, u;
  mpz_inits(n_minus_1, cur_value, prev_value, u, nullptr);
  mpz_sub_ui(n_minus_1, n, 1);
  bool result = false;

  mp_bitcnt_t t = mpz_scan1(n_minus_1, 0);
  mpz_tdiv_q_2exp(u, n_minus_1, t);
  Power(prev_value, a, u, n);

  for (int i = 0; i < t && !result; i++) {
    mpz_mul(cur_value, prev_value, prev_value);
    mpz_mod(cur_value, cur_value, n);
    if (mpz_cmp_ui(cur_value, 1) == 0 && mpz_cmp_ui(prev_value, 1) && mpz_cmp(prev_value, n_minus_1))
      result = true;
    mpz_set(prev_value, cur_value);
  }

  result = (mpz_cmp_ui(cur_value, 1) != 0);

  mpz_clears(n_minus_1, cur_value, prev_value, u, nullptr);
  return result;
}

bool NumberTheory::MillerRabinTest(const mpz_t &probable_prime) {
  HandleSIGSEGV();

  if (mpz_cmp_ui(probable_prime, 1) <= 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Prime number should be bigger be bigger than one");
  }

  if (mpz_cmp_ui(probable_prime, 2) == 0) {
    MishandleSIGSEGV();
    return true;
  }

  if (mpz_divisible_ui_p(probable_prime, 2)) {
    MishandleSIGSEGV();
    return false;
  }

  mpz_t cur_prime;
  mpz_init_set(cur_prime, probable_prime);

  MishandleSIGSEGV();

  mpz_t check_number;
  mpz_init(check_number);

  gmp_randstate_t random_state;
  gmp_randinit_mt(random_state);
  gmp_randseed_ui(random_state, static_cast<uint32_t>(time(nullptr)));

  bool result = true;

  for (int i = 0; i < kMillerRabinTestsNumber && result; i++) {
    mpz_set_ui(check_number, 0);
    while (mpz_cmp_ui(check_number, 1) <= 0)
      mpz_urandomm(check_number, random_state, cur_prime);

    if (Witness(check_number, cur_prime))
      result = false;
  }

  gmp_randclear(random_state);
  mpz_clears(cur_prime, check_number, nullptr);

  return result;
}

#pragma clang diagnostic pop