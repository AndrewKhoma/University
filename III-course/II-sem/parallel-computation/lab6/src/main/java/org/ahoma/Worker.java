package org.ahoma;
/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Worker extends Thread {
    private LifeModel lifeModel;
    private CyclicBarrier barrier;
    private ReentrantReadWriteLock locker;
    private byte type;

    Worker(LifeModel lifeModel, CyclicBarrier barrier, ReentrantReadWriteLock locker, byte type) {
        this.lifeModel = lifeModel;
        this.barrier = barrier;
        this.locker = locker;
        this.type = type;
    }

    @Override
    public void run() {
        while (!this.isInterrupted()) {
            locker.readLock().lock();
            lifeModel.simulate(type);
            locker.readLock().unlock();
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                break;
            }
        }
    }
}

