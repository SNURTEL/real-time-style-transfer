#include <memory>
#include <utility>
#include <fmt/core.h>

#include "../model/manager.hpp"
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QFileDialog>

#include "main_window.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Style Transfer Main Window");
    resize(400, 300);

    loadButton = std::make_shared<QPushButton>("Load", this);
    loadButton->setGeometry(10, 10, 100, 50);
    QObject::connect(loadButton.get(), &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);

    runButton = std::make_shared<QPushButton>("Run", this);
    runButton->setGeometry(130, 10, 100, 50);
    QObject::connect(runButton.get(), &QPushButton::clicked, this, &MainWindow::onRunButtonClicked);

    image = std::make_shared<QLabel>(this);
    text = std::make_shared<QLabel>(this);
    text->setGeometry(130, 80, 100, 50);

    QPixmap pixmap;

    if (pixmap.load(":/resources/template.jpg")) {
        setImage(pixmap);
    } else {
        qDebug() << "Cannot load template image";
    }
}

void MainWindow::onLoadButtonClicked() {
    QString filename = QFileDialog::getOpenFileName(nullptr, "Wybierz plik", "", "Obrazy (*.png *.jpg *.bmp)");

    if (!filename.isEmpty()) {
        QPixmap pixmap;
        if (pixmap.load(filename)) {
            setImage(pixmap);
        }

        imageFilename = filename.toStdString();
    } else {
        QMessageBox::warning(this, "[Image]", "No image selected. Try again!");
    }
}

void MainWindow::onRunButtonClicked() {
    auto tensor = ModelManager::loadImage(imageFilename);

    if (!tensor.has_value()) {
        QMessageBox::warning(this, "[Run]", "Incorrect image. Cannot load image in model");
        return;
    }

    int out_class = modelManager.get()->predict(tensor.value());
    if (out_class == -1) {
        QMessageBox::warning(this, "[Run]", "Model is not loaded. Restart application");
        return;
    }

    std::map<int, std::string> class_to_name{
            {0, "T-shirt/top"},
            {1, "Trouser"},
            {2, "Pullover"},
            {3, "Dress"},
            {4, "Coat"},
            {5, "Sandal"},
            {6, "Shirt"},
            {7, "Sneaker"},
            {8, "Bag"},
            {9, "Ankle boot"}
    };

    text->setText(
            QString::fromStdString(fmt::format("Predicted class is: {} [#{}]", class_to_name[out_class], out_class)));
    QMessageBox::information(this, "[Run]", "Successful prediction");
}

void MainWindow::setImage(QPixmap &map) {
    image->setPixmap(map);
    image->setGeometry(10, 80, map.width(), map.height());
}

void MainWindow::setModelManager(std::shared_ptr<ModelManager> manager) {
    modelManager = std::move(manager);
}
