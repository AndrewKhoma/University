//
// Created by ahoma on 27/04/19.
// Copyright (c) 2019 Andrii Khoma. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include <md4.h>

// Constants for MD4Transform routine.
const uint32_t kS11 = 3;
const uint32_t kS12 = 7;
const uint32_t kS13 = 11;
const uint32_t kS14 = 19;
const uint32_t kS21 = 3;
const uint32_t kS22 = 5;
const uint32_t kS23 = 9;
const uint32_t kS24 = 13;
const uint32_t kS31 = 3;
const uint32_t kS32 = 9;
const uint32_t kS33 = 11;
const uint32_t kS34 = 15;

static uint8_t kPadding[kBufferSize] = {0x80};

// Encodes input (uint32_t) into output (uint8_t). Assumes len is a multiple of 4.
static void Encode(uint8_t *output, const uint32_t *input, unsigned int len) {
  if (len % 4) {
    throw std::invalid_argument("Length should be multiple of 4");
  }

  for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = static_cast<uint8_t>(input[i] & 0xff);
    output[j + 1] = static_cast<uint8_t>((input[i] >> 8) & 0xff);
    output[j + 2] = static_cast<uint8_t>((input[i] >> 16) & 0xff);
    output[j + 3] = static_cast<uint8_t>((input[i] >> 24) & 0xff);
  }
}

// Decodes input (uint8_t) into output (uint32_t). Assumes len is a multiple of 4.
static void Decode(uint32_t *output, const uint8_t *input, unsigned int len) {
  if (len % 4) {
    throw std::invalid_argument("Length should be multiple of 4");
  }

  for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((uint32_t) input[j]) | (((uint32_t) input[j + 1]) << 8) |
        (((uint32_t) input[j + 2]) << 16) | (((uint32_t) input[j + 3]) << 24);
}

// F, G and H are basic MD4 functions.
uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
  return ((x & y) | ((~x) & z));
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
  return ((x & y) | (x & z) | (y & z));
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
  return (x ^ y ^ z);
}

// Rotates x left n bits.
uint32_t RotateLeft(uint32_t x, uint32_t n) {
  return (((x) << (n)) | ((x) >> (32 - (n))));
}

// FF, GG and HH are transformations for rounds 1, 2 and 3
// Rotation is separate from addition to prevent recomputation
void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s) {
  a += F(b, c, d) + x;
  a = RotateLeft(a, s);
}

void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s) {
  a += G(b, c, d) + x + (uint32_t) 0x5a827999;
  a = RotateLeft(a, s);
}

void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s) {
  a += H(b, c, d) + x + (uint32_t) 0x6ed9eba1;
  a = RotateLeft(a, s);
}

