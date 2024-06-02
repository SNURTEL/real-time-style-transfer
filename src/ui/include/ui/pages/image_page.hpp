#ifndef STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP

#include <QWidget>

#include "page.hpp"

class QPushButton;


class ImagePage : public Page {
public:
    explicit ImagePage(QWidget *parent);

    void setupUi();

    void activatePage() override;

    void deactivatePage() override;

private:
    QPushButton *btn;
};


#endif //STYLE_APPLICATION_UI_PAGES_IMAGE_PAGE_HPP
