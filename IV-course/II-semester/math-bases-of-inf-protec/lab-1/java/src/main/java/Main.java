/*
 *  Created by ahoma on 28/01/2020.
 *  Copyright (c) 2020 Andrii Khoma. All rights reserved.
 */

import org.javatuples.Triplet;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    File file =
        new File(
            Objects.requireNonNull(
                    Thread.currentThread().getContextClassLoader().getResource("input.txt"))
                .getFile());

    try (Scanner reader = new Scanner(new FileReader(file))) {
      long overallTime = 0;
      long timeStart, timeEnd;
      long gcd1, gcd2, gcd3, x, y;
      Triplet<Long, Long, Long> result;

      while (reader.hasNextLine()) {
        try {
          long a = reader.nextLong();
          long b = reader.nextLong();
          long c = reader.nextLong();

          timeStart = System.nanoTime();
          gcd1 = AlgoGCD.RecursiveGCD(a, b);
          gcd2 = AlgoGCD.BinaryGCD(a, b);
          result = AlgoGCD.BinaryExtendedGCD(a, b);
          timeEnd = System.nanoTime();

          overallTime += timeEnd - timeStart;

          x = result.getValue0();
          y = result.getValue1();
          gcd3 = result.getValue2();

          assert (gcd1 == gcd2);
          assert (gcd2 == gcd3);
          assert (a * x + b * y == gcd3);

          System.out.printf("GCD(%d, %d) = %d\n", a, b, gcd2);
          System.out.printf("%d * %d + %d * %d = %d\n", a, x, b, y, gcd3);

          if (c % gcd2 != 0) {
            System.out.println("Can't solve equation a * s + b * t = c");
          } else {
            long mult = c / gcd2;
            System.out.printf("%d * %d + %d * %d = %d\n", a, x * mult, b, y * mult, c);
          }
        } catch (IllegalArgumentException e) {
          System.out.println("Couldn't calculate GCD because " + e.getMessage());
          e.printStackTrace();
        }
      }

      System.out.printf("Overall time of execution: %d microseconds", overallTime / 1000);

    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
