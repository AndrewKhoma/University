package org.ahoma;

/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class GameMouseAdapter extends MouseAdapter {
  private GamePanel panel;
  private static final int maxRadius = 100;

  GameMouseAdapter(GamePanel newPanel) {
    panel = newPanel;
  }

  @SuppressWarnings("SynchronizationOnLocalVariableOrMethodParameter")
  @Override
  public void mouseReleased(MouseEvent e) {
    int rad = 0;
    if (e.isAltDown()) rad = maxRadius;

    int x = e.getX();
    int y = e.getY();
    for (Duck duck : panel.ducks) {
      synchronized (duck) {
        if (x >= duck.x - rad
            && x <= duck.x + duck.sizeX + rad
            && y >= duck.y - rad
            && y <= duck.y + duck.sizeY + rad) duck.interrupt();
      }
    }
  }
}
