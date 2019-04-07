package org.ahoma;
/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Checker implements Runnable {
    private LifePanel lifePanel;
    private LifeModel lifeModel;
    private ReentrantReadWriteLock locker;

    int timeSleep = 20;
    private int first;

    Checker(LifePanel lifePanel, LifeModel lifeModel, ReentrantReadWriteLock locker) {
        this.lifePanel = lifePanel;
        this.lifeModel = lifeModel;
        this.locker = locker;
        first = 1;
    }

    @Override
    public void run() {
        if (first == 1) first = 0;
        else {
            locker.writeLock().lock();
            lifeModel.swapField();
            locker.writeLock().unlock();
            lifePanel.repaint();
            try {
                Thread.sleep(timeSleep);
            } catch (InterruptedException e) {
                //
            }
        }
    }
}

