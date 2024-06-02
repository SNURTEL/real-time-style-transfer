#include <cassert>
#include <map>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include "common/model_manager.hpp"
#include <boost/python.hpp>

namespace py = boost::python;

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

    py::object sys = py::import("sys");



    // C API
    // std::cout << "Initialize" << std::endl; 
    // Py_Initialize();

    // PyObject *sys = PyImport_ImportModule("sys");
    // PyObject *path = PyObject_GetAttrString(sys, "path");
    // PyList_Append(path, PyUnicode_FromString("scripts"));

    // std::cout << "Importing module" << std::endl; 
    // auto module = PyImport_ImportModule("test");
    // if (module == nullptr) {
    //     std::cout << "Module is null" << std::endl; 
    // }
    // std::cout << "Getting func" << std::endl; 
    // auto func = PyObject_GetAttrString(module, "main");
    // std::cout << "Calling func" << std::endl; 
    // auto res = PyObject_CallObject(func, PyTuple_New(0));
    // std::cout << PyLong_AsLong(res) << std::endl; 

    return std::nullopt;
}