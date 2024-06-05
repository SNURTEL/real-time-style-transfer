#ifndef STYLE_APPLICATION_COMMON_MODEL_HPP
#define STYLE_APPLICATION_COMMON_MODEL_HPP

#include <istream>
#include <string>
#undef slots
#include <torch/script.h>
#define slots Q_SLOTS

/**
 * @brief Wrapper around a Torch module
 *
 */
class Model {
  public:
    /**
     * @brief Load a traced model
     *
     * @param path Traced model (.pt) path
     * @return std::optional<Model> Model or std::nullopt if loading failed
     */
    static std::optional<Model> fromFile(const std::string &path);

    static std::optional<Model> fromStream(std::istream &stream);

    /**
     * @brief Feed the tensor through the network
     *
     * @param input Inpot tensor
     * @return at::Tensor Result
     */
    at::Tensor forward(const at::Tensor &input);

  private:
    torch::jit::Module _module;
    explicit Model(const torch::jit::Module &module);
    Model();
};

#endif // STYLE_APPLICATION_COMMON_MODEL_HPP