#ifndef STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP

#include <QWidget>

#include "page.hpp"

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
     * @brief Activates page
     */
    void activatePage() override;

    /**
     * @brief Deactivates page
     */
    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_CAMERA_P