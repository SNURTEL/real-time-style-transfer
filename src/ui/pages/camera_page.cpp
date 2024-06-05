#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "ui/pages/camera_page.hpp"
#include "ui/state.hpp"

#define CAMERAS 1

CameraPage::CameraPage(QWidget *parent, std::shared_ptr<State> state) : Page(parent, state) {
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

    this->setLayout(_layout.get());
    _layout->addLayout(_camerasLayout.get());
}

void CameraPage::updateUi() {
    if (CAMERAS > 0) {
        _title->setText("Camera Inference");
        _title->setStyleSheet("QLabel { color : #78e08f; }");
    }
    else {
        _title->setText("No camera available");
        _title->setStyleSheet("QLabel { color : #e55039; }");
    }
}

void CameraPage::activatePage() {
    Page::activatePage();
}

void CameraPage::deactivatePage() {
    Page::deactivatePage();
}
