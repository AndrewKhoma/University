package org.ahoma;
/*
 * Created by ahoma on 07/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Future;

public class Manager {
  private static final long timeDeltaMillis = 1000;
  private static final int port = 31415;
  private static final int connectionNumber = 2;

  private static ComputationProcess compute;
  private static Server server;
  private static List<Pair<ByteBuffer, Future<Integer>>> clientResponse;

  public static void main(String[] args) throws IOException {
    Runtime.getRuntime().addShutdownHook(new Thread(Manager::quit));

    Scanner sc = new Scanner(System.in);
    int variable = 0;
    boolean correctResponce = false;
    while (!correctResponce) {
      System.out.println("Type x parameter value:");
      correctResponce = true;
      if (sc.hasNextInt()) {
        variable = sc.nextInt();
        sc.nextLine();
      } else {
        correctResponce = false;
        sc.nextLine();
      }
    }

    compute =
        new ComputationProcess(connectionNumber, 0, (integer, integer2) -> integer & integer2);
    server = Server.open("localhost", port, variable, connectionNumber);

    new Client("localhost", port, x -> 42);

    new Client("localhost", port, new FuncitonF());

    boolean promptEnable = true;
    long lastPromptTime = System.currentTimeMillis();
    clientResponse = new ArrayList<>();

    while (true) {
      if (!compute.isComputed()) {
        tryToCompute();
      }

      if (compute.isComputed()) {
        System.exit(0);
      }

      if (promptEnable && (System.currentTimeMillis() - lastPromptTime) > timeDeltaMillis) {
        correctResponce = false;
        System.out.println("Computation process taking too long. Would you like to:");
        while (!correctResponce) {
          System.out.println("(a) continue");
          System.out.println("(b) continue without prompt");
          System.out.println("(c) cancel");
          correctResponce = true;
          String line = sc.nextLine().toLowerCase();
          switch (line) {
            case "a":
              {
                lastPromptTime = System.currentTimeMillis();
                break;
              }
            case "b":
              {
                promptEnable = false;
                break;
              }
            case "c":
              {
                System.exit(0);
                break;
              }
            default:
              correctResponce = false;
              System.out.println("Incorrect response: " + line);
          }
        }
      }
    }
  }

  private static void tryToCompute() {
    if (server.getClientResponce().size() > 0) {
      clientResponse.addAll(server.getAndClearClientResponce());
    }

    for (Pair<ByteBuffer, Future<Integer>> var : clientResponse) {
      if (var.getSecond().isDone() && !var.isChecked()) {
        compute.add(var.getFirst().getInt(0));
        var.setChecked();
      }
    }
  }

  private static void quit() {
    tryToCompute();
    if (compute.isComputed()) System.out.println("Computation result: " + compute.getResult());
    else System.out.println("Computation result is undefined");
  }
}
