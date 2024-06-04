#ifndef STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP

#include <QWidget>

#include "page.hpp"

/**
 * @brief Models page
 */
class ModelsPage : public Page {
public:
    explicit ModelsPage(QWidget *parent);

    /**
     * @brief Setups UI for Camera Page
     */
    void setupUi();

    /**
     * @brief Activates page
     */
    void activatePage() override;

    /**
     * @brief Deactivates page
     */
    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_MODELS_P