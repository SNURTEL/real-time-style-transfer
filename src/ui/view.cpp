#include <utility>

#include "ui/pages/page.hpp"
#include "ui/pages/page_index.hpp"
#include "ui/view.hpp"

View::View(QWidget *parent) : QStackedWidget(parent) {
    setupUi();
    _currentPageIndex = PageIndex::Nothing;
}

void View::setupUi() {}

void View::addPage(PageIndex pageIndex, std::shared_ptr<Page> page,
                   std::shared_ptr<QAction> action) {
    this->addWidget(page.get());

    connect(action.get(), &QAction::triggered, this,
            [this, pageIndex, action](bool checked = false) {
                if (pageIndex == getCurrentPageIndex()) {
                    action->setChecked(true);
                    return;
                }

                if (!checked) {
                    return;
                }

                this->switchPage(pageIndex);
            });

    _pages[pageIndex] = std::move(page);
    _actions[pageIndex] = action;

    if (_currentPageIndex == PageIndex::Nothing) {
        switchPage(pageIndex);
        action->setChecked(true);
    }
}

void View::switchPage(PageIndex pageIndex) {
    if (pageIndex == PageIndex::Nothing) {
        throw std::runtime_error("Cannot change to empty page");
    }

    // Deactivate current page
    if (_currentPageIndex != PageIndex::Nothing) {
        std::shared_ptr<Page> currentPage = getPage(_currentPageIndex);
        std::shared_ptr<QAction> currentPageAction =
            getPageAction(_currentPageIndex);
        currentPage->deactivatePage();
        currentPageAction->setChecked(false);
    }

    // Get new page
    std::shared_ptr<Page> page = getPage(pageIndex);

    int index = indexOf(page.get());
    if (index == -1) {
        throw std::runtime_error("Page is not added to view!");
    }

    // Activate new page
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

PageIndex View::getCurrentPageIndex() { return _currentPageIndex; }

std::shared_ptr<QAction> View::getPageAction(PageIndex pageIndex) {
    if (!_actions.contains(pageIndex)) {
        throw std::runtime_error("Cannot find this page!");
    }

    return _actions[pageIndex];
}
