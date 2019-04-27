//
// Created by ahoma on 23/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include <montgomery_arithmetic.h>

void CatchUninitializedVariables(int) {
  throw std::invalid_argument("Uninitialized variables");
}

void MontgomeryArithmetic::HandleSIGSEGV() {
  act_.sa_handler = CatchUninitializedVariables;
  sigemptyset(&act_.sa_mask);
  act_.sa_flags = 0;
  sigaction(SIGSEGV, &act_, &previous_act_);
}

void MontgomeryArithmetic::MishandleSIGSEGV() {
  sigaction(SIGSEGV, &previous_act_, nullptr);
}

void CheckModulo(const mpz_t &mod) {
  if (mpz_sgn(mod) <= 0)
    throw std::invalid_argument("Modulo should be positive");
}

void CheckVariable(const mpz_t &var, const mpz_t &mod, const std::string &variable_name) {
  mpz_t mod_minus_1;
  mpz_init(mod_minus_1);
  mpz_sub_ui(mod_minus_1, mod, 1);

  if (mpz_sgn(var) < 0 || mpz_cmp(var, mod_minus_1) > 0) {
    std::string mod_str(mpz_get_str(nullptr, 10, mod_minus_1));
    mpz_clear(mod_minus_1);
    throw std::invalid_argument("Variable " + variable_name + " should be in range [0, " + mod_str + "]");
  }

  mpz_clear(mod_minus_1);
}

void GetPowerOfTwo(mpz_t &result, uint64_t power, const mpz_t &modulo) {
  mpz_set_ui(result, 1);
  for (int p = 0; p < power; p++) {
    mpz_mul_2exp(result, result, 1);
    if (mpz_cmp(result, modulo) >= 0)
      mpz_sub(result, result, modulo);
  }
}

void MontgomeryArithmetic::Addition(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo) {
  HandleSIGSEGV();

  CheckModulo(modulo);
  CheckVariable(lhs, modulo, "lhs");
  CheckVariable(rhs, modulo, "rhs");

  mpz_t a, b, m;
  mpz_init_set(a, lhs);
  mpz_init_set(b, rhs);
  mpz_init_set(m, modulo);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  mpz_add(result, a, b);
  if (mpz_cmp(result, modulo) >= 0)
    mpz_sub(result, result, modulo);

  mpz_clears(a, b, m, nullptr);
}

void MontgomeryArithmetic::Subtraction(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo) {
  HandleSIGSEGV();

  CheckModulo(modulo);
  CheckVariable(lhs, modulo, "lhs");
  CheckVariable(rhs, modulo, "rhs");

  mpz_t a, b, m;
  mpz_init_set(a, lhs);
  mpz_init_set(b, rhs);
  mpz_init_set(m, modulo);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  mpz_sub(result, a, b);
  if (mpz_sgn(result) < 0)
    mpz_add(result, result, modulo);

  mpz_clears(a, b, m, nullptr);
}

void MontgomeryReduction(mpz_t &result, const mpz_t &src, uint64_t r, const mpz_t &n, const mpz_t &n_dash) {
  mpz_t m, t;
  mpz_inits(m, t, nullptr);

  mpz_tdiv_r_2exp(m, src, r);
  mpz_mul(m, m, n_dash);
  mpz_tdiv_r_2exp(m, m, r);

  mpz_mul(t, m, n);
  mpz_add(t, src, t);
  mpz_tdiv_q_2exp(t, t, r);

  if (mpz_cmp(t, n) >= 0)
    mpz_sub(result, t, n);
  else
    mpz_set(result, t);

  mpz_clears(m, t, nullptr);
}

void ConvertToMontgomery(mpz_t &result, const mpz_t &src, const mpz_t &modulo) {
  uint64_t r_power = mpz_sizeinbase(modulo, 2);
  mpz_t r_squared_mod, r, g, x, y;
  mpz_inits(r_squared_mod, r, g, x, y, nullptr);

  mpz_ui_pow_ui(r, 2, r_power);
  GetPowerOfTwo(r_squared_mod, r_power * 2, modulo);
  mpz_gcdext(g, x, y, r, modulo);
  mpz_neg(y, y);

  while (mpz_sgn(y) < 0)
    mpz_add(y, y, r);

  mpz_mul(result, src, r_squared_mod);
  MontgomeryReduction(result, result, r_power, modulo, y);

  mpz_clears(r_squared_mod, r, g, x, y, nullptr);
}

