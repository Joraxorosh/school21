#pragma once

#include <QString>

class QOpenGLShaderProgram;

namespace s21 {
/// @brief Загрузка и компиляция шейдеров (vertex/fragment) в
/// QOpenGLShaderProgram.
class GlShaderLoader final {
 public:
  /// @brief Загружает шейдеры из файлов, компилирует, линкует и пишет лог
  /// ошибки.
  static bool load(QOpenGLShaderProgram& program, const QString& vertex_path,
                   const QString& fragment_path, QString* out_error_log);
};

}  // namespace s21
