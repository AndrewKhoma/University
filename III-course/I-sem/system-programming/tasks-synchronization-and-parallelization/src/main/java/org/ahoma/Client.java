package org.ahoma;

/*
 * Created by ahoma on 07/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.channels.CompletionHandler;

class Client {

  private FunctionRunner personalFunction;

  Client(String host, int port, FunctionRunner function) throws IOException {

    personalFunction = function;
    AsynchronousSocketChannel sockChannel = AsynchronousSocketChannel.open();

    // try to connect to the server side
    sockChannel.connect(
        new InetSocketAddress(host, port),
        sockChannel,
        new CompletionHandler<Void, AsynchronousSocketChannel>() {
          @Override
          public void completed(Void result, AsynchronousSocketChannel channel) {
            // start to read message
            startRead(channel);
          }

          @Override
          public void failed(Throwable exc, AsynchronousSocketChannel channel) {
            System.out.println("Failed to connect to server");
          }
        });
  }

  private synchronized void startRead(final AsynchronousSocketChannel sockChannel) {
    final ByteBuffer buf = ByteBuffer.allocate(Constants.BSIZE);
    sockChannel.read(
        buf,
        sockChannel,
        new CompletionHandler<Integer, AsynchronousSocketChannel>() {

          @Override
          public void completed(Integer result, AsynchronousSocketChannel channel) {
            if (result != -1) {
              int variable = buf.getInt(0);
              int computationResult = personalFunction.function(variable);
              startWrite(channel, computationResult);
            }
          }

          @Override
          public void failed(Throwable exc, AsynchronousSocketChannel channel) {
            System.out.println("fail to read message from server");
          }
        });
  }

  private synchronized void startWrite(
      final AsynchronousSocketChannel sockChannel, int compResult) {
    ByteBuffer buf = ByteBuffer.allocate(Constants.BSIZE);
    buf.asIntBuffer().put(compResult);
    sockChannel.write(
        buf,
        sockChannel,
        new CompletionHandler<Integer, AsynchronousSocketChannel>() {
          @Override
          public void completed(Integer result, AsynchronousSocketChannel channel) {
            try {
              channel.close();
            } catch (IOException e) {
              e.printStackTrace();
            }
          }

          @Override
          public void failed(Throwable exc, AsynchronousSocketChannel channel) {
            System.out.println("Fail to write the message to server");
          }
        });
  }
}
