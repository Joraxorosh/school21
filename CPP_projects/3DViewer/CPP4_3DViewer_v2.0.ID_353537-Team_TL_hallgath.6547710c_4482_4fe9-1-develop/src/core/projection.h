#pragma once
#include "matrix.h"

namespace s21 {
/// @brief Построение матриц проекции (перспективной и ортографической).
class Projection final {
 public:
  /// @brief Перспективная (центральная) проекция: строит матрицу perspective по
  /// FOV.
  static S21Matrix Perspective(double vertical_fov_deg,  // центральная проекция
                               double aspect_ratio, double near_plane,
                               double far_plane);
  /// @brief Ортографическая проекция: строит матрицу ortho по границам
  /// left/right/bottom/top и near/far.
  static S21Matrix Ortho(
      double left, double right,  // параллельная(ортографическая) проекция mvp
      double bottom, double top, double z_near, double z_far);
  /// @brief Симметричная ортографическая проекция по полу-ширине и aspect
  /// (центр в 0), с near/far.
  static S21Matrix OrthoSymmetric(double half_width, double aspect,
                                  double z_near, double z_far);
};
}  // namespace s21
