#ifndef STYLE_APPLICATION_UI_STATE_HPP
#define STYLE_APPLICATION_UI_STATE_HPP

#include <optional>

#include "common/model.hpp"
#include "common/model_manager.hpp"

class Downloader;

/**
 * @brief State of application
 */
class State {
public:
    State();

    /**
     * @brief Get active model
     * @return std::optional<modelManager::PretrainedModel> Active model
     */
    std::optional<modelManager::PretrainedModel> getActiveModel();

    /**
     * @brief Set active model
     * @param model New model
     */
    void setActiveModel(modelManager::PretrainedModel model);

    /**
     * @brief Get downloader
     */
    std::shared_ptr<Downloader> getDownloader();

    /**
     * @brief Loads model
     */
    bool ensureModelLoaded();

    /**
     * @brief Get model
     */
    std::shared_ptr<Model> getModel();

private:
    bool _loaded;
    std::optional<modelManager::PretrainedModel> _activeModel;
    std::shared_ptr<Downloader> _downloader;
    std::shared_ptr<Model> _model;
};


#endif //STYLE_APPLICATION_UI_STATE_HPP
