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
            _inputImage->setPixmap(pixmap);
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
    auto _mat = image::loadImage(_inputImagePath.value(), cv::IMREAD_COLOR);
    if (!_mat) {
        _inputImagePath = std::nullopt;
        updateUi();
    }
    cv::Mat mat = _mat.value()(cv::Rect(0, 0, _mat.value().size[1] / 2 * 2, _mat.value().size[0] / 2 * 2));
    cv::Mat paddedFrame;
    int longerEdge = std::max(mat.size[0], mat.size[1]);
    int vPadding = std::max(0, (longerEdge - mat.size[0]) / 2);
    int hPadding = std::max(0, (longerEdge - mat.size[1]) / 2);
    cv::copyMakeBorder(mat, paddedFrame, vPadding, vPadding, hPadding, hPadding, cv::BORDER_ISOLATED);
    // cv::Mat square = cv2.copyMakeBorder(src, top, bottom, left, right, borderType)
    // cv::resize(mat.value(), scaledFrame, cv::Size(512, 512), 0, 0,
    //             cv::INTER_LINEAR);

    // Convert to tensor
    auto tensor = cv2ToTensor(paddedFrame, true).cuda();
    qDebug() << "Converted to tensor";

    // Get model and forward the tensor
    std::shared_ptr<Model> model = _state->getModel();
    qDebug() << "Model ready";
    auto result = model->forward(tensor);
    qDebug() << "Result is here";

    auto denormalized = ((result + 1) * 127.5)
                            .detach()
                            .clamp(0, 255)
                            .to(torch::kU8)
                            .to(torch::kCPU);
    qDebug() << "Denormalized result";


    // Convert result tensor to Cv2 Mat
    auto resultMat = tensorToCv2(denormalized, true);
    qDebug() << "Back to cv2";
    cv::Mat cropped = resultMat(cv::Rect(hPadding, vPadding, mat.size[1], mat.size[0]));

    // cv::Mat scaled;
    // cv::resize(resultMat, scaled, cv::Size(1024, 1024), 0, 0, cv::INTER_LINEAR);

    // Convert Cv2 Mat to QImage, then to QPixmap
    cv::Mat bgra;
    cv::cvtColor(cropped, bgra, cv::COLOR_BGR2BGRA);
    _currImage = bgra.clone();
    if (!_currImage) {
        return;
    }
    QImage img(_currImage.value().data, _currImage.value().cols, _currImage.value().rows, QImage::Format_RGB32);
    qDebug() << "QImage now";
    QPixmap pixmap = QPixmap::fromImage(img);
    qDebug() << "Nearly finished";
    // Display
    _outputImage->setPixmap(pixmap);
    qDebug() << "Done!";

    // cv::imshow("Transferred", cropped.clone());
}
