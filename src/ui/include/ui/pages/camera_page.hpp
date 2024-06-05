/**
 * @brief Camera page module
 */
#ifndef STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP

#include <QWidget>

#include "page.hpp"

class QVBoxLayout;

class QHBoxLayout;

class QLabel;

class QPushButton;

class State;

/**
 * @brief Camera inference page
 */
class CameraPage : public Page {
  public:
    explicit CameraPage(QWidget *parent, std::shared_ptr<State> state);

    /**
     * @brief Setups UI for Camera Page
     */
    void setupUi();

    /**
     * @brief Updates UI
     */
    void updateUi();

    /**
     * @brief Activates page
     */
    void activatePage() override;

    /**
     * @brief Deactivates page
     */
    void deactivatePage() override;

  private slots:
    void onButtonClicked();

  private:
    std::shared_ptr<QVBoxLayout> _layout;
    std::shared_ptr<QHBoxLayout> _camerasLayout;
    std::shared_ptr<QLabel> _title;
    std::shared_ptr<QLabel> _cameraLeft;
    std::shared_ptr<QLabel> _cameraRight;
    std::shared_ptr<QPushButton> _button;
};

#endif // STYLE_APPLICATION_UI_PAGES_CAMERA_P