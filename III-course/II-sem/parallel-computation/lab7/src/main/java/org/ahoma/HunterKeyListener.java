package org.ahoma;

/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class HunterKeyListener implements KeyListener {
  private GamePanel panel;

  HunterKeyListener(GamePanel newPanel) {
    panel = newPanel;
  }

  @Override
  public void keyTyped(KeyEvent keyEvent) {}

  @Override
  public void keyPressed(KeyEvent keyEvent) {
    if (panel != null) {

      if (keyEvent.getKeyCode() == 32 && panel.hunter.getCountBullet() < panel.getMaxBullets()) {
        Bullet bullet;
        if (panel.hunter.getSide() == 1)
          bullet =
              new Bullet(panel, panel.hunter, panel.hunter.getX() - 4, panel.hunter.getY() + 80);
        else
          bullet =
              new Bullet(
                  panel,
                  panel.hunter,
                  panel.hunter.getX() + Hunter.sizeX + 4,
                  panel.hunter.getY() + 80);
        bullet.start();
      }

      if (keyEvent.getKeyCode() == KeyEvent.VK_LEFT) {
        panel.hunter.setKeys(true, false);
        if (panel.hunter.getX() > 0) {
          if (panel.hunter.getSide() != 1) {
            panel.hunter.setIcon(new ImageIcon(panel.getClass().getResource("hunterRL.png")));
            panel.hunter.setSide(1);
          }
        }
      } else if (keyEvent.getKeyCode() == KeyEvent.VK_RIGHT) {
        panel.hunter.setKeys(false, true);
        if (panel.hunter.getX() < panel.width - Hunter.sizeX) {
          if (panel.hunter.getSide() != 2) {
            panel.hunter.setIcon(new ImageIcon(panel.getClass().getResource("hunterLR.png")));
            panel.hunter.setSide(2);
          }
        }
      }
    }
  }

  @Override
  public void keyReleased(KeyEvent keyEvent) {
    if (keyEvent.getKeyCode() == KeyEvent.VK_RIGHT) panel.hunter.setKeys(false, false);
    else if (keyEvent.getKeyCode() == KeyEvent.VK_LEFT) panel.hunter.setKeys(false, false);
  }
}
