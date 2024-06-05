#include "ui/state.hpp"
#include "common/model.hpp"
#include "ui/downloader.hpp"
#include <QWidget>

State::State() {
    _loaded = false;
    _activeModel = std::nullopt;
    _downloader = std::make_shared<Downloader>();
}

std::optional<modelManager::PretrainedModel> State::getActiveModel() {
    return _activeModel;
}

void State::setActiveModel(modelManager::PretrainedModel model) {
    _activeModel = model;
    _loaded = false;
}

std::shared_ptr<Downloader> State::getDownloader() { return _downloader; }

bool State::ensureModelLoaded() {
    if (_loaded) {
        return true;
    }

    if (!_activeModel) {
        return false;
    }

    _loaded = true;
    std::optional<std::filesystem::path> modelPath =
        modelManager::getOrDownloadModelPath(_activeModel.value());
    if (!modelPath) {
        return false;
    }

    auto model = Model::fromFile(modelPath.value().string());
    if (!model) {
        qDebug() << "Issues with model";
        return false;
    }
    qDebug() << "Model loaded";

    _model = std::make_shared<Model>(std::move(model.value()));
    qDebug() << "As pointer now";
    return true;
}

std::shared_ptr<Model> State::getModel() {
    if (!ensureModelLoaded()) {
        throw std::runtime_error("Cannot get model");
    }

    return _model;
}