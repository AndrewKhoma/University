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
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public class Manager {
  private static final long timeDeltaMillis = 1000;
  private static final int port = 31415;
  private static final int connectionNumber = 2;

  private static ComputationManager compute;
  private static Server server;
  private static List<Pair<ByteBuffer, Future<Integer>>> clientResponse;

  private static boolean calculationsEnabled;

  public static void main(String[] args) throws IOException {
    Runtime.getRuntime().addShutdownHook(new Thread(Manager::quit));

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

    calculationsEnabled = true;
    startComputation(variable, connectionNumber, true);
    // TODO(ahoma): add computation manager as parameter
    // TODO(ahoma): add client functions as variadic parameter
    // TODO(ahoma): rewrite Manager as singleton and add Demonstration class
  }

  private static void startComputation(int value, int clientConnectionNumber, boolean promptEnable)
      throws IOException {
    compute =
        new ComputationManager(
            clientConnectionNumber, 0, (integer, integer2) -> integer * integer2);
    server = Server.open("localhost", port, value, clientConnectionNumber);

    new Client(
        "localhost",
        port,
        x -> {
          try {
            Thread.sleep(4000);
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
          return 42;
        });

    new Client("localhost", port, new FunctionF());

    clientResponse = new ArrayList<>();

    boolean correctResponse;
    Scanner sc = new Scanner(System.in);

    long lastPromptTime = System.currentTimeMillis();
    while (calculationsEnabled) {
      if (promptEnable && (System.currentTimeMillis() - lastPromptTime) > timeDeltaMillis) {
        correctResponse = false;
        System.out.println("Computation process taking too long. Would you like to:");
        while (!correctResponse) {
          System.out.println("(a) continue");
          System.out.println("(b) continue without prompt");
          System.out.println("(c) cancel");
          correctResponse = true;
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
                calculationsEnabled = false;
                break;
              }
            default:
              correctResponse = false;
              System.out.println("Incorrect response: " + line);
          }
        }
      }

      if (!compute.isComputed()) {
        tryToComputeResult();
      }

      if (compute.isComputed()) {
        calculationsEnabled = false;
      }
    }
  }

  private static void interruptCalculation() {
    calculationsEnabled = false;
  }

  private static void tryToComputeResult() {
    if (server.getClientResponse().size() > 0) {
      clientResponse.addAll(server.getAndClearClientResponse());
    }

    for (Pair<ByteBuffer, Future<Integer>> var : clientResponse) {
      if (var.getSecond().isDone() && !var.isChecked()) {
        try {
          var.getSecond().get();
        } catch (InterruptedException e) {
          e.printStackTrace();
          System.out.println("Result computation was interrupted");
        } catch (ExecutionException e) {
          e.printStackTrace();
        }

        compute.add(var.getFirst().getInt(0));
        var.setChecked();
      }
    }
  }

  private static void quit() {
    tryToComputeResult();
    if (compute.isComputed()) System.out.println("Computation result: " + compute.getResult());
    else System.out.println("Computation result is undefined");
  }
}
