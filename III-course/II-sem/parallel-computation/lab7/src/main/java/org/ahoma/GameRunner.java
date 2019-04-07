package org.ahoma;
/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

public class GameRunner extends Thread {
  private GamePanel panel;

  GameRunner(GamePanel newPanel) {
    panel = newPanel;
  }

  @Override
  public void run() {
    if (panel.hunter == null) {
      panel.hunter = new Hunter(panel.gameCreator, panel);
      panel.hunter.start();
    }

    while (!isInterrupted()) {
      if (panel.ducks.size() < panel.getMaxDucks()) {
        Duck duck = new Duck(panel.width, panel.height, panel);
        panel.ducks.add(duck);
        duck.start();
      }
      try {
        sleep(200);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
