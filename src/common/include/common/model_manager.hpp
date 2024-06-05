/**
 * @brief Module for managing models
 */
#ifndef STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP
#define STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP

#include <filesystem>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace modelManager {
enum PretrainedModel {
    style_monet,
    style_cezanne,
    style_ukiyoe,
    style_vangogh
};

/**
 * @brief Get all available models
 * @return Vector of available models
 */
std::vector<modelManager::PretrainedModel> getAllModels();

/**
 * @brief Get name of model
 * @return Name of model
 */
std::string pretrainedModelToString(PretrainedModel);

/**
 * @brief Get model by name
 * @return Model
 */
std::optional<PretrainedModel> stringToPretrainedModel(std::string);

/**
 * Get set of downloaded models
 * @return Set of downloaded models
 */
std::optional<std::set<PretrainedModel>> getDownloadedModels();

/**
 * @brief Download model
 * @return Path where model is located
 */
std::optional<std::filesystem::path> _downloadModel(PretrainedModel);

/**
 * @brief Get model path
 * @return Path where model is located
 */
std::optional<std::filesystem::path> _getModelPath(PretrainedModel);

/**
 * @brief Get model path or download
 * @return Path where model is located
 */
std::optional<std::filesystem::path> getOrDownloadModelPath(PretrainedModel);
} // namespace modelManager

#endif // STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP