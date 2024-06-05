#include <utility>

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "common/model_manager.hpp"
#include "ui/components/model_list_element.hpp"
#include "ui/downloader.hpp"
#include "ui/state.hpp"

ModelListElement::ModelListElement(QWidget *parent,
                                   modelManager::PretrainedModel model,
                                   std::shared_ptr<State> state,
                                   std::function<void()> updateStateAndUiCallback)
    : QWidget(parent) {
    _model = model;
    _state = std::move(state);
    _innerState = ModelListElementState::Unknown;
    _updateStaneAndUiCallback = updateStateAndUiCallback;
    setupUi();
    _updateStaneAndUiCallback();
}

void ModelListElement::setupUi() {
    _layout = std::make_shared<QHBoxLayout>(this);

    _name = std::make_shared<QLabel>(this);
    _status = std::make_shared<QLabel>(this);
    _button = std::make_shared<QPushButton>(this);
    _spinner = std::make_shared<QLabel>(this);

    _button->setDisabled(true);
    connect(_button.get(), &QPushButton::clicked, this,
            &ModelListElement::onButtonClicked);

    QPixmap pixmap("resources/loading.png");
    QPixmap resized =
        pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _spinner->setPixmap(resized);

    _layout->addWidget(_name.get());
    _layout->addWidget(_status.get());
    _layout->addWidget(_spinner.get());
    _layout->addWidget(_button.get());

    this->setLayout(_layout.get());
}

void ModelListElement::updateState() {
    auto downloadedModels = modelManager::getDownloadedModels();
    if (downloadedModels->contains(_model)) {
        if (_state->getActiveModel() == _model) {
            _innerState = ModelListElementState::Active;
        } else {
            _innerState = ModelListElementState::Downloaded;
        }
    } else {
        _innerState = ModelListElementState::NotDownloaded;
    }
}

void ModelListElement::updateUi() {
    std::string modelName = modelManager::pretrainedModelToString(_model);
    _name->setText(QString::fromUtf8(modelName.c_str()));

    _spinner->setVisible(false);

    switch (_innerState) {
    case ModelListElementState::NotDownloaded:
        _status->setText(QString::fromUtf8("Not downloaded"));
        _status->setStyleSheet("QLabel { color : #e55039; }");
        _button->setDisabled(false);
        _button->setText(QString::fromUtf8("Download"));
        break;
    case ModelListElementState::Downloading:
        _status->setText(QString::fromUtf8("Downloading"));
        _status->setStyleSheet("QLabel { color : #4a69bd; }");
        _button->setDisabled(true);
        _spinner->setVisible(true);
        break;
    case ModelListElementState::Downloaded:
        _status->setText(QString::fromUtf8("Downloaded"));
        _status->setStyleSheet("QLabel { color : #4a69bd; }");
        _button->setDisabled(false);
        _button->setText(QString::fromUtf8("Activate"));
        break;
    case ModelListElementState::Active:
        _status->setText(QString::fromUtf8("Active"));
        _status->setStyleSheet("QLabel { color : #78e08f; }");
        _button->setDisabled(true);
        _button->setText(QString::fromUtf8("Active"));
        break;
    case ModelListElementState::Unknown:
        _status->setText(QString::fromUtf8("Unknown"));
        _status->setStyleSheet("QLabel { color : #e55039; }");
        _button->setDisabled(true);
        _button->setText(QString::fromUtf8("Unknown"));
        break;
    }
}

void ModelListElement::onButtonClicked() {
    switch (_innerState) {
    case ModelListElementState::NotDownloaded:
        _innerState = ModelListElementState::Downloading;
        updateUi();
        update();
        repaint();
        _state->getDownloader()->download(_model);
        break;
    case ModelListElementState::Downloaded:
        _state->setActiveModel(_model);
        break;
    default:
        break;
    }

    _updateStaneAndUiCallback();
}

void ModelListElement::onDownloadComplete() {
    _innerState = ModelListElementState::Downloaded;

    _updateStaneAndUiCallback();
}
