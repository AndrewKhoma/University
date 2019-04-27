//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include <des.h>

DES::DES(uint64_t key) {
  Keygen(key);
}

uint64_t DES::Encrypt(uint64_t block) {
  return Des(block, false);
}

uint64_t DES::Decrypt(uint64_t block) {
  return Des(block, true);
}

void DES::Keygen(uint64_t key) {
  // initial key schedule calculation
  uint64_t permuted_choice_1 = 0;  // 56 bits
  for (char i : kPermChoice1) {
    permuted_choice_1 <<= 1;
    permuted_choice_1 |= (key >> (64 - i)) & kLB64Mask;
  }

  // 28 bits
  auto C = (uint32_t) ((permuted_choice_1 >> 28) & 0x000000000fffffff);
  auto D = (uint32_t) (permuted_choice_1 & 0x000000000fffffff);

  // Calculation of the 16 keys
  for (uint8_t i = 0; i < kRoundNum; i++) {
    // key schedule, shifting Ci and Di
    for (uint8_t j = 0; j < kIterationShift[i]; j++) {
      C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
      D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
    }

    uint64_t permuted_choice_2 = (((uint64_t) C) << 28) | (uint64_t) D;

    sub_key_[i] = 0;  // 48 bits (2*24)
    for (char j : kPermChoice2) {
      sub_key_[i] <<= 1;
      sub_key_[i] |= (permuted_choice_2 >> (56 - j)) & kLB64Mask;
    }
  }
}

uint64_t InitPerm(uint64_t block) {
  // initial permutation
  uint64_t result = 0;
  for (char i : kInitPerm) {
    result <<= 1;
    result |= (block >> (64 - i)) & kLB64Mask;
  }
  return result;
}

uint64_t InitInvPerm(uint64_t block) {
  // inverse initial permutation
  uint64_t result = 0;
  for (char i : kInitInversePerm) {
    result <<= 1;
    result |= (block >> (64 - i)) & kLB64Mask;
  }
  return result;
}

void Feistel(uint32_t &L, uint32_t &R, uint32_t F) {
  uint32_t temp = R;
  R = L ^ F;
  L = temp;
}

// Func(R,k) function
uint32_t Func(uint32_t R, uint64_t k) {
  // applying expansion permutation and returning 48-bit data
  uint64_t s_input = 0;
  for (char i : kExpansion) {
    s_input <<= 1;
    s_input |= (uint64_t) ((R >> (32 - i)) & kLB32Mask);
  }

  // XORing expanded Ri with Ki, the round key
  s_input = s_input ^ k;

  // applying S-Boxes function and returning 32-bit data
  uint32_t s_output = 0;
  for (uint8_t i = 0; i < 8; i++) {
    // Outer bits
    auto row = static_cast<char>((s_input & (0x0000840000000000 >> 6 * i)) >> (42 - 6 * i));
    row = static_cast<char>((row >> 4) | (row & 0x01));

    // Middle 4 bits of input
    auto column = static_cast<char>((s_input & (0x0000780000000000 >> 6 * i)) >> (43 - 6 * i));

    s_output <<= 4;
    s_output |= (uint32_t) (kSBox[i][16 * row + column] & 0x0f);
  }

  // applying the round permutation
  uint32_t f_result = 0;
  for (char i : kPermBox) {
    f_result <<= 1;
    f_result |= (s_output >> (32 - i)) & kLB32Mask;
  }

  return f_result;
}

uint64_t DES::Des(uint64_t block, bool mode) {
  // applying initial permutation
  block = InitPerm(block);

  // dividing T' into two 32-bit parts
  auto L = static_cast<uint32_t>((block >> 32) & kL64Mask);
  auto R = static_cast<uint32_t>(block & kL64Mask);

  // 16 rounds
  for (uint8_t i = 0; i < kRoundNum; i++) {
    uint32_t F = mode ? Func(R, sub_key_[15 - i]) : Func(R, sub_key_[i]);
    Feistel(L, R, F);
  }

  // swapping the two parts
  block = (((uint64_t) R) << 32) | (uint64_t) L;
  // applying final permutation
  return InitInvPerm(block);
}

#pragma clang diagnostic pop
