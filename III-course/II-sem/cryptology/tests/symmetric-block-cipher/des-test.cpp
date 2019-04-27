//
// Created by ahoma on 26/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <gtest/gtest.h>
#include <des_cbc.h>
#include <des.h>

const int kKey = 42;
const int kInitValue = 53;
const int kIterationNumber = 100000;

TEST(DESTest, SameKey) {
  DES des(kKey);

  for (uint64_t i = 0; i < kIterationNumber; i++) {
    static uint64_t input, encoded_input, output;
    // from the start
    input = i;
    encoded_input = des.Encrypt(input);
    output = des.Decrypt(encoded_input);
    ASSERT_EQ(output, input);
    // from the end
    input = UINT64_MAX - i;
    encoded_input = des.Encrypt(input);
    output = des.Decrypt(encoded_input);
    ASSERT_EQ(output, input);
  }
}

TEST(DESTest, DifferentKey) {
  DES des1(kKey), des2(kKey + 2);

  for (uint64_t i = 0; i < kIterationNumber; i++) {
    static uint64_t input, encoded_input, output;
    // from the start
    input = i;
    encoded_input = des1.Encrypt(input);
    output = des2.Decrypt(encoded_input);
    ASSERT_NE(output, input);
    // from the end
    input = UINT64_MAX - i;
    encoded_input = des1.Encrypt(input);
    output = des2.Decrypt(encoded_input);
    ASSERT_NE(output, input);
  }
}

TEST(DESCBCTest, SameKeySameInit) {
  DESCBC des(kKey, kInitValue);

  for (uint64_t i = 0; i < kIterationNumber; i++) {
    static uint64_t input, encoded_input, output, prev_output = kInitValue;
    // from the start
    input = i;
    encoded_input = des.Encrypt(input);
    output = des.Decrypt(encoded_input);
    ASSERT_EQ(output ^ encoded_input, input ^ prev_output);
    prev_output = encoded_input;
    // from the end
    input = UINT64_MAX - i;
    encoded_input = des.Encrypt(input);
    output = des.Decrypt(encoded_input);
    ASSERT_EQ(output ^ encoded_input, input ^ prev_output);
    prev_output = encoded_input;
  }
}

TEST(DESCBCTest, DiffKeySameInit) {
  DESCBC des1(kKey, kInitValue), des2(kKey + 2, kInitValue);

  for (uint64_t i = 0; i < kIterationNumber; i++) {
    static uint64_t input, encoded_input, output, prev_output = kInitValue;
    // from the start
    input = i;
    encoded_input = des1.Encrypt(input);
    output = des2.Decrypt(encoded_input);
    ASSERT_NE(output ^ encoded_input, input ^ prev_output);
    prev_output = encoded_input;
    // from the end
    input = UINT64_MAX - i;
    encoded_input = des1.Encrypt(input);
    output = des2.Decrypt(encoded_input);
    ASSERT_NE(output ^ encoded_input, input ^ prev_output);
    prev_output = encoded_input;
  }
}
