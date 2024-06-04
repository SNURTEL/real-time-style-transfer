#ifndef STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP
#define STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP

#include <filesystem>
#include <map>
#include <optional>
#include <set>
#include <string>

namespace modelManager {
enum PretrainedModel {
    style_monet,
    style_cezanne,
    style_ukiyoe,
    style_vangogh
};

std::vector<modelManager::PretrainedModel> getAllModels();

std::string pretrainedModelToString(PretrainedModel);

std::optional<PretrainedModel> stringToPretrainedModel(std::string);

std::optional<std::set<PretrainedModel>> getDownloadedModels();

std::optional<std::filesystem::path> _downloadModel(PretrainedModel);

std::optional<std::filesystem::path> _getModelPath(PretrainedModel);

std::optional<std::filesystem::path> getOrDownloadModelPath(PretrainedModel);
} // namespace modelManager

#endif //STYLE_APPLICATION_COMMON_MODEL_MANAGER_HPP