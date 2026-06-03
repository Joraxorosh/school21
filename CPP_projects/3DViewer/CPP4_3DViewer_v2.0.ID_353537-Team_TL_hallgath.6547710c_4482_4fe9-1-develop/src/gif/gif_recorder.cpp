#include "gif_recorder.h"
#include "gif.h"

#include <QPainter>

namespace s21 {

    GifRecorder::GifRecorder(QObject* parent)
        : QObject(parent) {}

    void GifRecorder::startRecording(const QString& filename) {
        if (isRecording_) return;

        outputFile_ = filename;
        frames_.clear();
        frames_.reserve(kMaxFrames);

        isRecording_ = true;
        nextCaptureMs_ = 0;
        elapsed_.start();
    }

    void GifRecorder::stopRecording() {
        isRecording_ = false;
    }

    void GifRecorder::captureFrame(const QImage& frame) {
        if (!isRecording_) return;

        const qint64 nowMs = elapsed_.elapsed();
        if (nowMs < nextCaptureMs_) return;
        nextCaptureMs_ += kCaptureIntervalMs; // 100 мс

        QImage src = frame.convertToFormat(QImage::Format_RGBA8888);
        QImage scaled = src.scaled(
            kWidth, kHeight,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        QImage canvas(kWidth, kHeight, QImage::Format_RGBA8888);
        canvas.fill(Qt::black);

        QPainter p(&canvas);
        p.drawImage((kWidth - scaled.width()) / 2, (kHeight - scaled.height()) / 2, scaled);
        p.end();

        frames_.push_back(canvas);

        if (static_cast<int>(frames_.size()) >= kMaxFrames) {
            isRecording_ = false;
            const bool ok = saveGifInternal();
            emit gifSaved(ok, outputFile_);
        }
    }

    bool GifRecorder::saveGifInternal() {
        if (frames_.empty()) return false;

        ::GifWriter gif;
        if (!::GifBegin(&gif,
                        outputFile_.toStdString().c_str(),
                        kWidth,
                        kHeight,
                        kGifDelayCs)) {
            return false;
                        }

        for (const QImage& frame : frames_) {
            ::GifWriteFrame(&gif,
                            frame.constBits(),
                            kWidth,
                            kHeight,
                            kGifDelayCs);
        }

        return ::GifEnd(&gif);
    }
}