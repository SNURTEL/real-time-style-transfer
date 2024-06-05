#include <iostream>

#include <QFileDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <qnamespace.h>

#include "common/image.hpp"
#include "common/model.hpp"
#include "common/utils.hpp"
#include "ui/pages/image_page.hpp"
#include "ui/state.hpp"

ImagePage::ImagePage(QWidget *parent, std::shared_ptr<State> state)
    : Page(parent, state) {
    setupUi();
}

void ImagePage::setupUi() {
    _layout = std::make_shared<QVBoxLayout>(this);
    _layout->setObjectName(QString::fromUtf8("Layout"));
    _imagesLayout = std::make_shared<QHBoxLayout>(this);
    _controlsLayout = std::make_shared<QHBoxLayout>(this);

    // region Title
    _title = std::make_shared<QLabel>(this);
    _title->setText(QString::fromUtf8("???"));
    _title->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setPointSize(16);
    _title->setFont(font);

    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    _title->setSizePolicy(sizePolicy1);
    _layout->addWidget(_title.get());
    // endregion

    // region Images
    _inputImage = std::make_shared<QLabel>(this);
    _outputImage = std::make_shared<QLabel>(this);
    _imagesLayout->addWidget(_inputImage.get());
    _imagesLayout->addWidget(_outputImage.get());
    // endregion

    // region Controls
    _loadImageButton = std::make_shared<QPushButton>(this);
    _loadImageButton->setText(QString::fromUtf8("Load image"));
    connect(_loadImageButton.get(), &QPushButton::clicked, this,
            &ImagePage::onLoadImageButtonClicked);

    _transformButton = std::make_shared<QPushButton>(this);
    _transformButton->setText(QString::fromUtf8("Transform"));
    connect(_transformButton.get(), &QPushButton::clicked, this,
            &ImagePage::onTransformButtonClicked);

    _controlsLayout->addWidget(_loadImageButton.get());
    _controlsLayout->addWidget(_transformButton.get());
    // endregion

    this->setLayout(_layout.get());
    _layout->addLayout(_imagesLayout.get());
    _layout->addLayout(_controlsLayout.get());
}

void ImagePage::activatePage() {
    Page::activatePage();

    updateUi();
}

void ImagePage::updateUi() {
    _transformButton->setDisabled(true);

    if (_state->getActiveModel()) {
        _title->setText(QString::fromUtf8("Transform style"));
        _title->setStyleSheet("QLabel { color : #78e08f; }");

        if (_inputImagePath) {
            _transformButton->setDisabled(false);
        }
    } else {
        _title->setText(QString::fromUtf8("Missing model"));
        _title->setStyleSheet("QLabel { color : #e55039; }");
    }
}

void ImagePage::deactivatePage() { Page::deactivatePage(); }

void ImagePage::onLoadImageButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(
        nullptr, QString::fromUtf8("Choose file"), "",
        QString::fromUtf8("Images (*.png *.jpg *.bmp)"));

    if (!filename.isEmpty()) {
        QPixmap pixmap;
        if (pixmap.load(filename)) {
            float downscaleFactor =
                pixmap.height() > 800 || pixmap.width() > 800
                    ? std::max(pixmap.height() / 800, pixmap.width() / 800)
                    : 1;
            _inputImage->setPixmap(pixmap.scaled(
                pixmap.width() / downscaleFactor,
                pixmap.height() / downscaleFactor, Qt::KeepAspectRatio));
            _inputImagePath = filename.toStdString();
            updateUi();
        }
    }
}

void ImagePage::onTransformButtonClicked() {
    if (!_inputImagePath) {
        updateUi();
    }

    // Load to Cv2 mat
    auto __mat = image::loadImage(_inputImagePath.value(), cv::IMREAD_COLOR);
    if (!__mat) {
        _inputImagePath = std::nullopt;
        updateUi();
    }

    cv::Mat _mat = __mat.value()(cv::Rect(0, 0, __mat.value().size[1] / 2 * 2,
                                          __mat.value().size[0] / 2 * 2));

    float downscaleFactor =
        _mat.size[0] > 800 || _mat.size[1] > 800
            ? std::max(_mat.size[0] / 800, _mat.size[1] / 800)
            : 1;
    cv::Mat mat;
    cv::resize(_mat, mat,
               cv::Size(_mat.size[1] / downscaleFactor,
                        _mat.size[0] / downscaleFactor),
               0, 0, cv::INTER_LINEAR);

    std::shared_ptr<Model> model = _state->getModel();

    cv::Mat out = transfer(mat, model);

    // Convert Cv2 Mat to QImage, then to QPixmap
    cv::Mat bgra;
    cv::cvtColor(out, bgra, cv::COLOR_BGR2BGRA);
    _currImage = bgra.clone();
    if (!_currImage) {
        return;
    }
    QImage img(_currImage.value().data, _currImage.value().cols,
               _currImage.value().rows, QImage::Format_RGB32);
    QPixmap pixmap = QPixmap::fromImage(img);
    // Display
    _outputImage->setPixmap(pixmap);
}
