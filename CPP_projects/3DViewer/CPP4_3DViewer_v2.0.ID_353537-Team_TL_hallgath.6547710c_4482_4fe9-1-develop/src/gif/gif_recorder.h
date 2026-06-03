#pragma once

#include <QObject>
#include <QImage>
#include <QElapsedTimer>
#include <QString>
#include <vector>

namespace s21 {
	/**
   * @brief Класс записи анимированного GIF из последовательности кадров QImage.
   *
   * Класс предназначен для упрощённой записи GIF-анимации в рамках задания:
   * фиксированные параметры вывода составляют 640x480 пикселей, 10 кадров/с
   * и длительность 5 секунд (50 кадров).
   */
	class GifRecorder : public QObject {
		Q_OBJECT
	public:
		/**
	    * @brief Создаёт объект записи GIF.
	    * @param parent Родительский объект Qt.
	    */
		explicit GifRecorder(QObject* parent = nullptr);
		/**
	    * @brief Деструктор.
	    */
		~GifRecorder() override = default;
		/// @brief запускает запись GIF в указанный файл.
		void startRecording(const QString& filename);
		/// @brief Принудительно останавливает запись без сохранения результата.
		void stopRecording();
		/// @brief Возвращает признак активной записи.
		bool isRecording() const { return isRecording_; }

	public slots:
		/// @brief frame Исходный кадр сцены.
		void captureFrame(const QImage& frame);

		signals:
			/// @brief Сигнал о завершении автоматического сохранения GIF
			void gifSaved(bool success, const QString& filename);

	private:
		/// @brief Выполняет сериализацию накопленных кадров в один GIF-файл.
		bool saveGifInternal();

		/// Ширина выходного GIF (пиксели).
		static constexpr int kWidth = 640;
		/// Высота выходного GIF (пиксели).
		static constexpr int kHeight = 480;
		/// Частота кадров GIF (кадров в секунду).
		static constexpr int kFps = 10;
		/// Длительность записи (секунды).
		static constexpr int kDurationSec = 5;
		/// Общее количество кадров в записи.
		static constexpr int kMaxFrames = kFps * kDurationSec;
		/// Интервал дискретизации входного потока кадров (мс).
		static constexpr int kCaptureIntervalMs = 1000 / kFps;
		/// Задержка кадра в формате GIF (сотые доли секунды).
		static constexpr int kGifDelayCs = 100 / kFps;

		/// @brief Буфер накопленных кадров.
		std::vector<QImage> frames_;
		/// Признак активной записи.
		bool isRecording_ = false;
		/// Путь к выходному GIF-файлу.
		QString outputFile_;
		/// @brief Таймер для определения моментов захвата кадров.
		QElapsedTimer elapsed_;
		/// Следующий момент времени (в мс от старта записи), когда нужно принять кадр.
		qint64 nextCaptureMs_ = 0; // следующий момент времени, когда надо взять кадр
	};
} // namespace s21

