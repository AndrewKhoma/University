package org.ahoma;
/*
 * Created by ahoma on 14/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.util.Scanner;

public class Demonstration {
  public static void main(String[] args) throws IOException {

    String version = System.getProperty("java.version");
    System.out.println(version);

    Scanner sc = new Scanner(System.in);
    int variable = 0;
    boolean correctResponse = false;
    while (!correctResponse) {
      System.out.println("Type x parameter value:");
      correctResponse = true;
      if (sc.hasNextInt()) {
        variable = sc.nextInt();
        sc.nextLine();
      } else {
        correctResponse = false;
        sc.nextLine();
      }
    }

    ComputationManager computationManager =
        new ComputationManager(0, (integer, integer2) -> integer * integer2);
    MainManager mainManager =
        new MainManager(
            true,
            variable,
            3120,
            2,
            computationManager,
            integer -> 42,
            integer -> {
              try {
                Thread.sleep(2000);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return 42;
            });
    mainManager.startComputing();
  }
}
