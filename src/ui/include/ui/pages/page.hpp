#ifndef STYLE_APPLICATION_UI_PAGES_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_PAGE_HPP

#include <QWidget>

/**
 * @brief Base Page class
 */
class Page : public QWidget {
public:
    Page(QWidget *parent) : QWidget(parent) {}

    /**
     * @brief Activates page
     */
    virtual void activatePage();

    /**
     * @brief Deactivates page
     */
    virtual void deactivatePage();

    /**
     * @brief Checking if page is active
     * @return true if page is active, false otherwise
     */
    virtual bool isActive();

private:
    bool _active{false};
};

#endif //STYLE_APPLICATION_UI_PAGES_PAGE_HPP
