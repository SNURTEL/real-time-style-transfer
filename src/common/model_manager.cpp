#include <boost/python/list.hpp>
#include <cassert>
#include <cmath>
#include <map>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <iostream>
#include "common/model_manager.hpp"
#include <boost/python.hpp>
#include <boost/algorithm/string.hpp>
#include <Python.h>

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

    Py_Initialize();

    try
    {
        py::object sys = py::import("sys");

        std::cout << "Interpreter path is " << py::extract<std::string>(sys.attr("executable"))() << std::endl;

        py::object pathlib = py::import("pathlib");
        py::object Path = pathlib.attr("Path");
        py::object pythonpath = sys.attr("path");
        pythonpath.attr("append")("/home/tomek/zpr/24l-zpr/scripts");

        // TODO adjust for Windows
        py::object executablePath = Path(py::extract<std::string>(sys.attr("executable"))());
        py::object versionInfo = sys.attr("version_info");


        py::object sitePackagesPath = py::str(executablePath.attr("parents")[1]) + "/lib/python" + py::str(versionInfo.attr("major")) + "." + py::str(versionInfo.attr("minor")) + "/site-packages";
        py::object sitePackages64Path = py::str(executablePath.attr("parents")[1]) + "/lib64/python" + py::str(versionInfo.attr("major")) + "." + py::str(versionInfo.attr("minor")) + "/site-packages";

        std::cout << "Inferred site-packages path is " << py::extract<std::string>(py::str(sitePackagesPath))() << std::endl;

        pythonpath.attr("append")( py::extract<std::string>(py::str(sitePackagesPath))());
        pythonpath.attr("append")(py::extract<std::string>(py::str(sitePackages64Path))());
        // pythonpath = py::list(py::extract<std::string>(py::str(sitePackagesPath))());

        py::object create_cyclegan_pretrained = py::import("create_cyclegan_pretrained");
        py::object modelEnum = create_cyclegan_pretrained.attr("Model");
        py::object modelEnumValue = modelEnum(modelManager::pretrainedModelToString(model));
        py::object res = create_cyclegan_pretrained.attr("get_model")(modelEnumValue);


        std::cout <<  py::extract<std::string>(py::str(res))() << std::endl;

    } catch (const py::error_already_set&) {
        PyErr_Print();
        return std::nullopt;
    }


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