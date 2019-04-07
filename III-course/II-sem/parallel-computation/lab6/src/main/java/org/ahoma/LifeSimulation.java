package org.ahoma;

/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

import javax.swing.*;
import java.awt.*;

public class LifeSimulation extends JFrame {

    private FileDialog fileDialog = null;
    private LifePanel lifePanel;
    private JButton startButton;
    private JButton stopButton;
    private JSlider slider;
    private LifeSimulation amI = this;

    private static final int panelWidth = 50;
    private static final int panelHeight = 25;
    private static final int cellSize = 20;

    private LifeSimulation(String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        lifePanel = new LifePanel();

        lifePanel.initialize(panelWidth, panelHeight, cellSize);
        add(lifePanel);

        JToolBar toolBar = new JToolBar();
        toolBar.setFloatable(false);
        add(toolBar, BorderLayout.NORTH);

        startButton = new JButton("Start");
        toolBar.add(startButton);
        stopButton = new JButton("Stop");
        stopButton.setEnabled(false);
        toolBar.add(stopButton);
        JButton clearFieldButton = new JButton("Clear field");
        toolBar.add(clearFieldButton);
        JButton loadButton = new JButton("Load");
        toolBar.add(loadButton);
        JButton saveButton = new JButton("Save");
        toolBar.add(saveButton);

        slider = new JSlider(1, 10);
        slider.setValue(2);
        lifePanel.setUpdateDelay(slider.getValue());
        slider.addChangeListener(e -> lifePanel.setUpdateDelay(slider.getValue()));

        toolBar.addSeparator();
        toolBar.add(new JLabel(" Fast"));
        toolBar.add(slider);
        toolBar.add(new JLabel("Slow"));

        startButton.addActionListener(
                e -> {
                    lifePanel.startSimulation();
                    startButton.setEnabled(false);
                    stopButton.setEnabled(true);
                });

        stopButton.addActionListener(
                e -> {
                    lifePanel.stopSimulation(startButton);
                    stopButton.setEnabled(false);
                });

        clearFieldButton.addActionListener(
                e -> {
                    synchronized (lifePanel.getLifeModel()) {
                        lifePanel.getLifeModel().clear();
                        lifePanel.repaint();
                    }
                });

        loadButton.addActionListener(
                e -> {
                    fileDialog = new FileDialog(amI, "Load from file", FileDialog.LOAD);
                    fileDialog.setVisible(true);
                    if (fileDialog.getDirectory() != null && fileDialog.getFile() != null) {
                        String name = fileDialog.getDirectory() + fileDialog.getFile();
                        try {
                            lifePanel.download(name);
                        } catch (Exception t) {
                            System.out.println("Incorrect download file");
                        }
                    }
                });

        saveButton.addActionListener(
                e -> {
                    fileDialog = new FileDialog(amI, "Save to file", FileDialog.SAVE);
                    fileDialog.setVisible(true);
                    String name = fileDialog.getDirectory() + fileDialog.getFile();
                    try {
                        lifePanel.save(name);
                    } catch (Exception t) {
                        System.out.println("Can't save to file");
                    }
                });

        startButton.setMaximumSize(new Dimension(100, 50));
        clearFieldButton.setMaximumSize(new Dimension(100, 50));
        stopButton.setMaximumSize(new Dimension(100, 50));
        loadButton.setMaximumSize(new Dimension(100, 50));
        saveButton.setMaximumSize(new Dimension(100, 50));
        slider.setMaximumSize(new Dimension(300, 50));
        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) {
        }

        SwingUtilities.invokeLater(() -> new LifeSimulation("Game of Life"));
    }
}
