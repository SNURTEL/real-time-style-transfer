#ifndef STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP

#include <QWidget>

#include "ipage.hpp"


class ModelsPage : public QWidget, public IPage {
public:
    ModelsPage(QWidget *parent);

    void setupUi();

    void activatePage() override;

    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
