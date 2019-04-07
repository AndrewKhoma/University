package org.ahoma;

/*
 *  Created by ahoma on 05/04/2019.
 *  Copyright (c) 2019  Andrii Khoma. All rights reserved.
 */

class LifeModel {

    private byte[][] mainField;
    private byte[][] backField;

    private int width, height;
    private int[][] neighbors;

    LifeModel(int width, int height) {
        this.width = width;
        this.height = height;
        mainField = new byte[height][width];
        backField = new byte[height][width];
        neighbors = new int[][]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    void clear() {
        for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) mainField[i][j] = 0;
    }

    void setCell(int x, int y, byte c) {
        mainField[x][y] = c;
    }

    byte getCell(int x, int y) {
        return mainField[x][y];
    }

    void simulate(byte type) {
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                byte n = countNeighbors(x, y, type);
                backField[x][y] = simulateCell(mainField[x][y], n, type);
            }
        }
    }

    void swapField() {
        byte[][] t = mainField;
        mainField = backField;
        backField = t;
    }

    private byte countNeighbors(int xA, int yA, byte type) {
        byte n = 0;
        for (int i = 0; i < 8; i++) {
            int x = xA + neighbors[i][0];
            int y = yA + neighbors[i][1];
            if (x >= 0 && x < height && y >= 0 && y < width) {
                if (mainField[x][y] == type) n++;
            }
        }
        return n;
    }

    private byte simulateCell(byte self, byte n, byte type) {
        if (self == type && n < 2) return 0;
        if (self == type && (n == 2 || n == 3)) return type;
        if (self == type) return 0;
        if (n == 3) return type;

        return self;
    }
}

