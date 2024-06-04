#include "ui/state.hpp"
#include "ui/downloader.hpp"

State::State() {
    _activeModel = std::nullopt;
    _downloader = std::make_shared<Downloader>();
}

std::optional<modelManager::PretrainedModel> State::getActiveModel() {
    return _activeModel;
}

void State::setActiveModel(modelManager::PretrainedModel model) {
    _activeModel = model;
}

std::shared_ptr<Downloader> State::getDownloader() {
    return _downloader;
}
