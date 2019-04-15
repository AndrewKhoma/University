package org.ahoma;
/*
 * Created by ahoma on 15/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.*;
import java.util.function.Function;

class ClientParameter implements Serializable {
  private Function<Integer, Integer> function;
  private String address;
  private int port;

  ClientParameter(String address, int port, Function<Integer, Integer> function) {
    this.function = function;
    this.address = address;
    this.port = port;
  }

  void changeAddress(String address) {
    this.address = address;
  }

  void changePort(int port) {
    this.port = port;
  }

  void changeFunction(Function<Integer, Integer> function) {
    this.function = function;
  }

  String getAddress() {
    return address;
  }

  int getPort() {
    return port;
  }

  Function<Integer, Integer> getFunction() {
    return function;
  }

  @SuppressWarnings("ResultOfMethodCallIgnored")
  void serialize(String outputPath) throws IOException {
    File outputFile = new File(outputPath);
    if (!outputFile.exists()) {
      outputFile.createNewFile();
    }

    try (ObjectOutputStream outputStream =
        new ObjectOutputStream(new FileOutputStream(outputFile))) {
      outputStream.writeObject(this);
    }
  }
}
