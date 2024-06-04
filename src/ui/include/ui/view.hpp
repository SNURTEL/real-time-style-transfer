#ifndef STYLE_APPLICATION_UI_VIEW_HPP
#define STYLE_APPLICATION_UI_VIEW_HPP

#include <QStackedWidget>

class Page;

enum class PageIndex;


/**
 * @brief View for displaying pages
 */
class View : public QStackedWidget {
public:
    explicit View(QWidget *parent);

    /**
     * @brief Setups UI for Camera Page
     */
    void setupUi();

    /**
     * @brief Adds page to view
     * @param pageIndex Index of the page
     * @param page Page object
     * @param action Action that is connected to displaying this page
     */
    void addPage(PageIndex pageIndex, std::shared_ptr<Page> page, std::shared_ptr<QAction> action);

    /**
     * @brief Switches page to page with given index
     * @param pageIndex Index of new page
     */
    void switchPage(PageIndex pageIndex);

    /**
     * @brief Get page object by page index
     * @param page Index of the page
     * @return std::shared_ptr<Page> Page object
     */
    std::shared_ptr<Page> getPage(PageIndex page);

    /**
     * @brief Get action connected to page by page index
     * @param pageIndex Index of the page
     * @return std::shared_ptr<QAction> Action of this page
     */
    std::shared_ptr<QAction> getPageAction(PageIndex pageIndex);

    /**
     * @brief Get current page index
     * @return PageIndex Current page index
     */
    PageIndex getCurrentPageIndex();
private:
    PageIndex _currentPageIndex;
    std::map<PageIndex, std::shared_ptr<Page>> _pages;
    std::map<PageIndex, std::shared_ptr<QAction>> _actions;
};


#endif //STYLE_APPLICATION_UI_VIEW_HPP
