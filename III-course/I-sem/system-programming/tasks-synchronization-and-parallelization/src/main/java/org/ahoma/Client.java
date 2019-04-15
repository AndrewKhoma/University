package org.ahoma;
/*
 * Created by ahoma on 15/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public class Client {
  private static ClientParameter clientParameter;

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Incorrect usage. Specify client parameter file name");
    }

    System.out.println("client stated");
    Object parameterClass;
    clientParameter = null;
    try {
      System.out.println("Serialization started");
      File inputFile = new File(args[0]);
      System.out.println("Input file " + args[0]);
      ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(inputFile));
      System.out.println("Forming output stream");
      parameterClass = inputStream.readObject();
      System.out.println("Read object");
      clientParameter = (ClientParameter) parameterClass;
    } catch (Exception exc) {
      System.out.println(exc.toString());
      System.out.println("Can't open file Exception");
      System.exit(0);
    } catch (Throwable exc) {
      System.out.println("Can't open file Throwable");
      System.exit(0);
    }

    try {
      startClient();
    } catch (IOException e) {
      System.out.println("Can't create client");
    }
  }

  @SuppressWarnings("StatementWithEmptyBody")
  private static void startClient() throws IOException {
    AsynchronousSocketChannel sockChannel = AsynchronousSocketChannel.open();

    // try to connect to the server side
    Future<Void> isConnected =
        sockChannel.connect(
            new InetSocketAddress(clientParameter.getAddress(), clientParameter.getPort()));

    while (!isConnected.isDone()) ; // Trying to connect to server

    try {
      isConnected.get();
    } catch (InterruptedException | ExecutionException e) {
      e.printStackTrace();
    }

    System.out.println("Connected to server");
    ByteBuffer buffer = ByteBuffer.allocate(Constants.BSIZE);
    Future<Integer> readWrite = sockChannel.read(buffer);

    while (!readWrite.isDone()) ; // Trying to read from server

    System.out.println("Read from server");
    int result = -1;
    try {
      result = readWrite.get();
    } catch (InterruptedException | ExecutionException e) {
      e.printStackTrace();
    }

    int computationResult = 0;
    if (result != -1) {
      int variable = buffer.getInt(0);
      computationResult = clientParameter.getFunction().apply(variable);
    }

    buffer.flip();
    buffer.asIntBuffer().put(computationResult);
    readWrite = sockChannel.write(buffer);

    while (!readWrite.isDone()) ; // Trying to write on server

    try {
      readWrite.get();
    } catch (InterruptedException | ExecutionException e) {
      e.printStackTrace();
    }

    System.out.println("Message sent");
    sockChannel.close();
  }
}
