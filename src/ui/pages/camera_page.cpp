#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
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
        //        _camera = std::make_shared<QCamera>(QCameraDevice::FrontFace);
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
    _button->setText(QString::fromUtf8("Run standalone"));
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

void CameraPage::deactivatePage() { Page::deactivatePage(); }

void CameraPage::onButtonClicked() {
    std::shared_ptr<Model> model = _state->getModel();

    auto cam = Camera::build();

    if (!cam) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return;
    }

    _button->setDisabled(true);
    for (;;) {
        auto frame = cam->nextFrame();
        if (!frame) {
            std::cerr << "Error getting frame" << std::endl;
            return;
        }
        cv::Mat scaledFrame;
        cv::resize(frame.value(), scaledFrame, cv::Size(256, 256), 0, 0,
                   cv::INTER_LINEAR);
        at::Tensor frameTensor = cv2ToTensor(scaledFrame, true).cuda();

        at::Tensor pred = ((model->forward(frameTensor) + 1) * 127.5)
                              .detach()
                              .clamp(0, 255)
                              .to(torch::kU8)
                              .to(torch::kCPU);
        cv::Mat predCv = tensorToCv2(pred, true);
        cv::Mat upscaled;
        cv::resize(predCv, upscaled, cv::Size(1024, 1024), 0, 0,
                   cv::INTER_LINEAR);

        cv::imshow("Live", upscaled.clone());
        // cv::imshow("Live", frame.value().clone()); // @temp

        if (cv::waitKey(5) >= 0) {
            break;
        }

        if (!this->isVisible() || !this->isEnabled()) {
            break;
        }
    }

    _button->setDisabled(false);
}
