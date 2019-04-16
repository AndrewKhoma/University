package org.ahoma;
/*
 * Created by ahoma on 14/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

public class TestManagerThread extends Thread {

  private volatile MainManager mainManager;

  @SafeVarargs
  public TestManagerThread(
      boolean promptEnable,
      int newValue,
      int newPort,
      int clientConnectionNumber,
      ComputationManager computationManager,
      SerializableFunction<Integer, Integer>... clientFunctions) {
    mainManager =
        new MainManager(
            promptEnable,
            newValue,
            newPort,
            clientConnectionNumber,
            computationManager,
            clientFunctions);
  }

  @Override
  public void run() {
    mainManager.startComputing();
  }

  public synchronized void interruptManager() {
    mainManager.interruptCalculation();
  }

  public synchronized boolean notClientsSpawned() {
    return !mainManager.isClientsSpawned();
  }

  public synchronized void stopCalculation() {
    mainManager.quit();
  }
}
