#include "manager.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <torch/script.h>

ModelManager::ModelManager() {}

bool ModelManager::loadModel(std::string filename) {
    try {
        module = std::make_shared<torch::jit::Module>(
            std::move(torch::jit::load(filename)));
    } catch (const c10::Error &e) {
        return false;
    }

    return true;
}

std::optional<at::Tensor> ModelManager::loadImage(std::string filename) {
    std::string path = cv::samples::findFile(filename);
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        return std::nullopt;
    }

    return std::make_optional(std::move(to_tensor(image)));
}

int ModelManager::predict(at::Tensor input) {
    input = input.to(torch::kFloat32);

    std::vector<torch::jit::IValue> batch;
    batch.push_back(input);

    if (!module) {
        return -1;
    }

    auto output = module.get()->forward(batch);
    int out_class = torch::argmax(output.toTensor()).item<int>();
    return out_class;
}

torch::Tensor ModelManager::to_tensor(cv::Mat image) {
    return torch::from_blob(image.data,
                            {image.rows, image.cols, image.channels()},
                            torch::kByte)
        .unsqueeze(0);
}
