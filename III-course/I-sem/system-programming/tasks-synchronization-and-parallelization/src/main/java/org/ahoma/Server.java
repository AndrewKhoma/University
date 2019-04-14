package org.ahoma;

/*
 * Created by ahoma on 07/04/2019.
 * Copyright (C) 2019 Andrii Khoma. All rights reserved.
 */

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousServerSocketChannel;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.channels.CompletionHandler;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicInteger;

@SuppressWarnings("SameParameterValue")
class Server {

  private final List<Pair<ByteBuffer, Future<Integer>>> clientResponse;

  Server(String bindAddr, int bindPort, int variable, int connNum) throws IOException {
    InetSocketAddress sockAddr = new InetSocketAddress(bindAddr, bindPort);

    AtomicInteger currConnection = new AtomicInteger(0);
    clientResponse = new ArrayList<>();

    AsynchronousServerSocketChannel serverSock = AsynchronousServerSocketChannel.open();

    serverSock.bind(sockAddr);

    serverSock.accept(
        serverSock,
        new CompletionHandler<AsynchronousSocketChannel, AsynchronousServerSocketChannel>() {

          @Override
          public void completed(
              AsynchronousSocketChannel sockChannel, AsynchronousServerSocketChannel serverSock) {
            if (currConnection.get() < connNum) {
              currConnection.getAndIncrement();
              serverSock.accept(serverSock, this);

              startWrite(sockChannel, variable);
            }
          }

          @Override
          public void failed(Throwable exc, AsynchronousServerSocketChannel serverSock) {
            System.out.println("Fail to accept a connection");
          }
        });
  }

  private void startWrite(AsynchronousSocketChannel sockChannel, final int variable) {
    ByteBuffer buffer = ByteBuffer.allocate(Constants.BSIZE);
    buffer.asIntBuffer().put(variable);

    sockChannel.write(
        buffer,
        sockChannel,
        new CompletionHandler<Integer, AsynchronousSocketChannel>() {

          @Override
          public void completed(Integer result, AsynchronousSocketChannel channel) {
            if (result != -1) {
              startRead(channel);
            }
          }

          @Override
          public void failed(Throwable exc, AsynchronousSocketChannel channel) {
            System.out.println("Fail to write message to client");
          }
        });
  }

  private synchronized void startRead(AsynchronousSocketChannel sockChannel) {
    final ByteBuffer buffer = ByteBuffer.allocate(Constants.BSIZE);
    Future<Integer> readVal = sockChannel.read(buffer);
    clientResponse.add(Pair.createPair(buffer, readVal));
  }

  List<Pair<ByteBuffer, Future<Integer>>> getClientResponse() {
    return clientResponse;
  }

  synchronized List<Pair<ByteBuffer, Future<Integer>>> getAndClearClientResponse() {
    List<Pair<ByteBuffer, Future<Integer>>> result = new ArrayList<>(clientResponse);
    clientResponse.clear();
    assert result.size() != 0;
    return result;
  }
}
