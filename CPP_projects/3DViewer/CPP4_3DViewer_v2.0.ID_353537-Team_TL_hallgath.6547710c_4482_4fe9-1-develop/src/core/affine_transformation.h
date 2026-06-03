#pragma once

#include <array>

#include "matrix.h"

namespace s21 {
struct Vec3 {
  double x{};
  double y{};
  double z{};
};

/**
 * @brief Аффинные преобразования для матрицы вершин 3xN.
 *
 * Матрица вершин имеет вид 3xN, где каждый столбец — вершина (x,y,z).
 * Вращения задаются в градусах. Для OpenGL есть экспорт 4x4 в column-major.
 */
class AffineTransformation {
 public:
  /// @brief Матрица переноса 4x4 (сдвиг на dx, dy, dz).
  static S21Matrix Translation4(double dx, double dy, double dz);
  /// @brief Единичная матрица 4x4.
  static S21Matrix Identity4();
  /// @brief Единичная матрица 3x3.
  static S21Matrix Identity3();
  /// @brief Поворачивает модель вокруг её центра на углы OX/OY/OZ.
  static S21Matrix RotateBy(const S21Matrix& matrix, double OX_degree,
                            double OY_degree, double OZ_degree);
  /// @brief Сдвигает объект на (x, y, z).
  static S21Matrix MoveObject(const S21Matrix& matrix, double x, double y,
                              double z);
  /// @brief Масштабирует объект: умножает все координаты на rate.
  static S21Matrix Stretch(const S21Matrix& matrix, double rate);

  /// @brief Возвращает матрицу модели 4x4 для вращения вокруг центра.
  static S21Matrix ModelRotateAroundCenter4(const S21Matrix& vertices3xN,
                                            double ox_deg, double oy_deg,
                                            double oz_deg);
  /// @brief Матрица вращения вокруг оси Y на угол fi (в градусах), 4x4.
  static S21Matrix GetRotationYMatrix(double fi);
  /// @brief Матрица вращения вокруг оси X на угол fi (в градусах), 4x4.
  static S21Matrix GetRotationXMatrix(double fi);
  /// @brief Матрица вращения вокруг оси Z на угол fi (в градусах), 4x4.
  static S21Matrix GetRotationZMatrix(double fi);

  /// @brief Преобразует матрицу 4x4 в массив в column-major (для OpenGL).
  static std::array<float, 16> GetColMajor(const S21Matrix& matrix);

 private:
  /// @brief Делает из 3xN матрицу 4xN, добавляя снизу строку из 1.
  static S21Matrix ExpandMatrix(const S21Matrix& expanding_matrix);
  /// @brief Делает из 4xN матрицу 3xN, убирая 4-ю строку.
  static S21Matrix ShrinkMatrix(const S21Matrix& shrinking_matrix);

  /// @brief Применяет преобразование (A + перенос t) к вершинам 3xN.
  static S21Matrix ApplyTransformation(const S21Matrix& x, const S21Matrix& A,
                                       const Vec3& t);

  /// @brief Собирает матрицу 4x4 из A (верхний левый 3x3) и переноса t.
  static S21Matrix BuildAffine4(const S21Matrix& A, const Vec3& t);

  /**
   * @brief Находит центр модели по (bbox-center).
   * @param v Матрица вершин 3xN.
   * @return Центр ((min+max)/2) по каждой оси.
   */
  static s21::Vec3 ComputeBBoxCenter(const S21Matrix& v) {
    // v: 3xN
    if (v.get_rows() != 3) {
      throw std::invalid_argument("ComputeBBoxCenter: expected 3xN matrix");
    }

    const int n = v.get_cols();

    double min_x = v[0][0], max_x = v[0][0];
    double min_y = v[1][0], max_y = v[1][0];
    double min_z = v[2][0], max_z = v[2][0];

    for (int j = 1; j < n; ++j) {
      const double x = v[0][j];
      const double y = v[1][j];
      const double z = v[2][j];

      if (x < min_x) min_x = x;
      if (x > max_x) max_x = x;

      if (y < min_y) min_y = y;
      if (y > max_y) max_y = y;

      if (z < min_z) min_z = z;
      if (z > max_z) max_z = z;
    }

    return s21::Vec3{(min_x + max_x) * 0.5, (min_y + max_y) * 0.5,
                     (min_z + max_z) * 0.5};
  }

 public:
  ///@brief Печатает матрицу (для отладки).
  static void PrintMatrix(const S21Matrix& result,
                          bool should_transpose = false) {
    auto z = [](double v) { return (std::abs(v) < 1e-12) ? 0.0 : v; };
    auto x = should_transpose ? result.Transpose() : result;
    for (int i = 0; i < x.get_rows(); ++i) {
      for (int j = 0; j < x.get_cols(); ++j) {
        std::cout << z(x[i][j]) << '\t';
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};
};  // namespace s21
