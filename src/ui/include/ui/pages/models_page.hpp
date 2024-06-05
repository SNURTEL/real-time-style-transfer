/**
 * @brief Models Repository page module
 */
#ifndef STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP

#include <QWidget>

#include "page.hpp"
#include "ui/components/model_list_element.hpp"

class QVBoxLayout;

class QLabel;

class QListWidget;

class State;

/**
 * @brief Models page
 */
class ModelsPage : public Page {
  public:
    explicit ModelsPage(QWidget *parent, std::shared_ptr<State> state);

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

    /**
     * @brief Update children widgets
     */
    void updateChildren();

  private:
    std::shared_ptr<QVBoxLayout> _layout;
    std::shared_ptr<QLabel> _title;
    std::shared_ptr<QListWidget> _listWidget;
    std::list<ModelListElement *> _buttons;
};

#endif // STYLE_APPLICATION_UI_PAGES_MODELS_P