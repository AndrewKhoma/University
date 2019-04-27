//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_SRC_DES_H_
#define CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_SRC_DES_H_

#include <cstdint>

#include "des_key.h"
#include "des_data.h"

const int kRoundNum = 16;

class DES {
 public:
  explicit DES(uint64_t key);

  uint64_t Encrypt(uint64_t block);
  uint64_t Decrypt(uint64_t block);

 private:
  uint64_t sub_key_[kRoundNum]{};  // 48 bits each

  void Keygen(uint64_t key);

  uint64_t Des(uint64_t block, bool mode);
};

#endif  // CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_SRC_DES_H_
