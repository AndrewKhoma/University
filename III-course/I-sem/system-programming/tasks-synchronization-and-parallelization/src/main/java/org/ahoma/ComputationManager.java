package org.ahoma;
/*
 * Created by ahoma on 10/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.BiFunction;

public class ComputationManager {
  private BiFunction<Integer, Integer, Integer> function;
  private int argumentsNum;
  private int nowCalculated;
  private int result;
  private int zeroValue;

  private AtomicBoolean startedComputing;
  private AtomicBoolean computed;

  public ComputationManager(int zeroVal, BiFunction<Integer, Integer, Integer> operation) {
    zeroValue = zeroVal;
    function = operation;
    nowCalculated = 0;
    startedComputing = new AtomicBoolean(false);
    computed = new AtomicBoolean(false);
  }

  ComputationManager(int argNum, int zeroVal, BiFunction<Integer, Integer, Integer> operation) {
    this(zeroVal, operation);
    argumentsNum = argNum;
  }

  synchronized void resetArgumentNumber(int newArgNum) {
    argumentsNum = newArgNum;
    nowCalculated = 0;
    startedComputing.set(false);
    computed.set(false);
  }

  synchronized void add(Integer val) {
    if (startedComputing.get()) result = function.apply(result, val);
    else {
      result = val;
      startedComputing.compareAndSet(false, true);
    }

    nowCalculated++;

    if (nowCalculated == argumentsNum) computed.compareAndSet(false, true);
    if (result == zeroValue) computed.compareAndSet(false, true);
  }

  public synchronized boolean isComputed() {
    return computed.get();
  }

  public synchronized int getResult() {
    return result;
  }

  public synchronized int getNowCalculated() {
    return nowCalculated;
  }

  public synchronized int getZeroValue() {
    return zeroValue;
  }
}
