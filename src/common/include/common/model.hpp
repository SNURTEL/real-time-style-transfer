#include <string>
#include <torch/script.h>

class Model {
  public:
    static std::optional<Model> fromFile(const std::string &path);

    at::Tensor forward(const at::Tensor &input);

  private:
    torch::jit::Module _module;
    explicit Model(const torch::jit::Module &module);
    Model();
};
