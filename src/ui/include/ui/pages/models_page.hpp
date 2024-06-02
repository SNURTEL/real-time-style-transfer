#ifndef STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP

#include <QWidget>

#include "page.hpp"


class ModelsPage : public Page {
public:
    ModelsPage(QWidget *parent);

    void setupUi();

    void activatePage() override;

    void deactivatePage() override;
};


#endif //STYLE_APPLICATION_UI_PAGES_MODELS_PAGE_HPP
