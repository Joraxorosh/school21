#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iostream>

#include "s21_matrix_oop.h"

TEST(CreateMatrix, StandartConstructor) {
  S21Matrix matrix_a;
  ASSERT_TRUE(matrix_a.getCols() == 0);
  ASSERT_TRUE(matrix_a.getRows() == 0);
}

TEST(CreateMatrix, ParamConstr) {
  S21Matrix matrix_a(2, 2);
  ASSERT_TRUE(matrix_a.getCols() == 2);
  ASSERT_TRUE(matrix_a.getRows() == 2);
}

TEST(CreateMatrix, ParamConstWithWrongSizes) {
  EXPECT_THROW(S21Matrix matrix(-1, 2), std::length_error);
}

TEST(CreateMatrix, MoveConstr1) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b = std::move(matrix_a));
}

TEST(CreateMatrix, MoveConstr2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b = std::move(matrix_a);
  ASSERT_TRUE(matrix_b.getCols() == 2);
  ASSERT_TRUE(matrix_b.getRows() == 2);
}

TEST(CreateMatrix, MoveConstr3) {
  auto test1 = S21Matrix(3, 3);
  test1(1, 1) = 5;
  auto test2 = S21Matrix(test1);
  auto test3 = S21Matrix(std::move(test1));
  EXPECT_EQ(test2, test3);
}

TEST(CreateMatrix, CopyConstr1) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b(matrix_a));
}

TEST(CreateMatrix, CopyConstr2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(matrix_a);
  ASSERT_TRUE(matrix_b.getCols() == 2);
  ASSERT_TRUE(matrix_b.getRows() == 2);
  ASSERT_TRUE(matrix_b(0, 0) == matrix_a(0, 0));
  ASSERT_TRUE(matrix_b(1, 0) == matrix_a(1, 0));
  ASSERT_TRUE(matrix_b(1, 1) == matrix_a(1, 1));
  ASSERT_TRUE(matrix_b(0, 1) == matrix_a(0, 1));
}

TEST(CreateMatrix, CopyConstr3) {
  S21Matrix test = S21Matrix(3, 3);
  test(0, 0) = 1;
  S21Matrix temp(test);
  EXPECT_EQ(test, temp);
}

TEST(Accessors_and_mutators, GetCols) {
  S21Matrix test1 = S21Matrix();
  EXPECT_EQ(test1.getCols(), 0);

  S21Matrix test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.getCols(), 2);

  S21Matrix test3 = S21Matrix(4, 3);
  EXPECT_EQ(test3.getCols(), 3);

  S21Matrix test4 = S21Matrix(4, 111);
  EXPECT_EQ(test4.getCols(), 111);
}

TEST(Accessors_and_mutators, GetRows) {
  S21Matrix test1 = S21Matrix();
  EXPECT_EQ(test1.getRows(), 0);

  S21Matrix test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.getRows(), 2);

  S21Matrix test3 = S21Matrix(4, 3);
  EXPECT_EQ(test3.getRows(), 4);

  S21Matrix test4 = S21Matrix(123, 111);
  EXPECT_EQ(test4.getRows(), 123);
}

TEST(Accessors_and_mutators, SetCols) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1.setCols(5);
  EXPECT_EQ(test1.getCols(), 5);

  S21Matrix test2 = S21Matrix(1, 1);
  test2.setCols(1);
  EXPECT_EQ(test2.getCols(), 1);

  S21Matrix test3 = S21Matrix(1, 1);
  test3.setCols(99);
  EXPECT_EQ(test3.getCols(), 99);

  S21Matrix test4 = S21Matrix(1, 1);
  EXPECT_THROW(test4.setCols(0), std::length_error);
}

TEST(Accessors_and_mutators, SetRows) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1.setRows(5);
  EXPECT_EQ(test1.getRows(), 5);

  S21Matrix test2 = S21Matrix(1, 1);
  test2.setRows(1);
  EXPECT_EQ(test2.getRows(), 1);

  S21Matrix test3 = S21Matrix(1, 1);
  test3.setRows(99);
  EXPECT_EQ(test3.getRows(), 99);

  S21Matrix test4 = S21Matrix(1, 1);
  EXPECT_THROW(test4.setRows(0), std::length_error);
}

