#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <optional>
#include <thread>
#include <torch/types.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/camera.hpp"
#include "common/utils.hpp"
#include "ui/pages/camera_page.hpp"
#include "ui/state.hpp"

#define CAMERAS 1

CameraPage::CameraPage(QWidget *parent, std::shared_ptr<State> state)
    : Page(parent, state) {
    setupUi();
    updateUi();
}

CameraPage::~CameraPage() {
    setRunning(false);
}

void CameraPage::setupUi() {
    _layout = std::make_shared<QVBoxLayout>(this);
    _layout->setObjectName(QString::fromUtf8("Layout"));
    _camerasLayout = std::make_shared<QHBoxLayout>(this);

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

    if (CAMERAS > 0) {
        _cameraLeft = std::make_shared<QLabel>(this);
        _cameraRight = std::make_shared<QLabel>(this);

        QPixmap pixmap("resources/camera.png");
        _cameraLeft->setPixmap(pixmap);
        _cameraRight->setPixmap(pixmap);

        _camerasLayout->addWidget(_cameraLeft.get());
        _camerasLayout->addWidget(_cameraRight.get());
    }

    // region Button
    _button = std::make_shared<QPushButton>(this);
    _button->setText(QString::fromUtf8("Start"));
    connect(_button.get(), &QPushButton::clicked, this,
            &CameraPage::onButtonClicked);
    // endregion

    this->setLayout(_layout.get());
    _layout->addLayout(_camerasLayout.get());
}

void CameraPage::updateUi() {
    _button->setDisabled(true);

    if (CAMERAS > 0) {
        if (_state->getActiveModel()) {
            _title->setText("Camera Inference");
            _title->setStyleSheet("QLabel { color : #78e08f; }");
            _button->setDisabled(false);
        }
        else {
            _title->setText("Missing active model");
            _title->setStyleSheet("QLabel { color : #e55039; }");
        }
    }
    else {
        _title->setText("No camera available");
        _title->setStyleSheet("QLabel { color : #e55039; }");
    }
}

void CameraPage::activatePage() {
    Page::activatePage();

    updateUi();
}

void CameraPage::deactivatePage() { 
    Page::deactivatePage();
    setRunning(false);
}

void CameraPage::onButtonClicked() {
    _button->setDisabled(true);

    setRunning(!_isRunning);

    _button->setDisabled(false);
    updateUi();
}

void CameraPage::setRunning(bool flag) {
    _isRunning = flag;
    if (_isRunning) {
        if (!_updaterThread) {
            _updaterThread = std::thread(std::bind(&CameraPage::updater, this));
        }
        _button->setText(QString::fromUtf8("Stop"));
    } else {
        if (_updaterThread && _updaterThread->joinable()) {
            _updaterThread->join();
            _updaterThread = std::nullopt;
        } 
        _button->setText(QString::fromUtf8("Start"));
    }
}

void CameraPage::updater() {
    auto cam = Camera::build();
    if (!cam) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return;
    }
    std::shared_ptr<Model> model = _state->getModel();
    while (_isRunning) {
        auto __frame = cam->nextFrame();
        if (!__frame) {
            std::cerr << "Error getting frame" << std::endl;
            return;
        }
        cv::Mat _frame = __frame.value()(cv::Rect(0, 0, __frame.value().size[1] / 2 * 2, __frame.value().size[0] / 2 * 2));
        cv::Mat frame;
        cv::resize(_frame, frame, cv::Size(_frame.size[1] / 2, _frame.size[0] / 2), 0, 0,
                    cv::INTER_LINEAR);

        cv::Mat imageBGRAL;
        cv::cvtColor(frame, imageBGRAL, cv::COLOR_BGR2BGRA);

        _imageLeft = imageBGRAL.clone();
        QImage imgL(_imageLeft.value().data, _imageLeft.value().cols, _imageLeft.value().rows, QImage::Format_RGB32);
        QPixmap pixmapL = QPixmap::fromImage(imgL);
        _cameraLeft->setPixmap(pixmapL);

        cv::Mat paddedFrame;
        int longerEdge = std::max(frame.size[0], frame.size[1]);
        int vPadding = std::max(0, (longerEdge - frame.size[0]) / 2);
        int hPadding = std::max(0, (longerEdge - frame.size[1]) / 2);
        cv::copyMakeBorder(frame, paddedFrame, vPadding, vPadding, hPadding, hPadding, cv::BORDER_ISOLATED);

        cv::Mat downscaled;
        cv::resize(paddedFrame, downscaled, cv::Size(paddedFrame.size[0] / 2, paddedFrame.size[1] / 2), 0, 0,
                    cv::INTER_LINEAR);
        at::Tensor frameTensor = cv2ToTensor(downscaled, true).cuda();

        at::Tensor pred = ((model->forward(frameTensor) + 1) * 127.5)
                                .detach()
                                .clamp(0, 255)
                                .to(torch::kU8)
                                .to(torch::kCPU);
        cv::Mat predCv = tensorToCv2(pred, true);
        cv::Mat upscaled;
        cv::resize(predCv, upscaled, cv::Size(paddedFrame.size[0], paddedFrame.size[1]), 0, 0,
                    cv::INTER_LINEAR);
        cv::Mat cropped = upscaled(cv::Rect(hPadding, vPadding, frame.size[1], frame.size[0]));


        cv::Mat imageBGRAR;
        cv::cvtColor(cropped, imageBGRAR, cv::COLOR_BGR2BGRA);

        _imageRight = imageBGRAR.clone();
        QImage imgR(_imageRight.value().data, _imageRight.value().cols, _imageRight.value().rows, QImage::Format_RGB32);
        QPixmap pixmapR = QPixmap::fromImage(imgR);
        _cameraRight->setPixmap(pixmapR);
    }
}