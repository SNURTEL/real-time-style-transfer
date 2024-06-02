#ifndef STYLE_APPLICATION_UI_PAGES_PAGE_HPP
#define STYLE_APPLICATION_UI_PAGES_PAGE_HPP

class Page : public QWidget {
public:
    Page(QWidget *parent) : QWidget(parent) {}

    virtual void activatePage() = 0;

    virtual void deactivatePage() = 0;
};

#endif //STYLE_APPLICATION_UI_PAGES_PAGE_HPP
