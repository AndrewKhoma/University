//
// Created by ahoma on 20/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <des_cbc.h>

DESCBC::DESCBC(uint64_t key, uint64_t init_val) : des_(key) {
  last_block_ = init_val_ = init_val;
}

uint64_t DESCBC::Encrypt(uint64_t block) {
  last_block_ = des_.Encrypt(block ^ last_block_);
  return last_block_;
}

uint64_t DESCBC::Decrypt(uint64_t block) {
  uint64_t result = des_.Decrypt(block) ^last_block_;
  last_block_ = block;
  return result;
}

void DESCBC::Reset() {
  last_block_ = init_val_;
}
