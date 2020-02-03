#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

const int kNumIter = 100000;

typedef struct matrix {
  int dim1, dim2;
  float **value;
} matrix;

typedef struct hor_vert {
  int size;
  float *value;
} hor_vert;

matrix CreateMatrix(int dim1, int dim2, float default_value) {
  matrix result;
  result.dim1 = dim1, result.dim2 = dim2;

  result.value = (float **) calloc(dim1, sizeof(float *));
  for (int i = 0; i < dim1; i++) {
    result.value[i] = (float *) calloc(dim2, sizeof(float));
    for (int j = 0; j < dim2; j++) {
      result.value[i][j] = default_value;
    }
  }
  return result;
}

hor_vert CreateVertex(int size, float default_value) {
  hor_vert result;
  result.size = size;
  result.value = (float *) calloc(size, sizeof(float));
  for (int i = 0; i < size; i++) {
    result.value[i] = default_value;
  }
  return result;
}

void MatrixMultiplication(const matrix *matrix1, const matrix *matrix2, matrix *result) {
  assert(matrix1->dim2 == matrix2->dim1);
  assert(matrix1->dim1 == result->dim1);
  assert(matrix2->dim2 == result->dim2);

  for (int i = 0; i < matrix1->dim1; i++) {
    for (int j = 0; j < matrix2->dim2; j++) {
      result->value[i][j] = 0;
      for (int k = 0; k < matrix1->dim2; k++) {
        result->value[i][j] += matrix1->value[i][k] * matrix2->value[k][j];
      }
    }
  }
}

void PrintMatrix(const matrix *matrix1) {
  printf("\n");
  for (int i = 0; i < matrix1->dim1; i++) {
    for (int j = 0; j < matrix1->dim2; j++) {
      printf("%.4f ", matrix1->value[i][j]);
    }
    printf("\n");
  }
}

void VertexMatrixMultiplication(const hor_vert *vert, const matrix *matrix1, hor_vert *result) {
  assert(vert->size == matrix1->dim1);
  assert(matrix1->dim2 == result->size);

  for (int j = 0; j < matrix1->dim2; j++) {
    result->value[j] = 0;
    for (int k = 0; k < matrix1->dim1; k++) {
      result->value[j] += vert->value[k] * matrix1->value[k][j];
    }
  }
}

void CopyMatrix(const matrix *source, matrix *destination) {
  assert(source->dim1 == destination->dim1);
  assert(source->dim2 == destination->dim2);

  for (int i = 0; i < source->dim1; i++) {
    for (int j = 0; j < source->dim2; j++) {
      destination->value[i][j] = source->value[i][j];
    }
  }
}

void DoMarkovCalculation(int iter, const matrix *inp_matrix, const hor_vert *vert, hor_vert *pre_last, hor_vert *last) {
  matrix current = CreateMatrix(inp_matrix->dim1, inp_matrix->dim2, 0.0),
      next = CreateMatrix(inp_matrix->dim1, inp_matrix->dim2, 0.0);
  assert(inp_matrix->dim1 == inp_matrix->dim2);

  for (int i = 0; i < current.dim1; i++) {
    current.value[i][i] = 1;
  }

  for (int i = 0; i <= iter; i++) {
    MatrixMultiplication(&current, inp_matrix, &next);
    if (i == iter) {
      VertexMatrixMultiplication(vert, &current, last);
    } else if (i + 1 == iter) {
      VertexMatrixMultiplication(vert, &current, pre_last);
    }
    CopyMatrix(&next, &current);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m, num_iter;
  scanf("%d%d%d", &n, &m, &num_iter);

  matrix starting_matrix = CreateMatrix(n, m, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%f", &starting_matrix.value[i][j]);
    }
  }

  scanf("%d", &n);

  hor_vert starting_vert = CreateVertex(n, 0);
  for (int i = 0; i < n; i++) {
    scanf("%f", &starting_vert.value[i]);
  }

  clock_t start, end, overall = 0;
  hor_vert pre_last = CreateVertex(n, 0), last = CreateVertex(n, 0);

  for (int i = 0; i < kNumIter; i++) {
    start = clock();
    DoMarkovCalculation(num_iter, &starting_matrix, &starting_vert, &pre_last, &last);
    end = clock();
    overall += end - start;
  }

  printf("Overall time: %.2lf microsecond\n",
         (double) overall * 1e6 / ((double) (CLOCKS_PER_SEC) * (double) kNumIter));

  printf("p_%d:\n", num_iter - 1);
  for (int i = 0; i < starting_vert.size; i++) {
    printf("%.5f ", pre_last.value[i]);
  }

  printf("\np_%d:\n", num_iter);
  for (int i = 0; i < starting_vert.size; i++) {
    printf("%.5f ", last.value[i]);
  }

  return 0;
}