TEST(Overloaded_operators, MatrixsetterWrongIndexes) {
  S21Matrix matrix_a(2, 2);
  EXPECT_THROW(matrix_a(3, 0) = 1, std::logic_error);
}

TEST(Overloaded_operators, OperatorSumWithNoEqSizesMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  EXPECT_THROW(matrix_a += matrix_b, std::logic_error);
}

TEST(Overloaded_operators, OperatorSum) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 4;
  matrix_b(0, 1) = 3;
  matrix_b(1, 0) = 2;
  matrix_b(1, 1) = 1;
  matrix_a += matrix_b;
  EXPECT_EQ(matrix_a(0, 0), 5);
  EXPECT_EQ(matrix_a(0, 1), 5);
  EXPECT_EQ(matrix_a(1, 0), 5);
  EXPECT_EQ(matrix_a(1, 1), 5);
}

TEST(Overloaded_operators, OperatorSub) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 4;
  matrix_b(0, 1) = 3;
  matrix_b(1, 0) = 2;
  matrix_b(1, 1) = 1;
  matrix_a -= matrix_b;
  EXPECT_EQ(matrix_a(0, 0), -3);
  EXPECT_EQ(matrix_a(0, 1), -1);
  EXPECT_EQ(matrix_a(1, 0), 1);
  EXPECT_EQ(matrix_a(1, 1), 3);
}

TEST(Overloaded_operators, OperatorMul) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 4;
  matrix_b(0, 1) = 3;
  matrix_b(1, 0) = 2;
  matrix_b(1, 1) = 1;
  matrix_a *= matrix_b;
  EXPECT_EQ(matrix_a(0, 0), 8);
  EXPECT_EQ(matrix_a(0, 1), 5);
  EXPECT_EQ(matrix_a(1, 0), 20);
  EXPECT_EQ(matrix_a(1, 1), 13);
}

TEST(Overloaded_operators, OperatorSubWithNoEqSizesMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a -= matrix_b, std::logic_error);
}

TEST(Overloaded_operators, OperatorMulWithNoEqSizesMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a *= matrix_b, std::logic_error);
}

TEST(Overloaded_operators, OperatorMul2) {
  S21Matrix matrix_a(2, 1);

  matrix_a(0, 0) = 2;
  matrix_a(1, 0) = 3;
  S21Matrix matrix_b(2, 1);
  matrix_b = matrix_a * 3;

  EXPECT_EQ(matrix_b(0, 0), 6);
  EXPECT_EQ(matrix_b(1, 0), 9);
}

TEST(Overloaded_operators, OperatorMul3) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;
  matrix_a = matrix_a * 2;
  EXPECT_EQ(matrix_a(0, 0), 2);
  EXPECT_EQ(matrix_a(0, 1), 4);
  EXPECT_EQ(matrix_a(1, 0), 6);
  EXPECT_EQ(matrix_a(1, 1), 8);
}

TEST(Overloaded_operators, OperatorEqWithNoExSizesMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b;

  EXPECT_THROW(matrix_a = matrix_b, std::logic_error);
}

TEST(Overloaded_operators, OperatorEqWithNoExistSizesMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b;

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  EXPECT_THROW(matrix_b *= matrix_a, std::logic_error);
  EXPECT_THROW(matrix_b += matrix_a, std::logic_error);
  EXPECT_THROW(matrix_b -= matrix_a, std::logic_error);
}

