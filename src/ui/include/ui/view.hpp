#ifndef STYLE_APPLICATION_UI_VIEW_HPP
#define STYLE_APPLICATION_UI_VIEW_HPP

#include <QStackedWidget>

class Page;

enum class PageIndex;


class View : public QStackedWidget {
public:
    explicit View(QWidget *parent);

    void setupUi();

    void switchPage(PageIndex pageIndex);

    std::shared_ptr<Page> getPage(PageIndex page);

    std::shared_ptr<Page> getCurrentPage();

    PageIndex getCurrentPageIndex();
private:
    PageIndex _currentPageIndex;
    std::map<PageIndex, std::shared_ptr<Page>> _pages;
};


#endif //STYLE_APPLICATION_UI_VIEW_HPP
