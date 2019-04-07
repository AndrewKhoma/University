package org.ahoma;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

/*
 *  Created by ahoma on 04/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

public class Duck extends Thread {
  int x;
  int y;

  private int speedX;
  private int speedY;
  private int width;

  final int sizeX = 70;
  final int sizeY = 60;

  private JLabel duck;
  private GamePanel panel;

  Duck(int newWidth, int newHeight, GamePanel newPanel) {
    super();

    width = newWidth;
    int height = newHeight - newPanel.height * 5 / 12;
    panel = newPanel;

    Random random = new Random();
    int duckType = Math.abs(random.nextInt()) % 2;

    if (duckType == 0) duck = new JLabel(new ImageIcon(getClass().getResource("DuckLR.png")));
    else duck = new JLabel(new ImageIcon(getClass().getResource("DuckRL.png")));

    duck.setSize(new Dimension(sizeX, sizeY));

    speedX = Math.abs(random.nextInt(5)) + 1;
    speedY = -Math.abs(random.nextInt(4)) - 1;
    if (duckType == 1) speedX = -speedX;

    y = height;
    int quarterWidth = width / 4;
    x = width / 2 - quarterWidth / 2 + Math.abs(random.nextInt()) % quarterWidth - 2 * sizeX;
  }

  @Override
  public void run() {
    panel.add(duck);

    boolean flag = true;

    while (!isInterrupted() && flag) {
      int nx = x + speedX;
      int ny = y + speedY;

      if (speedX > 0 && nx > width) flag = false;
      if (speedX < 0 && nx < -sizeX) flag = false;
      if (ny < -sizeY) flag = false;

      x = nx;
      y = ny;
      duck.setLocation(x, y);

      try {
        sleep(20);
      } catch (InterruptedException e) {
        interrupt();
      }
    }

    if (flag) panel.changedCoins(1);
    else panel.changedCoins(-1);

    panel.remove(duck);
    panel.repaint();
    panel.ducks.remove(this);
  }
}
