#ifndef STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP

#include <QWidget>

#include "page.hpp"


class CameraPage : public Page {
public:
    CameraPage(QWidget *parent);

    void setupUi();

    void activatePage() override;

    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