TEST(Overloaded_operators, NonEqMatrix) {
  S21Matrix matrix_a(1, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  S21Matrix matrix_b(2, 2);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(Overloaded_operators, UnOperatorEqWithNoExistSizesMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b;
  S21Matrix result;

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  EXPECT_THROW(matrix_b * matrix_a, std::logic_error);
  EXPECT_THROW(matrix_b + matrix_a, std::logic_error);
  EXPECT_THROW(matrix_b - matrix_a, std::logic_error);
}

TEST(Core_functions_Eq, EqMatrix) {
  S21Matrix test1 = S21Matrix(3, 3);
  test1(1, 2) = 5;
  S21Matrix test2 = test1;
  EXPECT_TRUE(test1.EqMatrix(test2));

  test2(1, 1) = 1;
  EXPECT_FALSE(test1.EqMatrix(test2));

  S21Matrix test3 = S21Matrix(5, 5);
  EXPECT_FALSE(test1.EqMatrix(test3));
}

TEST(Core_functions_Sum, SumMatrix) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  S21Matrix test2 = test1;
  test1.SumMatrix(test2);
  EXPECT_EQ(test1(0, 0), 2);
}

TEST(Core_functions_Sum, SumMatrix2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 4;
  matrix_b(0, 1) = 3;
  matrix_b(1, 0) = 2;
  matrix_b(1, 1) = 1;

  matrix_a.SumMatrix(matrix_b);
  EXPECT_EQ(matrix_a(0, 0), 5);
  EXPECT_EQ(matrix_a(0, 1), 5);
  EXPECT_EQ(matrix_a(1, 0), 5);
  EXPECT_EQ(matrix_a(1, 1), 5);
}

TEST(Core_functions_Sum, SumNonEqMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(1, 0) = 3;
  matrix_b(1, 1) = 4;

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::logic_error);
}

TEST(Core_functions_Sum, SumMatrix3) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test_res = S21Matrix(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      test1(i, j) = 1;
      test_res(i, j) = 2;
    }
  }
  S21Matrix test2 = test1;
  test1 = (test1 + test2);
  EXPECT_EQ(test1, test_res);
}

TEST(Core_functions_Sub, SubNonEqMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::logic_error);
}

TEST(Core_functions_Sub, SubMatrix) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  S21Matrix test2 = test1;
  test1.SubMatrix(test2);
  EXPECT_EQ(test1(0, 0), 0);
}

TEST(Core_functions_Sub, SubMatrix1) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(1, 0) = 3;
  test1(1, 1) = 4;
  S21Matrix test2 = S21Matrix(2, 2);
  test2(0, 0) = 4;
  test2(0, 1) = 1;
  test2(1, 0) = 4;
  test2(1, 1) = 3;
  test1 = test1 - test2;
  EXPECT_EQ(test1(0, 0), -3);
  EXPECT_EQ(test1(0, 1), 1);
  EXPECT_EQ(test1(1, 0), -1);
  EXPECT_EQ(test1(1, 1), 1);
}

TEST(Core_functions_Mul_num, MulNumber1) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  test1.MulNumber(3);
  EXPECT_EQ(test1(0, 0), 15);
}

TEST(Core_functions_Mul_num, MulNumber2) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 5;
  test1(0, 1) = 1;
  test1(1, 0) = 2;
  test1(1, 1) = 3;
  test1.MulNumber(3);
  EXPECT_EQ(test1(0, 0), 15);
  EXPECT_EQ(test1(0, 1), 3);
  EXPECT_EQ(test1(1, 0), 6);
  EXPECT_EQ(test1(1, 1), 9);
}

TEST(Core_functions_Mul_matrix, MulNonEqMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::logic_error);
}

TEST(Core_functions_Mul_matrix, MulMatrix2) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  S21Matrix test2 = test1;
  test1 = (test1 * test2);
  EXPECT_EQ(test1(0, 0), 1);
}

TEST(Core_functions_Mul_matrix, MulMatrix) {
  S21Matrix test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.getRows(); i++) {
    for (int j = 0; j < test1.getCols(); j++) {
      test1(i, j) = test1.getRows() * i + j + 1;
    }
  }
  S21Matrix test2 = test1;
  test1.MulMatrix(test2);
  test2(0, 0) = 30;
  test2(0, 1) = 36;
  test2(0, 2) = 42;
  test2(1, 0) = 66;
  test2(1, 1) = 81;
  test2(1, 2) = 96;
  test2(2, 0) = 102;
  test2(2, 1) = 126;
  test2(2, 2) = 150;
  EXPECT_EQ(test1, test2);
}

