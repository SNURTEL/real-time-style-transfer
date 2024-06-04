#include "ui/state.hpp"

State::State() {
    _activeModel = std::nullopt;
}

std::optional<modelManager::PretrainedModel> State::getActiveModel() {
    return _activeModel;
}

void State::setActiveModel(modelManager::PretrainedModel model) {
    _activeModel = model;
}
