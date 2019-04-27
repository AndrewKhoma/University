//
// Created by ahoma on 27/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef CRYPTOLOGY_HASH_FUNCTION_INCLUDE_MD4_H_
#define CRYPTOLOGY_HASH_FUNCTION_INCLUDE_MD4_H_

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <string>

const int kStateNum = 4;
const int kOutputSize = 16;
const int kBufferSize = 64;

class MD4 {
 public:
  MD4();

  void Reset();

  void Append(const std::string &input);

  std::string Get();

 private:
  uint32_t state_[kStateNum]{};    // state (ABCD)
  uint32_t count_[2]{};            // number of bits, modulo 2^64 (lsb first)
  uint8_t buffer_[kBufferSize]{};  // input buffer

  void Append(uint8_t *input, int input_length);
};

#endif  // CRYPTOLOGY_HASH_FUNCTION_INCLUDE_MD4_H_
