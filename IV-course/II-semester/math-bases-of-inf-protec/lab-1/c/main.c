#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

int64_t RecursiveGCD(int64_t x, int64_t y) {
  if (x < 0) {
    x = labs(x);
  }

  if (y < 0) {
    y = labs(y);
  }

  assert(x >= 1 || y >= 1);

  if (!x) {
    return y;
  } else if (!y) {
    return x;
  }

  if (x == y) {
    return y;
  } else if (x < y) {
    return RecursiveGCD(x, y % x);
  } else {
    return RecursiveGCD(y, x % y);
  }
}

int64_t BinaryGCD(int64_t x, int64_t y) {
  x = labs(x), y = labs(y);

  assert(x >= 1 && y >= 1);

  if (x < y) {
    // x >= y
    x ^= y;
    y ^= x;
    x ^= y;
  }

  int64_t result = 1;
  while (!(x & 1) && !(y & 1)) {
    x >>= 1, y >>= 1, result <<= 1;
  }

  while (x) {
    while (!(x & 1)) x >>= 1;
    while (!(y & 1)) y >>= 1;
    int64_t t = labs(x - y) / 2;
    if (x >= y) {
      x = t;
    } else {
      y = t;
    }
  }

  return result * y;
}

int64_t BinaryExtendedGCD(int64_t x, int64_t y, int64_t *a, int64_t *b) {
  x = labs(x), y = labs(y);

  assert(x >= 1 && y >= 1);

  int64_t result = 1;
  while (!(x & 1) && !(y & 1)) {
    x >>= 1, y >>= 1, result <<= 1;
  }

  int64_t u = x, v = y, A = 1, B = 0, C = 0, D = 1;

  do {
    while (!(u & 1)) {
      u >>= 1;
      if (!(A & 1) && !(B & 1)) {
        A >>= 1, B >>= 1;
      } else {
        A = ((A + y) >> 1), B = ((B - x) >> 1);
      }
    }

    while (!(v & 1)) {
      v >>= 1;
      if (!(C & 1) && !(D & 1)) {
        C >>= 1, D >>= 1;
      } else {
        C = ((C + y) >> 1), D = ((D - x) >> 1);
      }
    }

    if (u >= v) {
      u -= v, A -= C, B -= D;
    } else {
      v -= u, C -= A, D -= B;
    }
  } while (u);

  *a = C, *b = D;

  return result * v;
}

int main() {
  freopen("input.txt", "r", stdin);
  int64_t a, b, c, x, y;
  clock_t begin, end, overall = 0;
  while (scanf("%ld %ld %ld", &a, &b, &c) == 3) {
    printf("----\n");

    begin = clock();
    int64_t gcd1 = RecursiveGCD(a, b);
    int64_t gcd2 = BinaryGCD(a, b);
    int64_t gcd3 = BinaryExtendedGCD(a, b, &x, &y);
    end = clock();
    overall += end - begin;

    assert(gcd1 == gcd2);
    assert(gcd2 == gcd3);
    assert((x * a + y * b) == gcd3);

    printf("GCD(%ld, %ld) = %ld\n", a, b, gcd2);
    printf("%ld * %ld + %ld * %ld = %ld\n", a, x, b, y, gcd3);

    if (c % gcd2) {
      printf("Can't solve equation a * s + b * t = c");
    } else {
      int64_t mult = c / gcd2;
      printf("%ld * %ld + %ld * %ld = %ld\n", a, x * mult, b, y * mult, c);
    }
  }

  printf("Overall time of execution: %.2lf microsecond", ((double) (overall) * 1e6 / (double) (CLOCKS_PER_SEC)));

  return 0;
}

/*
 * Find d - gcd of a,b,
 * Solve equation au+bv=d,
 * Solve equation as+bt=c,
1. a = 363
   b = 108
   c = 9
   Answer:
   d = 3
   u = -11
   v = 37
   s = -33
   t = 111

2. a = 729828
   b = 623466
   c = 11286
   Answer:
   d = 342
   u = -551
   v = 645
   s = -18183
   t = 21285

3. a = 529158829256032
   b = 455995784335360
   c = 106656
   Answer:
   d = 32
   u = -11903440256829
   v = 13813308646271
   s = -39674166376011057
   t = 46039757718021243
 */