#ifndef STYLE_APPLICATION_UI_VIEW_HPP
#define STYLE_APPLICATION_UI_VIEW_HPP

#include <QStackedWidget>

class Page;

enum class PageIndex;


class View : public QStackedWidget {
public:
    explicit View(QWidget *parent);

    void setupUi();

    void addPage(PageIndex pageIndex, std::shared_ptr<Page> page, std::shared_ptr<QAction> action);

    void switchPage(PageIndex pageIndex);

    std::shared_ptr<Page> getPage(PageIndex page);

    std::shared_ptr<QAction> getPageAction(PageIndex pageIndex);

    PageIndex getCurrentPageIndex();
private:
    PageIndex _currentPageIndex;
    std::map<PageIndex, std::shared_ptr<Page>> _pages;
    std::map<PageIndex, std::shared_ptr<QAction>> _actions;
};


#endif //STYLE_APPLICATION_UI_VIEW_HPP
