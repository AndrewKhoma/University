package org.ahoma;
/*
 * Created by ahoma on 14/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.util.function.Function;

public class TestManagerThread extends Thread {

  private volatile MainManager mainManager;

  @SafeVarargs
  public TestManagerThread(
      boolean promptEnable,
      int newValue,
      int newPort,
      int clientConnectionNumber,
      ComputationManager computationManager,
      Function<Integer, Integer>... clientFunctions) {
    try {
      mainManager =
          new MainManager(
              promptEnable,
              newValue,
              newPort,
              clientConnectionNumber,
              computationManager,
              clientFunctions);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  @Override
  public void run() {
    mainManager.startComputing();
  }

  public synchronized void interruptManager() {
    mainManager.interruptCalculation();
  }

  public synchronized boolean clientsSpawned() {
    return mainManager.isClientsSpawned();
  }

  public synchronized void stopCalculation() {
    mainManager.quit();
  }
}
