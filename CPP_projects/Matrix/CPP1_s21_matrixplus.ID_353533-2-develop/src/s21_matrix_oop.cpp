#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows > 0 && cols > 0) {
    matrix_ = new double *[getRows()];
    for (int i = 0; i < getRows(); ++i) {
      matrix_[i] = new double[getCols()];
      for (int j = 0; j < getCols(); ++j) {
        matrix_[i][j] = 0;
      }
    }
  } else
    throw std::length_error("Matrix size must be greater than 0");
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[this->rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_];
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

int S21Matrix::getCols() { return cols_; }

int S21Matrix::getRows() { return rows_; }

void S21Matrix::setRows(int new_rows) {
  if (new_rows < 1)
    throw std::length_error("Matrix size must be greater than 0");
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    int min = std::min(rows_, new_rows);
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = tmp;
  }
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols < 1)
    throw std::length_error("Matrix size must be greater than 0");
  if (new_cols != cols_) {
    S21Matrix tmp(rows_, new_cols);
    int min = std::min(cols_, new_cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool flag = true;
  if (!this->isValid() || !other.isValid() || rows_ != other.rows_ ||
      cols_ != other.rows_)
    flag = false;
  if (flag) {
    for (int i = 0; i < rows_ && flag; i++) {
      for (int j = 0; j < cols_ && flag; j++) {
        if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = false;
        }
      }
    }
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!this->isValid() || !other.isValid()) {
    throw std::logic_error("invalid matrix");
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrix dimensions must be equal");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!this->isValid() || !other.isValid()) {
    throw std::logic_error("invalid matrix");
  }
  if (rows_ != other.rows_ || cols_ != other.rows_) {
    throw std::logic_error("Matrix dimensions must be equal");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (this->isValid()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (!this->isValid() || !other.isValid()) {
    throw std::logic_error("invalid matrix");
  }
  if (cols_ != other.rows_) {
    throw std::logic_error("matrix A columns must be equal to matrix B rows");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        res(i, j) += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
  *this = std::move(res);
}

S21Matrix S21Matrix::Transpose() {
  if (!this->isValid()) {
    throw std::logic_error("invalid matrix");
  }
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed(j, i) = matrix_[i][j];
    }
  }
  return transposed;
}

double S21Matrix::Determinant() {
  if (!this->isValid()) throw std::logic_error("invalid matrix");
  if (rows_ != cols_)
    throw std::logic_error(
        "To get Determinant matrix dimensions must be equal");
  double result;
  int n = rows_;
  if (n == 1)
    result = matrix_[0][0];
  else if (n == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    int sign = 1;
    result = 0.0;
    for (int col = 0; col < n; col++) {
      S21Matrix minor = GetMinor(0, col);
      double minor_det = minor.Determinant();
      result += sign * matrix_[0][col] * minor_det;
      sign *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!this->isValid()) throw std::logic_error("invalid matrix");
  if (rows_ != cols_) throw std::logic_error("Matrix dimensions must be equal");

  S21Matrix result(rows_, cols_);

  if (rows_ == 1)
    result(0, 0) = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = this->GetMinor(i, j);
        double calc = minor.Determinant();
        if ((i + j) % 2 != 0) {
          calc *= -1;
        }
        result(i, j) = calc;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!this->isValid()) {
    throw std::logic_error("invalid matrix");
  }
  double determinant = Determinant();
  if (std::fabs(determinant) < 1e-7) {
    throw std::logic_error("Determinant must be non-zero");
  }
  S21Matrix temp_calc = CalcComplements();
  S21Matrix result = temp_calc.Transpose();
  result *= (1 / determinant);
  return result;
}

S21Matrix S21Matrix::GetMinor(const int row_s, const int col_s) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int m_r = 0;
  for (int i = 0; i < rows_; i++) {
    int m_col = 0;
    if (i != row_s) {
      for (int j = 0; j < cols_; j++) {
        if (j != col_s) {
          minor(m_r, m_col) = matrix_[i][j];
          m_col++;
        }
      }
      m_r++;
    }
  }
  return minor;
}

bool S21Matrix::isValid() const {
  return matrix_ != nullptr && cols_ > 0 && rows_ > 0;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result = (*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result = (*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) {
  S21Matrix result = (*this);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result = (*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (!other.isValid()) {
    throw std::logic_error("invalid matrix");
  }
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] this->matrix_;
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if ((row < 0 || row > getRows() - 1) || (col < 0 || col > getCols() - 1)) {
    throw std::logic_error("invalid parameters");
  }
  return matrix_[row][col];
}