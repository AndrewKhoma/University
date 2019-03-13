package org.Ahoma;

import javafx.scene.control.Slider;

class ConcurrentValue {
  private Slider slider;

  private Thread threadDecrease;
  private Thread threadIncrease;

  private volatile int semaphore;

  private volatile boolean decIsRunning;
  private volatile boolean incIsRunning;

  ConcurrentValue(Slider s) {
    slider = s;
    semaphore = 0;
    decIsRunning = true;
    incIsRunning = true;
  }

  void setSemaphore(int value) {
    semaphore = value;
  }

  int getSemaphore() {
    return semaphore;
  }

  void setPriorityToInc(int priority) {
    threadIncrease.setPriority(priority);
  }

  void setPriorityToDec(int priority) {
    threadDecrease.setPriority(priority);
  }

  void setDecIsRunning(boolean value) {
    decIsRunning = value;
  }

  void setIncIsRunning(boolean value) {
    incIsRunning = value;
    if (!incIsRunning) threadIncrease.interrupt();
  }

  void startDec() {
    threadDecrease =
        new Thread(
            () -> {
              while (decIsRunning) {
                slider.setValue(10.0);
              }
            });
    threadDecrease.setDaemon(true);
    threadDecrease.start();
  }

  void startInc() {
    threadIncrease =
        new Thread(
            () -> {
              while (incIsRunning) {
                slider.setValue(90);
              }
            });
    threadIncrease.setDaemon(true);
    threadIncrease.start();
  }
}
