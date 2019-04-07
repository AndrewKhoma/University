package org.ahoma;

import javax.swing.*;
import java.awt.*;
import java.util.concurrent.ConcurrentLinkedQueue;

/*
 *  Created by ahoma on 04/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

public class GamePanel extends JPanel {
  int width;
  int height;

  private int coins = 0;
  private int maxCoins = 0;
  private JLabel score;
  private JLabel bestScore;
  private ImageIcon background = new ImageIcon(getClass().getResource("background.png"));
  private final int minimumDucks = 2;
  private static final int maxBullets = 5;
  private int maxDucks = minimumDucks;

  ConcurrentLinkedQueue<Duck> ducks = new ConcurrentLinkedQueue<>();

  Hunter hunter = null;
  GameCreator gameCreator;

  GamePanel(GameCreator gameCreator) {
    setBackground(Color.WHITE);
    this.gameCreator = gameCreator;
    width = gameCreator.getWidth();
    height = gameCreator.getHeight();

    // field editor
    setLayout(null);
    setSize(width, height);

    score = new JLabel("Score: 0");
    score.setVisible(true);
    score.setFont(new Font("Serif", Font.PLAIN, 22));
    score.setSize(200, 100);
    score.setLocation(5, height - 120);
    this.add(score);

    bestScore = new JLabel("Best Score: 0");
    bestScore.setVisible(true);
    bestScore.setFont(new Font("Serif", Font.PLAIN, 22));
    bestScore.setSize(200, 100);
    bestScore.setLocation(5, height - 100);
    this.add(bestScore);

    Toolkit toolkit = Toolkit.getDefaultToolkit();
    Image image = toolkit.getImage(getClass().getResource("sight.png"));
    Cursor c =
        toolkit.createCustomCursor(image, new Point(getX() + 14, getY() + 14), "breech-sight");
    setCursor(c);

    GameMouseAdapter myMouseAdapter = new GameMouseAdapter(this);
    addMouseListener(myMouseAdapter);

    GameRunner game = new GameRunner(this);
    game.start();
  }

  synchronized int getMaxDucks() {
    return maxDucks;
  }

  synchronized int getMaxBullets() {
    return maxBullets;
  }

  synchronized void changedCoins(int d) {
    coins += d;
    if (coins < 0) coins = 0;
    if (maxCoins < coins) maxCoins = coins;

    int coinsLog2 = (int) Math.floor(Math.log(coins) / Math.log(2.0)),
        anotherCoins = (int) Math.pow(2.0, coinsLog2);

    if (anotherCoins == coins) maxDucks = coinsLog2;
    if (maxDucks < minimumDucks) maxDucks = minimumDucks;

    score.setText("Score: " + coins);
    bestScore.setText("Best Score: " + maxCoins);
  }

  @Override
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    g.drawImage(background.getImage(), 0, 0, width, height, null);
  }

  @Override
  public Dimension getPreferredSize() {
    return new Dimension(width, height);
  }

  @Override
  public Dimension getMinimumSize() {
    return new Dimension(width, height);
  }

  @Override
  public Dimension getMaximumSize() {
    return new Dimension(width, height);
  }
}
