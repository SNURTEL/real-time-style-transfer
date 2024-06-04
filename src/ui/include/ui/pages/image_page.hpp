#ifndef STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP

#include <QWidget>

#include "page.hpp"

class QPushButton;

/**
 * @brief Image inference page
 */
class ImagePage : public Page {
public:
    explicit ImagePage(QWidget *parent);

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
    QPushButton *btn;
};


#endif //STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
