#pragma once

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cstdint>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

/// @brief Вершина модели (координаты x,y,z).
struct Vertex {
  double x, y, z;
};

/// @brief Ребро: пара индексов вершин (индексация с 0).
using Edge = std::pair<unsigned int, unsigned int>;

/// @brief Парсер .obj: читает вершины, рёбра и индексы треугольников из файла.
class ObjParser {
 public:
  /// @brief Загружает данные модели из .obj файла.
  /// @param filename Путь к файлу.
  /// @param vertices Выход: список вершин.
  /// @param edges Выход: список рёбер (пары индексов вершин, 0-based).
  /// @param tri_indices Выход: индексы треугольников (для заливки).
  static bool Parse(const std::string& filename, std::vector<Vertex>& vertices,
                    std::vector<Edge>& edges,
                    std::vector<std::uint32_t>& tri_indices);
};
}  // namespace s21
