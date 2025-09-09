#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;
  if (result == NULL || rows < 1 || columns < 1) flag = ERROR_INCORRECT;
  if (flag == OK) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) flag = ERROR_INCORRECT;
  }
  if (flag == OK) {
    for (int i = 0; i < rows && flag == OK; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  if (flag == OK) {
    result->columns = columns;
    result->rows = rows;
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  int err_flag = OK;
  if (right_matrix(A) == ERROR_INCORRECT ||
      right_matrix(B) == ERROR_INCORRECT || B->columns != A->columns ||
      B->rows != A->rows) {
    err_flag = ERROR_INCORRECT;
    flag = FAILURE;
  }

  if (err_flag == OK) {
    for (int i = 0; i < A->rows && flag == SUCCESS; i++) {
      for (int j = 0; j < A->columns && flag == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) flag = FAILURE;
      }
    }
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) || right_matrix(B) || result == NULL)
    flag = ERROR_INCORRECT;
  else if (A->rows != B->rows || A->columns != B->columns)
    flag = ERROR_CALCULATION;
  else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) || right_matrix(B) || result == NULL)
    flag = ERROR_INCORRECT;
  else if (A->rows != B->rows || A->columns != B->columns)
    flag = ERROR_CALCULATION;
  else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) == ERROR_INCORRECT || result == NULL)
    flag = ERROR_INCORRECT;
  else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) || right_matrix(B) || result == NULL)
    flag = ERROR_INCORRECT;
  else if (A->columns != B->rows)
    flag = ERROR_CALCULATION;
  else {
    flag = s21_create_matrix(A->rows, B->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) || result == NULL)
    flag = ERROR_INCORRECT;
  else {
    flag = s21_create_matrix(A->columns, A->rows, result);
    if (flag == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++)
          result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (right_matrix(A) || result == NULL)
    flag = ERROR_INCORRECT;
  else if (A->columns != A->rows)
    flag = ERROR_CALCULATION;
  else if (A->columns == 1) {
    flag = s21_create_matrix(A->rows, A->rows, result);
    if (flag == OK) result->matrix[0][0] = A->matrix[0][0];
  } else {
    flag = s21_create_matrix(A->rows, A->rows, result);
    if (flag == OK) {
      matrix_t minor;
      flag = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      if (flag == OK) {
        double det;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            s21_get_minor_matrix(&minor, A, i, j);
            s21_determinant(&minor, &det);
            result->matrix[i][j] = det * pow(-1, i + j);
          }
        }
        s21_remove_matrix(&minor);
      }
    }
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;
  if (right_matrix(A) || result == NULL)
    flag = ERROR_INCORRECT;
  else if (A->rows != A->columns)
    flag = ERROR_CALCULATION;
  else {
    int n = A->rows;
    if (n == 1)
      *result = A->matrix[0][0];
    else if (n == 2)
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    else {
      int sign = 1;
      *result = 0.0;
      for (int col = 0; col < n; col++) {
        matrix_t minor;
        flag = s21_create_matrix(n - 1, n - 1, &minor);
        if (flag == OK) {
          s21_get_minor_matrix(&minor, A, 0, col);
          double minor_det = 0;
          flag = s21_determinant(&minor, &minor_det);
          if (flag == OK) {
            *result += sign * A->matrix[0][col] * minor_det;
            sign *= -1;
          }
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;
  double det = 0;
  flag = s21_determinant(A, &det);
  if (fabs(det) <= 1e-6 && flag == OK) flag = ERROR_CALCULATION;
  if (flag == OK) {
    matrix_t buf;
    flag = s21_calc_complements(A, &buf);
    if (flag == OK) {
      matrix_t bufT;
      flag = s21_transpose(&buf, &bufT);
      if (flag == OK) {
        flag = s21_mult_number(&bufT, 1 / det, result);
        s21_remove_matrix(&bufT);
      }
      s21_remove_matrix(&buf);
    }
  }
  return flag;
}

//  Support functions

int right_matrix(matrix_t *A) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || A->columns < 1 || A->rows < 1)
    flag = ERROR_INCORRECT;
  if (flag == OK) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] == NULL) flag = ERROR_INCORRECT;
    }
  }
  return flag;
}

void s21_get_minor_matrix(matrix_t *minor, matrix_t *A, int except_I,
                          int except_J) {
  int k = 0, m = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != except_I && j != except_J) {
        minor->matrix[k][m] = A->matrix[i][j];
        m++;
      }
    }
    if (i != except_I) {
      k++;
    }
    m = 0;
  }
}

void s21_filling_matrix(double *nums, matrix_t *A) {
  int count = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = nums[count];
      count++;
    }
  }
}