#ifndef STYLE_APPLICATION_UI_STATE_HPP
#define STYLE_APPLICATION_UI_STATE_HPP

#include <optional>

#include "common/model_manager.hpp"

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

private:
    std::optional<modelManager::PretrainedModel> _activeModel;
};


#endif //STYLE_APPLICATION_UI_STATE_HPP
