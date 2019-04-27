//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#ifndef CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_INCLUDE_DESCBC_H_
#define CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_INCLUDE_DESCBC_H_

#include "des.h"

class DESCBC {
 public:
  DESCBC(uint64_t key, uint64_t init_val);

  uint64_t Encrypt(uint64_t block);

  uint64_t Decrypt(uint64_t block);

  void Reset();

 private:
  DES des_;
  uint64_t init_val_, last_block_;
};

#endif  // CRYPTOLOGY_SYMMETRIC_BLOCK_CIPHER_INCLUDE_DESCBC_H_