// MD4 basic transformation. Transforms state based on block.
static void MD4Transform(uint32_t state[kStateNum], uint8_t block[kBufferSize]) {
  static uint32_t a, b, c, d, x[kOutputSize];
  a = state[0], b = state[1], c = state[2], d = state[3];

  Decode(x, block, kBufferSize);

  // Round 1
  FF(a, b, c, d, x[0], kS11);   // 1
  FF(d, a, b, c, x[1], kS12);   // 2
  FF(c, d, a, b, x[2], kS13);   // 3
  FF(b, c, d, a, x[3], kS14);   // 4
  FF(a, b, c, d, x[4], kS11);   // 5
  FF(d, a, b, c, x[5], kS12);   // 6
  FF(c, d, a, b, x[6], kS13);   // 7
  FF(b, c, d, a, x[7], kS14);   // 8
  FF(a, b, c, d, x[8], kS11);   // 9
  FF(d, a, b, c, x[9], kS12);   // 10
  FF(c, d, a, b, x[10], kS13);  // 11
  FF(b, c, d, a, x[11], kS14);  // 12
  FF(a, b, c, d, x[12], kS11);  // 13
  FF(d, a, b, c, x[13], kS12);  // 14
  FF(c, d, a, b, x[14], kS13);  // 15
  FF(b, c, d, a, x[15], kS14);  // 16

  // Round 2
  GG(a, b, c, d, x[0], kS21);   // 17
  GG(d, a, b, c, x[4], kS22);   // 18
  GG(c, d, a, b, x[8], kS23);   // 19
  GG(b, c, d, a, x[12], kS24);  // 20
  GG(a, b, c, d, x[1], kS21);   // 21
  GG(d, a, b, c, x[5], kS22);   // 22
  GG(c, d, a, b, x[9], kS23);   // 23
  GG(b, c, d, a, x[13], kS24);  // 24
  GG(a, b, c, d, x[2], kS21);   // 25
  GG(d, a, b, c, x[6], kS22);   // 26
  GG(c, d, a, b, x[10], kS23);  // 27
  GG(b, c, d, a, x[14], kS24);  // 28
  GG(a, b, c, d, x[3], kS21);   // 29
  GG(d, a, b, c, x[7], kS22);   // 30
  GG(c, d, a, b, x[11], kS23);  // 31
  GG(b, c, d, a, x[15], kS24);  // 32


  // Round 3
  HH(a, b, c, d, x[0], kS31);   // 33
  HH(d, a, b, c, x[8], kS32);   // 34
  HH(c, d, a, b, x[4], kS33);   // 35
  HH(b, c, d, a, x[12], kS34);  // 36
  HH(a, b, c, d, x[2], kS31);   // 37
  HH(d, a, b, c, x[10], kS32);  // 38
  HH(c, d, a, b, x[6], kS33);   // 39
  HH(b, c, d, a, x[14], kS34);  // 40
  HH(a, b, c, d, x[1], kS31);   // 41
  HH(d, a, b, c, x[9], kS32);   // 42
  HH(c, d, a, b, x[5], kS33);   // 43
  HH(b, c, d, a, x[13], kS34);  // 44
  HH(a, b, c, d, x[3], kS31);   // 45
  HH(d, a, b, c, x[11], kS32);  // 46
  HH(c, d, a, b, x[7], kS33);   // 47
  HH(b, c, d, a, x[15], kS34);  // 48

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  // Zeroize sensitive information.
  std::fill(x, x + kOutputSize, 0);
}

MD4::MD4() {
  Reset();
}

void MD4::Reset() {
  count_[0] = count_[1] = 0;

  // Load magic initialization constants.
  state_[0] = 0x67452301;
  state_[1] = 0xefcdab89;
  state_[2] = 0x98badcfe;
  state_[3] = 0x10325476;

  std::fill(buffer_, buffer_ + kBufferSize, 0);
}

void MD4::Append(uint8_t *input, int input_length) {
  unsigned int i, index, partial_length;

  // Compute number of bytes mod 64
  index = static_cast<unsigned int>((count_[0] >> 3) & 0x3F);
  // Update number of bits
  if ((count_[0] += (static_cast<uint32_t>(input_length) << 3)) < (static_cast<uint32_t>(input_length) << 3))
    count_[1]++;
  count_[1] += (static_cast<uint32_t>(input_length) >> 29);

  partial_length = kBufferSize - index;

  // Transform as many times as possible.
  if (input_length >= partial_length) {
    std::copy(input, input + partial_length, &buffer_[index]);
    MD4Transform(state_, buffer_);

    for (i = partial_length; i + kBufferSize - 1 < input_length; i += kBufferSize)
      MD4Transform(state_, &input[i]);

    index = 0;
  } else {
    i = 0;
  }

  // Buffer remaining input
  std::copy(&input[i], &input[i] + input_length - i, &buffer_[index]);
}

void MD4::Append(const std::string &input) {
  auto input_len = static_cast<uint32_t>(input.size());

  Append(const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(input.c_str())), input_len);
}

std::string MD4::Get() {
  uint8_t bits[8];

  // Save number of bits
  Encode(bits, count_, 8);

  // Pad out to 56 mod 64.
  auto index = static_cast<unsigned int>((count_[0] >> 3) & 0x3f);
  unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);
  Append(kPadding, padLen);

  // Append length (before padding)
  Append(bits, 8);
  static uint8_t digest[kOutputSize];
  // Store state in digest
  Encode(digest, state_, kOutputSize);

  // Zeroize sensitive information.
  Reset();

  std::stringstream stream;
  for (uint8_t numb : digest) {
    stream << std::hex << std::setfill('0') << std::setw(2) << int(numb);
  }
  return stream.str();
}

#pragma clang diagnostic pop
