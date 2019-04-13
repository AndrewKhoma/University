package org.ahoma;
/*
 * Created by ahoma on 10/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.BiFunction;

class ComputationManager {
  private BiFunction<Integer, Integer, Integer> function;
  private int argumentsNum;
  private int nowCalculated;
  private int result;
  private int zeroValue;

  private AtomicBoolean startedComputing;
  private AtomicBoolean computed;

  ComputationManager(int argNum, int zeroVal, BiFunction<Integer, Integer, Integer> operation) {
    argumentsNum = argNum;
    zeroValue = zeroVal;
    function = operation;
    startedComputing = new AtomicBoolean(false);
    computed = new AtomicBoolean(false);
  }

  void add(Integer val) {
    if (startedComputing.get()) result = function.apply(result, val);
    else {
      result = val;
      startedComputing.compareAndSet(false, true);
    }

    nowCalculated++;

    if (nowCalculated == argumentsNum) computed.compareAndSet(false, true);
    if (result == zeroValue) computed.compareAndSet(false, true);
  }

  boolean isComputed() {
    return computed.get();
  }

  int getResult() {
    return result;
  }
}
