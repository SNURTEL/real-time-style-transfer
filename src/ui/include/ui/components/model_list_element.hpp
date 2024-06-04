#ifndef STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP
#define STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP

#include <QWidget>
#include "common/model_manager.hpp"

class QHBoxLayout;

class QLabel;

class QPushButton;

/**
 * @brief List elements that represents model
 */
class ModelListElement : public QWidget {
public:
    ModelListElement(QWidget *parent, modelManager::PretrainedModel model);

    /**
     * @brief Setups Ui for element
     */
    void setupUi();

    /**
     * @brief Updates Ui state
     */
    void update();
private:
    modelManager::PretrainedModel _model;
    std::shared_ptr<QHBoxLayout> _layout;
    std::shared_ptr<QLabel> _name;
    std::shared_ptr<QLabel> _status;
    std::shared_ptr<QPushButton> _button;
};


#endif //STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP
