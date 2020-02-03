/*
 *  Created by ahoma on 03/02/2020.
 *  Copyright (c) 2020 Andrii Khoma. All rights reserved.
 */

public class MarkovProcess {
  static float[][] DoMarkovProcess(int numIter, float[][] inputMatrix, float[] inputVertex) {
    if (inputMatrix.length != inputMatrix[0].length) {
      throw new IllegalArgumentException("Should be square matrix");
    }

    float[][] res = new float[2][inputVertex.length];

    float[][] cur = new float[inputMatrix.length][inputMatrix.length];
    for (int i = 0; i < inputMatrix.length; i++) {
      cur[i][i] = 1;
    }

    for (int i = 0; i <= numIter; i++) {
      float[][] nextMatrix = MatrixMultiplication(cur, inputMatrix);
      if (i == numIter) {
        res[1] = VertexMatrixMultiplication(inputVertex, cur);
      } else if (i + 1 == numIter) {
        res[0] = VertexMatrixMultiplication(inputVertex, cur);
      }
      cur = nextMatrix;
    }

    return res;
  }

  static float[][] MatrixMultiplication(float[][] lhs, float[][] rhs) {
    if (rhs.length != lhs[0].length) {
      throw new IllegalArgumentException("Can't multiply two matrix");
    }

    float[][] res = new float[lhs.length][rhs[0].length];
    for (int i = 0; i < lhs.length; i++) {
      for (int j = 0; j < rhs[0].length; j++) {
        res[i][j] = 0;
        for (int k = 0; k < rhs.length; k++) {
          res[i][j] += lhs[i][k] * rhs[k][j];
        }
      }
    }

    return res;
  }

  static float[] VertexMatrixMultiplication(float[] lhs, float[][] rhs) {
    if (lhs.length != rhs.length) {
      throw new IllegalArgumentException("Can't multiply vertex on matrix");
    }

    float[] res = new float[rhs[0].length];
    for (int j = 0; j < rhs[0].length; j++) {
      res[j] = 0;
      for (int k = 0; k < lhs.length; k++) {
        res[j] += lhs[k] * rhs[k][j];
      }
    }

    return res;
  }
}