void ConvertFromMontgomery(mpz_t &result, const mpz_t &src, const mpz_t &modulo) {
  uint64_t r_power = mpz_sizeinbase(modulo, 2);
  mpz_t r_squared_mod, r, g, x, y;
  mpz_inits(r_squared_mod, r, g, x, y, nullptr);

  mpz_ui_pow_ui(r, 2, r_power);
  GetPowerOfTwo(r_squared_mod, r_power * 2, modulo);
  mpz_gcdext(g, x, y, r, modulo);
  mpz_neg(y, y);

  while (mpz_sgn(y) < 0)
    mpz_add(y, y, r);

  MontgomeryReduction(result, src, r_power, modulo, y);

  mpz_clears(r_squared_mod, r, g, x, y, nullptr);
}

void MontgomeryMultiplication(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo) {
  uint64_t r_power = mpz_sizeinbase(modulo, 2);
  mpz_t r, g, x, y;
  mpz_inits(r, g, x, y, nullptr);
  mpz_ui_pow_ui(r, 2, r_power);
  mpz_gcdext(g, x, y, r, modulo);
  mpz_neg(y, y);

  while (mpz_sgn(y) < 0)
    mpz_add(y, y, r);

  mpz_mul(result, lhs, rhs);
  MontgomeryReduction(result, result, r_power, modulo, y);

  mpz_clears(r, g, x, y, nullptr);
}

void MontgomeryArithmetic::Multiplication(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo) {
  HandleSIGSEGV();

  CheckModulo(modulo);

  if (mpz_divisible_2exp_p(modulo, 1) && mpz_cmp_ui(modulo, 2) != 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Modulo should not be divisible by 2");
  }

  CheckVariable(lhs, modulo, "lhs");
  CheckVariable(rhs, modulo, "rhs");

  mpz_t a, b, m;
  mpz_init_set(a, lhs);
  mpz_init_set(b, rhs);
  mpz_init_set(m, modulo);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  if (mpz_cmp_ui(modulo, 2) == 0) {
    mpz_mul(result, a, b);
  } else {
    ConvertToMontgomery(a, a, m);
    ConvertToMontgomery(b, b, m);
    MontgomeryMultiplication(result, a, b, m);
    ConvertFromMontgomery(result, result, m);
  }

  mpz_clears(a, b, m, nullptr);
}

void MontgomeryInversion(mpz_t &result, const mpz_t &src, const mpz_t &modulo) {
  uint64_t r_power = mpz_sizeinbase(modulo, 2);
  mpz_t r_cubic_mod, r, g, x, y_r_mod, y_src_mod;
  mpz_inits(r_cubic_mod, r, g, x, y_r_mod, y_src_mod, nullptr);

  mpz_ui_pow_ui(r, 2, r_power);
  GetPowerOfTwo(r_cubic_mod, r_power * 3, modulo);
  mpz_gcdext(g, x, y_src_mod, modulo, src);
  mpz_gcdext(g, x, y_r_mod, r, modulo);
  mpz_neg(y_r_mod, y_r_mod);

  while (mpz_sgn(y_src_mod) < 0)
    mpz_add(y_src_mod, y_src_mod, modulo);

  while (mpz_sgn(y_r_mod) < 0)
    mpz_add(y_r_mod, y_r_mod, r);

  mpz_mul(result, y_src_mod, r_cubic_mod);
  MontgomeryReduction(result, result, r_power, modulo, y_r_mod);

  mpz_clears(r_cubic_mod, r, g, x, y_r_mod, y_src_mod, nullptr);
}

