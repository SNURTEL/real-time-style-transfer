#ifndef STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP
#define STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP

#include "common/model_manager.hpp"
#include <QWidget>
#include <functional>

class QHBoxLayout;

class QLabel;

class QPushButton;

class State;

enum class ModelListElementState {
    NotDownloaded,
    Downloading,
    Downloaded,
    Active,
    Unknown
};

/**
 * @brief List elements that represents model
 */
class ModelListElement : public QWidget {
  public:
    ModelListElement(QWidget *parent, modelManager::PretrainedModel model,
                     std::shared_ptr<State> state,
                     std::function<void()> updateUiCallback);

    /**
     * @brief Setups Ui for element
     */
    void setupUi();

    /**
     * @brief Updates state
     */
    void updateState();

    /**
     * @brief Updates Ui state
     */
    void updateUi();

  private:
    ModelListElementState _innerState;
    std::shared_ptr<State> _state;
    modelManager::PretrainedModel _model;
    std::shared_ptr<QHBoxLayout> _layout;
    std::shared_ptr<QLabel> _name;
    std::shared_ptr<QLabel> _status;
    std::shared_ptr<QPushButton> _button;
    std::shared_ptr<QLabel> _spinner;
    std::function<void()> _updateStaneAndUiCallback;

  private slots:

    void onButtonClicked();
    void onDownloadComplete();
};

#endif // STYLE_APPLICATION_UI_COMPONENTS_MODEL_LIST_ELEMENT_HPP
