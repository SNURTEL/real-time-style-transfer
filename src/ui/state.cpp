#include "ui/state.hpp"
#include "common/model.hpp"
#include "ui/downloader.hpp"

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

std::shared_ptr<Downloader> State::getDownloader() {
    return _downloader;
}

void State::ensureModelLoaded() {
    if (_loaded) {
        return;
    }

    if (!_activeModel) {
        return;
    }

    _loaded = true;
    std::optional<std::filesystem::path> modelPath = modelManager::getOrDownloadModelPath(_activeModel.value());
    if (!modelPath) {
        return;
    }

    auto model = Model::fromFile(modelPath.value().string());
    if (!model) {
        return;
    }

    _model = std::make_shared<Model>(std::move(model.value()));
}

void State::useModel() {
    ensureModelLoaded();
}
