#include "ui/view.hpp"
#include "ui/pages/camera_page.hpp"
#include "ui/pages/image_page.hpp"
#include "ui/pages/models_page.hpp"
#include "ui/pages/epage.hpp"

View::View(QWidget *parent) : QStackedWidget(parent) {
    setupUi();
}

void View::setupUi() {
    _pages[EPage::ImageInference] = std::make_shared<ImagePage>(this);
    _pages[EPage::CameraInference] = std::make_shared<CameraPage>(this);
    _pages[EPage::Models] = std::make_shared<ModelsPage>(this);

    _activePage = getPage(EPage::ImageInference);

    for (auto & page : _pages) {
        this->addWidget(page.second.get());
    }
    // endregion
}

void View::switchPage(EPage page) {
    std::shared_ptr<Page> pageImpl = getPage(page);

    int index = indexOf(pageImpl.get());
    if (index == -1) {
        throw std::runtime_error("Page is not added to view!");
    }

    _activePage->deactivatePage();

    setCurrentIndex(index);
    _activePage = pageImpl;
    _activePage->activatePage();
}

std::shared_ptr<Page> View::getPage(EPage page) {
    if (!_pages.contains(page)) {
        throw std::runtime_error("Cannot find this page!");
    }

    return _pages[page];
}
