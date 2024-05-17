#include <exception>
#include <stdexcept>
#include <string>

class ModelLoadingError : public std::runtime_error {
    std::string what_message;

  public:
    explicit ModelLoadingError(std::string);

    const char *what() const noexcept override;
};