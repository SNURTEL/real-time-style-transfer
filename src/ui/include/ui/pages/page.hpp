#ifndef STYLE_APPLICATION_UI_PAGES_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_PAGE_HPP

#include <QWidget>


class Page : public QWidget {
public:
    Page(QWidget *parent) : QWidget(parent) {}

    virtual void activatePage();

    virtual void deactivatePage();

    virtual bool isActive();

private:
    bool _active;
};

#endif //STYLE_APPLICATION_UI_PAGES_PAGE_HPP
