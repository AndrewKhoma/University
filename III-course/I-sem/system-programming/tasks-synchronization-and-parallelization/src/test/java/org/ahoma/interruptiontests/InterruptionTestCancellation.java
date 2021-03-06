package org.ahoma.interruptiontests;
/*
 * Created by ahoma on 14/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import org.ahoma.ComputationManager;
import org.ahoma.TestManagerThread;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;

@Execution(ExecutionMode.SAME_THREAD)
class InterruptionTestCancellation {
  private ComputationManager computationManager;

  private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
  private final PrintStream originalOut = System.out;

  @BeforeEach
  void setup() {
    computationManager = new ComputationManager(0, (integer, integer2) -> integer * integer2);
    System.setOut(new PrintStream(outContent));
  }

  @AfterEach
  void restoreStreams() {
    System.setOut(originalOut);
  }

  @Test
  void fNonZeroGHangs() {
    TestManagerThread testThread =
        new TestManagerThread(
            false,
            5,
            15000,
            2,
            computationManager,
            integer -> 42,
            integer -> {
              try {
                while (!Thread.interrupted()) Thread.sleep(400);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return integer * integer;
            });

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    try {
      while (testThread.notClientsSpawned()) Thread.sleep(20);
      Thread.sleep(100);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    try {
      Thread.sleep(400);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.interruptManager();
    testThread.stopCalculation();

    assertEquals(
        "Function #2 has been canceled\nComputation result is undefined\n", outContent.toString());
  }

  @Test
  void gNonZeroFHangs() {
    TestManagerThread testThread =
        new TestManagerThread(
            false,
            5,
            15001,
            2,
            computationManager,
            integer -> {
              try {
                while (!Thread.interrupted()) Thread.sleep(400);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return integer * integer;
            },
            integer -> 42);

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    try {
      while (testThread.notClientsSpawned()) Thread.sleep(20);
      Thread.sleep(100);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    try {
      Thread.sleep(400);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.interruptManager();
    testThread.stopCalculation();

    assertEquals(
        "Function #1 has been canceled\nComputation result is undefined\n", outContent.toString());
  }
}
