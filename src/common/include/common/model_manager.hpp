#include <map>
#include <optional>
#include <filesystem>
#include <string>
#include <set>


namespace modelManager {
    enum PretrainedModel { style_monet, style_cezanne, style_ukiyoe, style_vangogh };

    std::string pretrainedModelToString(PretrainedModel);

    std::optional<PretrainedModel> stringToPretrainedModel(std::string);

    std::optional<std::set<PretrainedModel>> getDownloadedModels();

    std::optional<std::filesystem::path> downloadModel(PretrainedModel);
}