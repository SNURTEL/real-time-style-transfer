#ifndef STYLE_APPLICATION_MODEL_MANAGER_HPP
#define STYLE_APPLICATION_MODEL_MANAGER_HPP

#include <opencv2/core.hpp>
#include <torch/script.h>

/**
 * @brief A class to manage loading PyTorch models and using them for inference
 *
 */
class ModelManager {
  public:
    explicit ModelManager();

    /**
     * @brief Loads the model from a given `.pt` file.
     *
     * @param filename Model file
     * @return true Model loaded successfully
     * @return false Model loading failed
     */
    bool loadModel(std::string filename);

    /**
     * @brief TODO Remove this: predit image class
     *
     * @param input Image tensor in format (N_CHANNELS, WIDTH, HEIGHT)
     * @return int Predicted class
     */
    int predict(at::Tensor input);

    /**
     * @brief Loads an image from file as cv::Mat in grayscale.
     *
     * @param filename Image filename.
     * @return std::optional<at::Tensor> Loaded image.
     */
    static std::optional<at::Tensor> loadImage(std::string filename);

  private:
    /**
     * @brief Converts an OpenCV image to a Torch tensor of `torch::kByte`.
     *
     * @param image OpenCV image
     * @return torch::Tensor Output tensor
     */
    static torch::Tensor to_tensor(cv::Mat image);

    /**
     * @brief Loaded module.
     *
     */
    std::shared_ptr<torch::jit::Module> module;
};

#endif // STYLE_APPLICATION_MODEL_MANAGER_HPP