void MontgomeryArithmetic::Inversion(mpz_t &result, const mpz_t &src, const mpz_t &modulo) {
  HandleSIGSEGV();

  CheckModulo(modulo);
  if (mpz_divisible_2exp_p(modulo, 1) && mpz_cmp_ui(modulo, 2) != 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Modulo should not be divisible by 2");
  }

  CheckVariable(src, modulo, "src");

  mpz_t a, m, gcd;
  mpz_init(gcd);
  mpz_init_set(a, src);
  mpz_init_set(m, modulo);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  mpz_gcd(gcd, a, m);
  if (mpz_cmp_ui(gcd, 1) != 0) {
    mpz_clears(a, m, gcd, nullptr);
    throw std::invalid_argument("Source value should have gcd equal 1 with modulo");
  }

  if (mpz_cmp_ui(modulo, 2) == 0) {
    mpz_set(result, a);
  } else {
    ConvertToMontgomery(a, a, m);
    MontgomeryInversion(result, a, m);
    ConvertFromMontgomery(result, result, m);
  }

  mpz_clears(a, m, gcd, nullptr);
}

void MontgomeryArithmetic::Division(mpz_t &result, const mpz_t &lhs, const mpz_t &rhs, const mpz_t &modulo) {
  HandleSIGSEGV();

  CheckModulo(modulo);
  if (mpz_divisible_2exp_p(modulo, 1) && mpz_cmp_ui(modulo, 2) != 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Modulo should not be divisible by 2");
  }

  CheckVariable(lhs, modulo, "lhs");
  CheckVariable(rhs, modulo, "rhs");

  mpz_t a, b, gcd, m;
  mpz_init(gcd);
  mpz_init_set(a, lhs);
  mpz_init_set(b, rhs);
  mpz_init_set(m, modulo);
  mpz_set_ui(result, 0);

  MishandleSIGSEGV();

  mpz_gcd(gcd, b, m);
  if (mpz_cmp_ui(gcd, 1) != 0) {
    mpz_clears(a, b, m, gcd, nullptr);
    throw std::invalid_argument("Rhs value should have gcd equal 1 with modulo");
  }

  if (mpz_cmp_ui(modulo, 2) == 0) {
    mpz_mul(result, a, b);
  } else {
    ConvertToMontgomery(a, a, m);
    ConvertToMontgomery(b, b, m);
    MontgomeryInversion(b, b, m);
    MontgomeryMultiplication(result, a, b, m);
    ConvertFromMontgomery(result, result, m);
  }

  mpz_clears(a, b, m, gcd, nullptr);
}

void MontgomeryArithmetic::Power(mpz_t &result, const mpz_t &base, const mpz_t &power, const mpz_t &modulo) {
  HandleSIGSEGV();

  if (mpz_sgn(power) < 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Power should be non-negative");
  }

  CheckModulo(modulo);
  if (mpz_divisible_2exp_p(modulo, 1) && mpz_cmp_ui(modulo, 2) != 0) {
    MishandleSIGSEGV();
    throw std::invalid_argument("Modulo should not be divisible by 2");
  }

  CheckVariable(base, modulo, "base");

  mpz_t cur_base, cur_power;

  mpz_init_set(cur_base, base);
  mpz_init_set(cur_power, power);
  mpz_set_ui(result, 1);

  MishandleSIGSEGV();

  if (mpz_cmp_ui(modulo, 2) == 0 && mpz_sgn(power) > 0) {
    mpz_set(result, base);
  } else {
    ConvertToMontgomery(cur_base, cur_base, modulo);
    ConvertToMontgomery(result, result, modulo);

    while (mpz_cmp_si(cur_power, 0) > 0) {
      if (mpz_odd_p(cur_power)) {
        MontgomeryMultiplication(result, result, cur_base, modulo);
      }

      MontgomeryMultiplication(cur_base, cur_base, cur_base, modulo);
      mpz_tdiv_q_2exp(cur_power, cur_power, 1);
    }

    ConvertFromMontgomery(result, result, modulo);
  }

  mpz_clears(cur_base, cur_power, nullptr);
}

#pragma clang diagnostic pop
