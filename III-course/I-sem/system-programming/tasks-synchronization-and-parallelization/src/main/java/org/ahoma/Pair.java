package org.ahoma;
/*
 * Created by ahoma on 09/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

class Pair<K, V> implements Cloneable {

  private final K element0;
  private final V element1;

  private boolean checked;

  static <K, V> Pair<K, V> createPair(K element0, V element1) {
    return new Pair<>(element0, element1);
  }

  private Pair(K element0, V element1) {
    this.element0 = element0;
    this.element1 = element1;
    checked = false;
  }

  boolean isChecked() {
    return checked;
  }

  void setChecked() {
    checked = true;
  }

  K getFirst() {
    return element0;
  }

  V getSecond() {
    return element1;
  }
}
