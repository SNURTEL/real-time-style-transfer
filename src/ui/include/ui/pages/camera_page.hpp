#ifndef STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP

#include <QWidget>

#include "ipage.hpp"


class CameraPage : public QWidget, public IPage {
public:
    CameraPage(QWidget *parent);

    void setupUi();

    void activatePage() override;

    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_CAMERA_PAGE_HPP
