#include <optional>
#include <iostream>
#include <filesystem>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <torch/csrc/jit/api/module.h>
#include <torch/script.h>

#include "common/model.hpp"

at::Tensor Model::forward(const at::Tensor &input) {
    auto inputConv = input.to(torch::kFloat32);

    std::vector<torch::jit::IValue> batch;
    batch.push_back(inputConv);

    return _module.forward(batch).toTensor();
}

Model::Model(const torch::jit::Module &module) : _module(module){};

std::optional<Model> Model::fromFile(const std::string &path) {
    std::cout << std::filesystem::current_path().string() << std::endl;
    std::cout << path << std::endl;
    try {
        return std::make_optional(Model(torch::jit::load(path)));
    } catch (const c10::Error &e) {
        std::cerr << e.what() << "\n";
        return std::nullopt;
    }
}
