#include "common/modelLoadingError.hpp"

const char* ModelLoadingError::what() const noexcept 
{
    return what_message.c_str();
}

ModelLoadingError::ModelLoadingError(std::string message) : std::runtime_error(message) {};
