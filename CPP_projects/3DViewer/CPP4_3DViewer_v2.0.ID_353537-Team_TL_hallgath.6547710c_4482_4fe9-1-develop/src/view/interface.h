#pragma once

#include <QtWidgets>

namespace s21 {

class GlWidget;
/// @brief Основной UI-контроллер: верхняя панель вкладок + выдвижная панель
/// настроек + инфо-строка.
class Interface final : public QWidget {
  Q_OBJECT

 public:
  /// @brief Создаёт интерфейс и привязывает его к viewport (GlWidget).
  explicit Interface(GlWidget* viewport, QWidget* parent = nullptr);
  ~Interface() override;

 protected:
  /// @brief Перехватывает события (например, клики/фокус) для управления
  /// панелью/вкладками.
  bool eventFilter(QObject* obj, QEvent* ev) override;
  /// @brief Обрабатывает изменение размера окна и подгоняет геометрию панелей.
  void resizeEvent(QResizeEvent* e) override;

 private:
  /// @brief Собирает все элементы UI.
  void BuildUi();
  /// @brief Применяет стили (палитра/шрифты/отступы).
  void ApplyStyle();
  /// @brief Убирает фокус с контролов.
  static void MakeControlsNoFocus(QWidget* root);
  /// @brief Пересчитывает высоту выдвижной панели под текущую страницу.
  void UpdatePanelHeight() const;
  /// @brief Обработчик клика по вкладке (переключение страницы).
  void OnTabClicked(int id);
  /// @brief Закрывает выдвижную панель.
  void OnClosePanel() const;

  /// @brief изображение в байты (PNG/JPG и т.п.) с заданным качеством.
  static QByteArray ImageToBytes(const QImage& img, const char* format,
                                 int quality);
  /// @brief Сохраняет текущий рендер в файл (скриншот).
  void SaveRenderedImage();

  /// @brief Страница настроек проекции.
  QWidget* MakePageProjection();
  /// @brief Страница настроек рёбер.
  QWidget* MakePageEdges();
  /// @brief Страница настроек вершин.
  QWidget* MakePageVertices();
  /// @brief Страница настроек фона.
  QWidget* MakePageBackground();
  /// @brief Страница Файл.
  QWidget* MakePageFile();

  GlWidget* viewport_ = nullptr;
  QWidget* topBar_ = nullptr;        ///< Верхняя панель вкладок.
  QButtonGroup* tabs_ = nullptr;     ///< Группа кнопок-вкладок.
  QFrame* panel_ = nullptr;          ///< Выдвижная панель.
  QFrame* panelBox_ = nullptr;       ///< Контейнер/рамка внутри панели.
  QStackedWidget* pages_ = nullptr;  ///< Набор страниц настроек.

 private:
  QWidget* infoBar_ = nullptr;  ///< Информационная строка (файл/вершины/рёбра).
  QLabel* fileValue_ = nullptr;  ///< Значение: имя файла.
  QLabel* vtxValue_ = nullptr;   ///< Значение: количество вершин.
  QLabel* edgeValue_ = nullptr;  ///< Значение: количество рёбер.

  /// @brief Показать/скрыть инфо-строку.
  void SetInfoBarVisible(bool on) const;

  /// @brief синхронизация с настройками
  void SyncControlsFromViewport() const;

  QPushButton* projOrthoBtn_ = nullptr;
  QPushButton* projPerspBtn_ = nullptr;

  QCheckBox* edgesDashedCheck_ = nullptr;
  QDoubleSpinBox* edgeWidthSpin_ = nullptr;
  QDoubleSpinBox* dashPeriodSpin_ = nullptr;
  QDoubleSpinBox* dashFillSpin_ = nullptr;

  QComboBox* vertexModeCombo_ = nullptr;
  QDoubleSpinBox* vertexSizeSpin_ = nullptr;

  QCheckBox* fillEnabledCheck_ = nullptr;
  QCheckBox* fillTransparentCheck_ = nullptr;
};
}  // namespace s21
