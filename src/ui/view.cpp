#include "ui/view.hpp"
#include "ui/pages/camera_page.hpp"
#include "ui/pages/image_page.hpp"
#include "ui/pages/models_page.hpp"

View::View(QWidget *parent) : QStackedWidget(parent) {
    setupUi();
}

void View::setupUi() {
    // region Create pages
    _imagePage = std::make_shared<ImagePage>(this);
    _cameraPage = std::make_shared<CameraPage>(this);
    _modelsPage = std::make_shared<ModelsPage>(this);

    this->addWidget(_imagePage.get());
    this->addWidget(_cameraPage.get());
    this->addWidget(_modelsPage.get());
    // endregion
}