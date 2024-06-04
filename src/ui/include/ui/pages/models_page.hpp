#ifndef STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP

#include <QWidget>

#include "page.hpp"

class QVBoxLayout;

class QLabel;

class QListWidget;

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

private:
    std::shared_ptr<QVBoxLayout> _layout;
    std::shared_ptr<QLabel> _title;
    std::shared_ptr<QListWidget> _listWidget;
};


#endif //STYLE_APPLICATION_UI_PAGES_MODELS_P