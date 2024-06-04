#include <utility>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "ui/components/model_list_element.hpp"
#include "common/model_manager.hpp"

ModelListElement::ModelListElement(QWidget *parent, modelManager::PretrainedModel model) : QWidget(parent) {
    _model = model;
    setupUi();
    update();
}

void ModelListElement::setupUi() {
    _layout = std::make_shared<QHBoxLayout>(this);

    _name = std::make_shared<QLabel>(this);
    _status = std::make_shared<QLabel>(this);
    _button = std::make_shared<QPushButton>(this);

    _layout->addWidget(_name.get());
    _layout->addWidget(_status.get());
    _layout->addWidget(_button.get());

    this->setLayout(_layout.get());
}

void ModelListElement::update() {
    std::string modelName = modelManager::pretrainedModelToString(_model);
    _name->setText(QString::fromUtf8(modelName.c_str()));

    _button->setText("Unknown");

    auto downloadedModels = modelManager::getDownloadedModels();
    if (downloadedModels->contains(_model)) {
        _status->setText(QString::fromUtf8("Downloaded"));
        _status->setStyleSheet("QLabel { color : #78e08f; }");
    }
    else {
        _status->setText(QString::fromUtf8("Not downloaded"));
        _status->setStyleSheet("QLabel { color : #e55039; }");
    }


}
