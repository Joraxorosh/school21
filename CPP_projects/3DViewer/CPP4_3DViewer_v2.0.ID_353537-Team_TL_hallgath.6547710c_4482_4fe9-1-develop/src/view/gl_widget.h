#pragma once

#include <core/affine_transformation.h>
#include <core/matrix.h>
#include <core/projection.h>
#include <gif/gif_recorder.h>
#include <parser/obj_parser.h>
#include <render/opengl/gl_render.h>
#include <settings/settings.h>

#include <QFileInfo>
#include <QKeyEvent>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QSet>
#include <QTimer>
#include <algorithm>
#include <array>

namespace s21 {
/// @brief OpenGL-виджет: загружает модель, управляет камерой/проекцией и рисует
/// через GlRender.
class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

 public:
  explicit GlWidget(QWidget* parent = nullptr);
  ~GlWidget() override;

  // interface
  /// @brief Установить цвет фона.
  void SetBackgroundColor(const QColor& c);
  /// @brief Установить тип проекции.
  void SetProjectionType(int type);
  /// @brief Включить/выключить пунктир для рёбер.
  void SetEdgesDashed(bool on);
  /// @brief Установить толщину рёбер.
  void SetEdgeWidth(float w);
  /// @brief Установить цвет рёбер.
  void SetEdgeColor(const QColor& c);
  /// @brief Режим вершин: 0=нет, 1=круг, 2=квадрат.
  void SetVertexMode(int mode);
  /// @brief Установить размер вершин.
  void SetVertexSize(float s);
  /// @brief Установить цвет вершин.
  void SetVertexColor(const QColor& c);
  /// @brief Период пунктира.
  void SetDashPeriod(float p);
  /// @brief Доля “штриха” в периоде.
  void SetDashFill(float f);
  /// @brief Включить/выключить заливку граней.
  void SetFillEnabled(bool on);
  /// @brief Установить прозрачность заливки (alpha).
  void SetFillAlpha(float a);
  /// @brief Установить цвет и прозрачность заливки.
  void SetFillColor(const QColor& c, float a);
  /// @brief Установить углы поворота модели (в градусах)
  void SetRotationDegrees(double ax_deg, double ay_deg, double az_deg);
  /// @brief Сбросить поворот к значениям по умолчанию.
  void ResetRotation();

  /// @brief Углы поворота модели.
  struct RotationDeg {
    double x;
    double y;
    double z;
  };
  /// @brief Получить текущие углы поворота.
  [[nodiscard]] RotationDeg GetRotationDegrees() const;

 signals:
  /// @brief Сигнал: изменились углы поворота.
  void RotationChanged(double ax_deg, double ay_deg, double az_deg);
  /// @brief Сигнал: запись gif.
  void GifSaved(bool success, const QString& filename);  // gif

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;

 public:
  /// @brief Включить/выключить “непрозрачный режим” заливки.
  void SetFillOpaque(bool opaque);

 private:
  float fill_alpha_saved_ = 0.8f;

 signals:
  /// @brief Сигнал: включение заливки изменилось.
  void FillEnabledChanged(bool on);

 private:
  bool render_ready_ = false;

 public:
  /// @brief Загрузить модель из .obj файла.
  bool LoadModelFromObjFile(const QString& path);
  /// @brief Возвращает, включена ли заливка
  bool GetFillEnabled() const { return params_.fill_enabled; }
  /// @brief Возвращает, “непрозрачна” ли заливка (alpha ~ 1).
  bool GetFillOpaque() const { return params_.fill_rgba[3] >= 0.999f; }

  /// @brief Режим проекции.
  enum class ProjectionMode { kPerspective, kOrtho };
  /// @brief Обработка нажатых клавиш (движение/управление).
  void TickInput();
  /// @brief Нормализация углов.
  void NormalizeAngles();
  /// @brief Пересчитать MVP-матрицу по текущим параметрам.
  void UpdateMvp();
  /// @brief Переключить режим проекции.
  void ToggleProjection();
  /// @brief Быстро включить/выключить заливку.
  void ToggleFill();

  GlRender render_;              ///< Низкоуровневый рендерер OpenGL.
  GlRender::MeshData mesh_;      ///< Данные меша (вершины/индексы).
  GlRender::DrawParams params_;  ///< Параметры отрисовки

  ProjectionMode proj_mode_ = ProjectionMode::kPerspective;

  // camera
  double cam_x_ = 0.0;
  double cam_y_ = 0.0;
  double cam_z_ = 3.0;

  double fov_y_deg_ = 60.0;  ///< FOV для перспективы.

  // symmetric
  double ortho_half_w_ = 1.2;

  // degrees
  double ax_ = 20.0;
  double ay_ = 30.0;
  double az_ = 0.0;

  std::array<float, 16> mvp_col_major_{};

  QTimer timer_;    //< Таймер для регулярного TickInput_/перерисовки.
  QSet<int> keys_;  ///< Набор нажатых клавиш.

 signals:
  /// @brief Сигнал: изменился масштаб.
  void ScaleChanged(double s);

 public:
  /// @brief Текущий масштаб модели.
  double GetScale() const { return scale_; }
  /// @brief Установить масштаб модели.
  void SetScale(double s);
  /// @brief Умножить масштаб на k.
  void ScaleBy(double k);
  /// @brief Сброс масштаба к 1.0.
  void ResetScale();

  // гетеры для настроек
  int GetProjectionType() const;
  bool GetEdgesDashed() const;
  float GetEdgeWidth() const;
  float GetDashPeriod() const;
  float GetDashFill() const;

  int GetVertexMode() const;
  float GetVertexSize() const;

  bool GetFillTransparent() const;
  float GetFillAlpha() const;

 private:
  double scale_ = 1.0;  ///< Масштаб модели.

 signals:
  /// @brief Сигнал: обновилась информация о модели (имя файла, вершины, рёбра)
  void ModelInfoChanged(const QString& file_name, int vertex_count,
                        int edge_count);

 public:
  /// @brief Имя текущего файла модели (для UI).
  QString GetModelFileName() const { return model_file_name_; }
  /// @brief Количество вершин в модели.
  int GetVertexCount() const { return model_vertex_count_; }
  /// @brief Количество рёбер в модели.
  int GetEdgeCount() const { return model_edge_count_; }

 private:
  QString model_file_name_ = "—";
  int model_vertex_count_ = 0;
  int model_edge_count_ = 0;

  /// @brief загрузка настроек
  void LoadSettings();
  /// @brief выгрузка настроек
  void SaveSettings() const;

 public:  // gif
  bool StartGifRecording(const QString& filename);
  void StopGifRecording();
  bool IsGifRecording() const;

 private:  // gif
  GifRecorder* gif_recorder_ = nullptr;
};
}  // namespace s21