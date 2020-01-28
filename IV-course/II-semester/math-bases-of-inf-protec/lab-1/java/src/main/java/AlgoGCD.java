/*
 *  Created by ahoma on 28/01/2020.
 *  Copyright (c) 2020 Andrii Khoma. All rights reserved.
 */

import org.javatuples.Triplet;

public class AlgoGCD {
  static long RecursiveGCD(long a, long b) throws IllegalArgumentException {
    if (a < 0) {
      a = Math.abs(a);
    }

    if (b < 0) {
      b = Math.abs(b);
    }

    if (a == 0 && b == 0) {
      throw new IllegalArgumentException("A or B should be positive");
    }

    if (a == 0) {
      return b;
    } else if (b == 0) {
      return a;
    }

    if (a == b) {
      return a;
    } else if (a < b) {
      return RecursiveGCD(a, b % a);
    } else {
      return RecursiveGCD(b, a % b);
    }
  }

  static long BinaryGCD(long a, long b) throws IllegalArgumentException {
    a = Math.abs(a);
    b = Math.abs(b);

    if (a == 0 || b == 0) {
      throw new IllegalArgumentException("A and B should be positive");
    }

    if (a < b) {
      // a >= b
      a ^= b;
      b ^= a;
      a ^= b;
    }

    long result = 1;
    while ((a & 1) == 0 && (b & 1) == 0) {
      a >>= 1;
      b >>= 1;
      result <<= 1;
    }

    while (a != 0) {
      while ((a & 1) == 0) a >>= 1;
      while ((b & 1) == 0) b >>= 1;
      long t = Math.abs(a - b) / 2;
      if (a >= b) {
        a = t;
      } else {
        b = t;
      }
    }

    return result * b;
  }

  static Triplet<Long, Long, Long> BinaryExtendedGCD(long a, long b)
      throws IllegalArgumentException {
    a = Math.abs(a);
    b = Math.abs(b);

    if (a == 0 || b == 0) {
      throw new IllegalArgumentException("A and B should be positive");
    }

    long result = 1;
    while ((a & 1) == 0 && (b & 1) == 0) {
      a >>= 1;
      b >>= 1;
      result <<= 1;
    }

    long u = a;
    long v = b;
    long A = 1;
    long B = 0;
    long C = 0;
    long D = 1;

    do {
      while ((u & 1) == 0) {
        u >>= 1;
        if ((A & 1) == 0 && (B & 1) == 0) {
          A >>= 1;
          B >>= 1;
        } else {
          A = ((A + b) >> 1);
          B = ((B - a) >> 1);
        }
      }

      while ((v & 1) == 0) {
        v >>= 1;
        if ((C & 1) == 0 && (D & 1) == 0) {
          C >>= 1;
          D >>= 1;
        } else {
          C = ((C + b) >> 1);
          D = ((D - a) >> 1);
        }
      }

      if (u >= v) {
        u -= v;
        A -= C;
        B -= D;
      } else {
        v -= u;
        C -= A;
        D -= B;
      }
    } while (u == 0);

    return new Triplet<>(C, D, result * v);
  }
}
