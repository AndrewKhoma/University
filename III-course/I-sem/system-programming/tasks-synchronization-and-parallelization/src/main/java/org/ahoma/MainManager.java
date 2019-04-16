package org.ahoma;
/*
 * Created by ahoma on 07/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

class MainManager {
  private static final long timeDeltaMillis = 1000;

  private ComputationManager compute;
  private Server server;
  private List<Pair<ByteBuffer, Future<Integer>>> clientResponse;
  private SerializableFunction<Integer, Integer>[] clientFunctions;
  private int serverPort;
  private int clientConnectionNumber;
  private List<Process> clientProcesses;

  private boolean calculationsEnabled;
  private boolean promptEnable;

  @SafeVarargs
  MainManager(
      boolean promptEnable,
      int value,
      int port,
      int clientConnectionNumber,
      ComputationManager computationManager,
      SerializableFunction<Integer, Integer>... clientFunctions) {

    Runtime.getRuntime().addShutdownHook(new Thread(this::quit));
    compute = computationManager;
    compute.resetArgumentNumber(clientConnectionNumber);
    serverPort = port;
    this.clientConnectionNumber = clientConnectionNumber;
    calculationsEnabled = true;
    server = new Server("localhost", port, value, clientConnectionNumber);
    clientResponse = new ArrayList<>();
    assert clientFunctions.length == clientConnectionNumber;
    this.clientFunctions = clientFunctions;
    this.promptEnable = promptEnable;
    clientProcesses = new ArrayList<>();
  }

  void startComputing() {
    try {
      server.startServing();
    } catch (IOException e) {
      e.printStackTrace();
    }

    String classPath =
        Objects.requireNonNull(MainManager.class.getClassLoader().getResource(".")).toString();

    synchronized (this) {
      for (SerializableFunction<Integer, Integer> function : clientFunctions) {
        ClientParameter clientParameter = new ClientParameter("localhost", serverPort, function);
        String clientParamName = "client-param-" + System.currentTimeMillis();

        try {
          clientParameter.serialize(clientParamName);
          ProcessBuilder clientBuilder =
              new ProcessBuilder("java", "-cp", classPath, "org.ahoma.Client", clientParamName);
          Process clientProcess = clientBuilder.start();
          clientProcesses.add(clientProcess);
        } catch (IOException e) {
          e.printStackTrace();
        }
      }
    }

    startInteraction();
  }

  synchronized boolean isClientsSpawned() {
    return server.getConnectionNumber().get() == clientConnectionNumber;
  }

  @SuppressWarnings("StatementWithEmptyBody")
  private void startInteraction() {
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
          while (!sc.hasNextLine()) ;
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

  public synchronized void interruptCalculation() {
    calculationsEnabled = false;
  }

  private void tryToComputeResult() {
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

  private void killAllProcesses() {
    for (Process process : clientProcesses) {
      if (process.isAlive()) process.destroy();
    }
  }

  public synchronized void quit() {
    tryToComputeResult();
    killAllProcesses();
    if (compute.isComputed()) System.out.println("Computation result: " + compute.getResult());
    else System.out.println("Computation result is undefined");
    System.out.flush();
  }
}
