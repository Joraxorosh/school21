#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QString>
#include <array>
#include <cstdint>
#include <vector>

#include "gl_shader_loader.h"

namespace s21 {
/// @brief Рендерер модели на OpenGL 3.3 (каркас/заливка/вершины, пунктир).
class GlRender {
 public:
  /// @brief Данные меша для загрузки в GPU: вершины и индексы
  /// треугольников/рёбер.
  struct MeshData {
    std::vector<float> vertices_xyz;
    std::vector<std::uint32_t> tri_indices;   // заливка граней
    std::vector<std::uint32_t> edge_indices;  // индексы ребер
  };
  /// @brief Параметры отрисовки: что рисовать и как (цвета, толщина, пунктир,
  /// вершины, фон).
  struct DrawParams {
    bool fill_enabled = false;  // заливка граней
    bool draw_edges = true;     // ребра
    bool edges_dashed = false;
    float dash_period = 0.1f;  // период
    float dash_fill = 0.5f;    // доля штриха

    float fill_rgba[4] = {0.f, 0.f, 1.f, 1.f};  // цвет заливки граней
    bool transparent = false;

    float edge_rgb[3] = {0.f, 0.f, 1.f};  // цвет ребер
    float edge_width = 2.f;               // толщина заливки

    // bool draw_vertices = false;   // показывать вершины
    int vertex_mode = 0;                        // 0=нет, 1=круг, 2=квадрат
    float vertex_size = 8.f;                    // размер вершин
    float vertex_rgb[3] = {0.f, 0.f, 1.f};      // цвет вершин
    float background_rgb[3] = {1.f, 1.f, 1.f};  // цвет фона
  };

  GlRender() = default;
  ~GlRender();

  /// @brief Инициализирует OpenGL-состояния и загружает шейдеры.
  bool Initialize(
      QOpenGLFunctions_3_3_Core* f,
      const QString& vertex_shader = "resources/shaders/basic.vert",
      const QString& fragment_shader = "resources/shaders/basic.frag");

  /// @brief Загружает меш (вершины/индексы) в GPU буферы.
  void UploadMesh(const MeshData& mesh);
  /// @brief Обновляет параметры viewport при изменении размеров окна.
  void Resize(int w, int h);
  /// @brief Рисует модель по матрице mvp (column-major) и параметрам отрисовки.
  void Render(const std::array<float, 16>& mvp_col_major,
              const DrawParams& params);
  /// @brief Освобождает OpenGL-ресурсы (VAO/VBO/EBO и т.п.).
  void Destroy();

 private:
  /// @brief Вершина ребра для пунктира (позиция + параметр вдоль ребра).
  struct EdgeVertex {
    float x, y, z;  ///< Позиция.
    float t;        ///< Параметр вдоль ребра для расчёта пунктира.
  };

  QOpenGLFunctions_3_3_Core* f_ = nullptr;  ///< Доступ к функциям OpenGL 3.3.

  QOpenGLShaderProgram program_;  ///< Шейдерная программа.
  int loc_mvp_ = -1;              // location for uMVP ///< uniform uMVP.
  int loc_color_ = -1;  // location for color (for 1) ///< uniform цвета.

  int loc_use_dash_ = -1;     ///< uniform: включить пунктир.
  int loc_dash_period_ = -1;  ///< uniform: период пунктира.
  int loc_dash_fill_ = -1;    ///< uniform: заполнение пунктира.

  int loc_point_mode_ = -1;  ///< uniform: режим вершин.
  int loc_point_soft_ = -1;  ///< uniform: сглаживание вершин.
  int loc_point_size_ = -1;  ///< uniform: размер вершин

  unsigned vao_ = 0;       ///< VAO для основного меша.
  unsigned vbo_ = 0;       ///< VBO вершин.
  unsigned ebo_tri_ = 0;   ///< EBO треугольников.
  unsigned ebo_edge_ = 0;  ///< EBO рёбер.

  unsigned vao_edge_ = 0;  // VAO/ VBO для aEdgeT ///< VAO для геометрии рёбер
                           // (пунктир/параметр t).
  unsigned vbo_edge_ = 0;  ///< VBO для EdgeVertex.

  int tri_index_count_ = 0;   ///< Количество индексов треугольников.
  int edge_index_count_ = 0;  ///< Количество индексов рёбер.

  int edge_vertex_count_ =
      0;  // vbo_edge кол-во ребер ///< Количество EdgeVertex в vbo_edge_.
  int vertex_count_ = 0;  ///< Количество вершин.
};
}  // namespace s21
