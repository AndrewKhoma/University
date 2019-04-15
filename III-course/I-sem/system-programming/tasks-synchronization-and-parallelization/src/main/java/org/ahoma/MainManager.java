package org.ahoma;
/*
 * Created by ahoma on 07/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.function.Function;

class MainManager {
  private static final long timeDeltaMillis = 1000;

  private ComputationManager compute;
  private Server server;
  private List<Pair<ByteBuffer, Future<Integer>>> clientResponse;
  private Function<Integer, Integer>[] clientFunctions;
  private int serverPort;

  private boolean calculationsEnabled;
  private boolean promptEnable;
  private boolean clientsSpawned;

  @SafeVarargs
  MainManager(
      boolean promptEnable,
      int value,
      int port,
      int clientConnectionNumber,
      ComputationManager computationManager,
      Function<Integer, Integer>... clientFunctions)
      throws IOException {

    Runtime.getRuntime().addShutdownHook(new Thread(this::quit));
    compute = computationManager;
    compute.resetArgumentNumber(clientConnectionNumber);
    serverPort = port;
    calculationsEnabled = true;
    server = new Server("localhost", port, value, clientConnectionNumber);
    clientResponse = new ArrayList<>();
    assert clientFunctions.length == clientConnectionNumber;
    this.clientFunctions = clientFunctions;
    this.promptEnable = promptEnable;
    clientsSpawned = false;
  }

  void startComputing() {
    try {
      server.startServing();
    } catch (IOException e) {
      e.printStackTrace();
    }

    String classPath =
        Objects.requireNonNull(MainManager.class.getClassLoader().getResource(".")).toString();

    int index = classPath.lastIndexOf("/test/");
    if (index != -1) classPath = classPath.substring(0, index) + "/main/";
    synchronized (this) {
      for (Function<Integer, Integer> function : clientFunctions) {
        ClientParameter clientParameter =
            new ClientParameter(
                "localhost", serverPort, (Function<Integer, Integer> & Serializable) function);
        String clientParamName = "client-param-" + System.currentTimeMillis();

        try {
          clientParameter.serialize(clientParamName);
          ProcessBuilder broker =
              new ProcessBuilder("java", "-cp", classPath, "org.ahoma.Client", clientParamName);
          Process runBroker = broker.start();

          synchronized (System.out) {
            Reader reader = new InputStreamReader(runBroker.getInputStream());
            int ch;
            BufferedWriter writer =
                new BufferedWriter(new FileWriter("test-report-" + System.currentTimeMillis()));
            while ((ch = reader.read()) != -1) writer.write((char) ch);
            reader.close();
            writer.close();
          }

          runBroker.waitFor();

          System.out.println("Program complete");
        } catch (IOException | InterruptedException e) {
          e.printStackTrace();
        }
      }
      clientsSpawned = true;
    }

    startInteraction();
  }

  synchronized boolean isClientsSpawned() {
    return clientsSpawned;
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

  public synchronized void quit() {
    tryToComputeResult();
    if (compute.isComputed()) System.out.println("Computation result: " + compute.getResult());
    else System.out.println("Computation result is undefined");
    System.out.flush();
  }
}
