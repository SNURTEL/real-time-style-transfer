#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QSizePolicy>
#include <QString>
#include <QFileDialog>

#include "ui/pages/image_page.hpp"
#include "ui/state.hpp"
#include "common/image.hpp"
#include "common/utils.hpp"

ImagePage::ImagePage(QWidget *parent, std::shared_ptr<State> state) : Page(parent, state) {
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
    connect(_loadImageButton.get(), &QPushButton::clicked, this, &ImagePage::onLoadImageButtonClicked);


    _transformButton = std::make_shared<QPushButton>(this);
    _transformButton->setText(QString::fromUtf8("Transform"));
    connect(_transformButton.get(), &QPushButton::clicked, this, &ImagePage::onTransformButtonClicked);

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

void ImagePage::deactivatePage() {
    Page::deactivatePage();
}

void ImagePage::onLoadImageButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(nullptr, QString::fromUtf8("Choose file"), "", QString::fromUtf8("Images (*.png *.jpg *.bmp)"));

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

    auto material = image::loadImage(_inputImagePath.value());
    if (!material) {
        _inputImagePath = std::nullopt;
        updateUi();
    }
    auto tensor = cv2ToTensor(material.value());


    return;
}


