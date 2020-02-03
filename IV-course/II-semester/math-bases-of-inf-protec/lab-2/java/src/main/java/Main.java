/*
 *  Created by ahoma on 03/02/2020.
 *  Copyright (c) 2020 Andrii Khoma. All rights reserved.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Objects;
import java.util.Scanner;

public class Main {
  static int NUM_ITERATIONS = 100000;

  public static void main(String[] args) {
    File file =
        new File(
            Objects.requireNonNull(
                    Thread.currentThread().getContextClassLoader().getResource("input.txt"))
                .getFile());
    try (Scanner reader = new Scanner(new FileReader(file))) {
      int n = reader.nextInt(), m = reader.nextInt(), num_iter = reader.nextInt();

      float[][] matrix = new float[n][m];
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          matrix[i][j] = reader.nextFloat();
        }
      }

      int vert_size = reader.nextInt();
      float[] vertex = new float[vert_size],
          preLast = new float[vert_size],
          last = new float[vert_size];
      for (int i = 0; i < vert_size; i++) {
        vertex[i] = reader.nextFloat();
      }

      long overall = 0, begin, end;

      float[][] return_value;
      for (int i = 0; i < NUM_ITERATIONS; i++) {
        begin = System.nanoTime();
        return_value = MarkovProcess.DoMarkovProcess(num_iter, matrix, vertex);
        end = System.nanoTime();
        overall += end - begin;

        preLast = return_value[0];
        last = return_value[1];
      }

      System.out.printf(
          "Overall time: %.2f microseconds\n", (double) overall / (double) (NUM_ITERATIONS * 1000));

      for (int i = 0; i < vert_size; i++) {
        System.out.printf("%.5f", preLast[i]);
        if (i + 1 == num_iter) {
          System.out.print("\n");
        } else {
          System.out.print(' ');
        }
      }

      for (int i = 0; i < vert_size; i++) {
        System.out.printf("%.5f", last[i]);
        if (i + 1 == num_iter) {
          System.out.print("\n");
        } else {
          System.out.print(' ');
        }
      }

    } catch (FileNotFoundException e) {
      e.printStackTrace();
    }
  }
}
