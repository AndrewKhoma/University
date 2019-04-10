package org.ahoma;
/*
 * Created by ahoma on 10/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.util.function.BiFunction;

class ComputationProcess {
  private BiFunction<Integer, Integer, Integer> function;
  private int argumentsNum;
  private int nowCalculated;
  private int result;
  private int zeroValue;

  private boolean startedComputing;
  private boolean computed;

  ComputationProcess(int argNum, int zeroVal, BiFunction<Integer, Integer, Integer> operation) {
    argumentsNum = argNum;
    zeroValue = zeroVal;
    function = operation;
    startedComputing = false;
    computed = false;
  }

  void add(Integer val) {
    if (startedComputing) result = function.apply(result, val);
    else result = val;

    nowCalculated++;

    if (nowCalculated == argumentsNum) computed = true;
    if (result == zeroValue) computed = true;
  }

  boolean isComputed() {
    return computed;
  }

  int getResult() {
    return result;
  }
}
