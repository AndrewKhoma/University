package org.ahoma.periodicprompttests;
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

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;

@Execution(ExecutionMode.CONCURRENT)
class PeriodicPromptTest {
  private ComputationManager computationManager;

  private ByteArrayInputStream inContent;
  private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
  private final InputStream originalIn = System.in;
  private final PrintStream originalOut = System.out;

  @BeforeEach
  void setup() {
    computationManager = new ComputationManager(0, (integer, integer2) -> integer * integer2);
    System.setOut(new PrintStream(outContent));
  }

  void systemIn(String input) {
    inContent = new ByteArrayInputStream(input.getBytes());
    System.setIn(inContent);
  }

  @AfterEach
  void restoreStreams() {
    System.setIn(originalIn);
    System.setOut(originalOut);
  }

  @Test
  void computationsBeforeFirstPrompt() {
    TestManagerThread testThread =
        new TestManagerThread(true, 5, 20000, 2, computationManager, integer -> 42, integer -> 2);

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    try {
      Thread.sleep(100);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(2, computationManager.getNowCalculated());
    assertTrue(computationManager.isComputed());

    testThread.stopCalculation();

    assertEquals("Computation result: 84\n", outContent.toString());
  }

  @Test
  void finishesDuringPrompt() {
    TestManagerThread testThread =
        new TestManagerThread(
            true,
            5,
            20001,
            2,
            computationManager,
            integer -> {
              try {
                Thread.sleep(1100);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return 42;
            },
            integer -> {
              try {
                Thread.sleep(1100);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return 2;
            });

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    systemIn("c");

    try {
      Thread.sleep(2300);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    assertEquals(
        "Computation process taking too long. Would you like to:\n"
            + "(a) continue\n"
            + "(b) continue without prompt\n"
            + "(c) cancel\n",
        outContent.toString());

    outContent.reset();

    testThread.stopCalculation();

    assertEquals(2, computationManager.getNowCalculated());
    assertTrue(computationManager.isComputed());

    assertEquals("Computation result: 84\n", outContent.toString());
  }

  @Test
  void fFinishesNonZeroGHangsContinuePrompt() {
    TestManagerThread testThread =
        new TestManagerThread(
            true,
            5,
            20002,
            2,
            computationManager,
            integer -> 42,
            integer -> {
              try {
                while (!Thread.interrupted()) Thread.sleep(100);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return 2;
            });

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    for (int tests = 0; tests < 2; tests++) {
      systemIn("a\n");
      inContent.reset();

      try {
        Thread.sleep(1200);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      assertEquals(1, computationManager.getNowCalculated());
      assertFalse(computationManager.isComputed());

      assertEquals(
          "Computation process taking too long. Would you like to:\n"
              + "(a) continue\n"
              + "(b) continue without prompt\n"
              + "(c) cancel\n",
          outContent.toString());

      outContent.reset();
    }

    testThread.stopCalculation();

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    assertEquals("Computation result is undefined\n", outContent.toString());
  }

  @Test
  void fFinishesNonZeroGHangsWithoutPrompt() {
    TestManagerThread testThread =
        new TestManagerThread(
            true,
            5,
            20003,
            2,
            computationManager,
            integer -> 42,
            integer -> {
              try {
                while (!Thread.interrupted()) Thread.sleep(100);
              } catch (InterruptedException e) {
                e.printStackTrace();
              }
              return 2;
            });

    assertEquals(0, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    testThread.start();

    for (int tests = 0; tests < 5; tests++) {
      if (tests == 0) {
        systemIn("b\n");
        inContent.reset();
      }

      try {
        Thread.sleep(1100);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      assertEquals(1, computationManager.getNowCalculated());
      assertFalse(computationManager.isComputed());

      if (tests == 0) {
        assertEquals(
            "Computation process taking too long. Would you like to:\n"
                + "(a) continue\n"
                + "(b) continue without prompt\n"
                + "(c) cancel\n",
            outContent.toString());
      } else {
        assertEquals("", outContent.toString());
      }

      outContent.reset();
    }

    testThread.stopCalculation();

    assertEquals(1, computationManager.getNowCalculated());
    assertFalse(computationManager.isComputed());

    assertEquals("Computation result is undefined\n", outContent.toString());
  }
}
