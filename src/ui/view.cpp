#include "ui/view.hpp"
#include "ui/pages/camera_page.hpp"
#include "ui/pages/image_page.hpp"
#include "ui/pages/models_page.hpp"
#include "ui/pages/page_index.hpp"

View::View(QWidget *parent) : QStackedWidget(parent) {
    setupUi();
    _currentPageIndex = PageIndex::ImageInference;
}

void View::setupUi() {
    _pages[PageIndex::ImageInference] = std::make_shared<ImagePage>(this);
    _pages[PageIndex::CameraInference] = std::make_shared<CameraPage>(this);
    _pages[PageIndex::Models] = std::make_shared<ModelsPage>(this);

    for (auto &page: _pages) {
        this->addWidget(page.second.get());
    }
}

void View::switchPage(PageIndex pageIndex) {
    std::shared_ptr<Page> page = getPage(pageIndex);
    std::shared_ptr<Page> currentPage = getCurrentPage();

    int index = indexOf(page.get());
    if (index == -1) {
        throw std::runtime_error("Page is not added to view!");
    }

    currentPage->deactivatePage();
    setCurrentIndex(index);
    page->activatePage();
    _currentPageIndex = pageIndex;
}

std::shared_ptr<Page> View::getPage(PageIndex page) {
    if (!_pages.contains(page)) {
        throw std::runtime_error("Cannot find this page!");
    }

    return _pages[page];
}

std::shared_ptr<Page> View::getCurrentPage() {
    return getPage(_currentPageIndex);
}

PageIndex View::getCurrentPageIndex() {
    return _currentPageIndex;
}
