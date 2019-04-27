//
// Created by ahoma on 27/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#include <gtest/gtest.h>
#include <md4.h>

TEST(MD4Test, CorrectWork) {
  MD4 test;
  test.Append("");
  ASSERT_EQ(test.Get(), "31d6cfe0d16ae931b73c59d7e0c089c0");

  test.Append("a");
  ASSERT_EQ(test.Get(), "bde52cb31de33e46245e05fbdbd6fb24");

  test.Append("abc");
  ASSERT_EQ(test.Get(), "a448017aaf21d8525fc10ae87aa6729d");

  test.Append("message digest");
  ASSERT_EQ(test.Get(), "d9130a8164549fe818874806e1c7014b");

  test.Append("abcdefghijklmnopqrstuvwxyz");
  ASSERT_EQ(test.Get(), "d79e1c308aa5bbcdeea8ed63df412da9");

  test.Append("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  ASSERT_EQ(test.Get(), "043f8582f241db351ce627e153e7f0e4");

  test.Append("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
  ASSERT_EQ(test.Get(), "e33b4ddc9c38f2199c3e7b164fcc0536");
}

std::string FromHexStringToASCIIString(const std::string &input) {
  auto len = static_cast<uint32_t>(input.length());
  std::string new_string, byte;
  for (uint32_t i = 0; i < len; i += 2) {
    byte = input.substr(i, 2);
    char chr = static_cast<char>(static_cast<int>(strtol(byte.c_str(), nullptr, 16)));
    new_string.push_back(chr);
  }
  return new_string;
}

TEST(MD4Test, SameHash) {
  MD4 test1, test2;
  // Two different hex strings
  std::string hex_string1 =
      "839c7a4d7a92cb5678a5d5b9"
      "eea5a7573c8a74deb366c3dc20a083b69f5d2a3bb3719dc69891e9f95e809fd7e8b23ba6318edd45e51fe39708bf9427e9c3e8b9",
      hex_string2 =
      "839c7a4d7a92cbd678a5d529"
      "eea5a7573c8a74deb366c3dc20a083b69f5d2a3bb3719dc69891e9f95e809fd7e8b23ba6318edc45e51fe39708bf9427e9c3e8b9";

  std::string fs_str = FromHexStringToASCIIString(hex_string1),
      sd_str = FromHexStringToASCIIString(hex_string2);
  test1.Append(fs_str);
  test2.Append(sd_str);
  ASSERT_EQ(test1.Get(), test2.Get());
}