TEST(Core_functions_Tranc, Transpose) {
  S21Matrix test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.getRows(); i++) {
    for (int j = 0; j < test1.getCols(); j++) {
      test1(i, j) = test1.getRows() * i + j + 1;
    }
  }
  test1 = test1.Transpose();
  S21Matrix test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = 4;
  test2(0, 2) = 7;
  test2(1, 0) = 2;
  test2(1, 1) = 5;
  test2(1, 2) = 8;
  test2(2, 0) = 3;
  test2(2, 1) = 6;
  test2(2, 2) = 9;
  EXPECT_EQ(test1, test2);
}

TEST(Core_functions_Tranc, TransposeError) {
  S21Matrix test1;
  EXPECT_THROW(test1.Transpose(), std::logic_error);
}

TEST(Core_functions_Calc, CalcCompError) {
  S21Matrix matrix_a(4, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a(3, 0) = 10;
  matrix_a(3, 1) = 11;
  matrix_a(3, 2) = 12;

  EXPECT_THROW(matrix_a.CalcComplements(), std::logic_error);
}

TEST(Core_functions_Calc, CalcComplements) {
  S21Matrix test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  test1 = test1.CalcComplements();
  S21Matrix test2 = S21Matrix(3, 3);
  test2(0, 0) = 0;
  test2(0, 1) = 10;
  test2(0, 2) = -20;
  test2(1, 0) = 4;
  test2(1, 1) = -14;
  test2(1, 2) = 8;
  test2(2, 0) = -8;
  test2(2, 1) = -2;
  test2(2, 2) = 4;
  EXPECT_EQ(test1, test2);
}

TEST(Core_functions_Calc, CalcComplements1) {
  S21Matrix test1 = S21Matrix(2, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  EXPECT_THROW(test1.CalcComplements(), std::logic_error);
}

TEST(Core_functions_Calc, CalcComplements2) {
  S21Matrix test1 = S21Matrix(1, 1);
  S21Matrix test2 = S21Matrix(1, 1);
  test2 = test1.CalcComplements();
  EXPECT_EQ(test1, test2);
}

TEST(Core_functions_Det, DetError) {
  S21Matrix matrix_a(4, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a(3, 0) = 10;
  matrix_a(3, 1) = 11;
  matrix_a(3, 2) = 12;

  EXPECT_THROW(matrix_a.Determinant(), std::logic_error);
}

TEST(Core_functions_Det, Determinant) {
  S21Matrix test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  EXPECT_DOUBLE_EQ(test1.Determinant(), -40);
}

TEST(Core_functions_Det, Determinant1) {
  S21Matrix test1 = S21Matrix(1, 1);
  test1(0, 0) = -40;
  EXPECT_DOUBLE_EQ(test1.Determinant(), -40);
}

TEST(Core_functions_Inv, IverseError) {
  S21Matrix matrix_a(4, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a(3, 0) = 10;
  matrix_a(3, 1) = 11;
  matrix_a(3, 2) = 12;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::logic_error);
}

TEST(Core_functions_Inv, IverseError2) {
  S21Matrix matrix_a;
  EXPECT_THROW(matrix_a.InverseMatrix(), std::logic_error);
}

TEST(Core_functions_Inv, IverseError3) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::logic_error);
}

TEST(Core_functions_Inv, InverseMatrix) {
  S21Matrix test1 = S21Matrix(3, 3);
  test1(0, 0) = 2;
  test1(0, 1) = 5;
  test1(0, 2) = 7;
  test1(1, 0) = 6;
  test1(1, 1) = 3;
  test1(1, 2) = 4;
  test1(2, 0) = 5;
  test1(2, 1) = -2;
  test1(2, 2) = -3;
  test1 = test1.InverseMatrix();
  S21Matrix test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = -1;
  test2(0, 2) = 1;
  test2(1, 0) = -38;
  test2(1, 1) = 41;
  test2(1, 2) = -34;
  test2(2, 0) = 27;
  test2(2, 1) = -29;
  test2(2, 2) = 24;
  EXPECT_EQ(test1, test2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}