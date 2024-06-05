#include "common/model_manager.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<modelManager::PretrainedModel> modelManager::getAllModels() {
    std::vector<modelManager::PretrainedModel> models;
    models.push_back(modelManager::style_monet);
    models.push_back(modelManager::style_cezanne);
    models.push_back(modelManager::style_ukiyoe);
    models.push_back(modelManager::style_vangogh);
    return models;
}

std::string modelManager::pretrainedModelToString(PretrainedModel model) {
    switch (model) {
    case PretrainedModel::style_cezanne:
        return "style_cezanne";
    case PretrainedModel::style_monet:
        return "style_monet";
    case PretrainedModel::style_ukiyoe:
        return "style_ukiyoe";
    case PretrainedModel::style_vangogh:
        return "style_vangogh";
    default:
        throw std::runtime_error("What a terrible failure");
    }
}

std::optional<modelManager::PretrainedModel>
modelManager::stringToPretrainedModel(std::string modelString) {
    if (modelString == "style_cezanne") {
        return PretrainedModel::style_cezanne;
    } else if (modelString == "style_monet") {
        return PretrainedModel::style_monet;
    } else if (modelString == "style_ukiyoe") {
        return PretrainedModel::style_ukiyoe;
    } else if (modelString == "style_vangogh") {
        return PretrainedModel::style_vangogh;
    } else {
        return std::nullopt;
    }
}

std::optional<std::set<modelManager::PretrainedModel>>
modelManager::getDownloadedModels() {
    std::string path = "./models";

    std::set<modelManager::PretrainedModel> availableModels{};

    if (!std::filesystem::is_directory(std::filesystem::path(path))) {
        return availableModels;
    }

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            continue;
        }

        auto filename = entry.path().filename();
        size_t lastindex = filename.string().find_last_of(".");
        std::string rawname = filename.string().substr(0, lastindex);

        auto modelFromString = stringToPretrainedModel(rawname);

        if (!modelFromString) {
            return std::nullopt;
        }

        if (modelFromString) {
            availableModels.insert(modelFromString.value());
        }
    }

    return std::make_optional(availableModels);
}

std::map<modelManager::PretrainedModel, std::string> _modelToUrl{
    {modelManager::PretrainedModel::style_cezanne,
     "https://docs.google.com/"
     "uc?export=download&id=1-x6kLQ3AxcgQCHQ9_HxDajizQM9klUBK"},
    {modelManager::PretrainedModel::style_monet,
     "https://docs.google.com/"
     "uc?export=download&id=12l7SQAvWpc3ZHaee46PeUv75_Z7SbzF-"},
    {modelManager::PretrainedModel::style_ukiyoe,
     "https://docs.google.com/"
     "uc?export=download&id=1MkSuU4Zk4fbdatM454svadpeP9vmb9CY"},
    {modelManager::PretrainedModel::style_vangogh,
     "https://docs.google.com/"
     "uc?export=download&id=1fZIkD0St9AJ2MvoWU_aMXleaOpHcPvR5"},
};

std::optional<std::filesystem::path>
modelManager::_downloadModel(modelManager::PretrainedModel model) {
    if (!fs::is_directory("models") || !fs::exists("models")) {
        fs::create_directory("models");
    }

    std::string url = _modelToUrl[model];

    std::string command = "curl -L \"" + url + "\" -o models/" +
                          modelManager::pretrainedModelToString(model) + ".ts";
    std::cout << command << std::endl;
    auto returnCode = system(command.c_str());

    if (returnCode) {
        return std::nullopt;
    }

    return modelManager::_getModelPath(model);
}

std::optional<std::filesystem::path>
modelManager::_getModelPath(modelManager::PretrainedModel model) {
    fs::path modelPath =
        "models/" + modelManager::pretrainedModelToString(model) + ".ts";
    if (!fs::exists(modelPath)) {
        return std::nullopt;
    }
    return modelPath;
}

std::optional<std::filesystem::path>
modelManager::getOrDownloadModelPath(modelManager::PretrainedModel model) {
    if (!fs::is_directory("models") || !fs::exists("models")) {
        fs::create_directory("models");
    }

    auto downloadedModels = modelManager::getDownloadedModels();

    if (downloadedModels->contains(model)) {
        auto modelPath = modelManager::_getModelPath(model);
        return modelPath;
    } else {
        auto modelPath = modelManager::_downloadModel(model);
        return modelPath;
    }
}