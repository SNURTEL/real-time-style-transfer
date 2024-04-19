#ifndef STYLE_APPLICATION_MODEL_MANAGER_HPP
#define STYLE_APPLICATION_MODEL_MANAGER_HPP

#include <torch/script.h>
#include <opencv2/core.hpp>

class ModelManager {
public:
    explicit ModelManager();

    bool loadModel(std::string filename);

    int predict(at::Tensor input);

    static std::optional<at::Tensor> loadImage(std::string filename);

private:
    static torch::Tensor to_tensor(cv::Mat image);

    std::shared_ptr<torch::jit::Module> module;
};


#endif //STYLE_APPLICATION_MODEL_MANAGER_HPP
