#include <cassert>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <Python.h>
#include "common/model_manager.hpp"

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

std::optional<modelManager::PretrainedModel> modelManager::stringToPretrainedModel(std::string modelString) {
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

std::optional<std::set<modelManager::PretrainedModel>> modelManager::getDownloadedModels() {
    std::string path = "./models";

    std::set<modelManager::PretrainedModel> availableModels {};

    for (const auto & entry : std::filesystem::directory_iterator(path)){
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

std::optional<std::filesystem::path> modelManager::downloadModel(modelManager::PretrainedModel model) {
    assert(model);
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                        "print('Today is', ctime(time()))");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }

    return std::nullopt;
}