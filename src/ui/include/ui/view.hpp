#ifndef STYLE_APPLICATION_UI_VIEW_HPP
#define STYLE_APPLICATION_UI_VIEW_HPP

#include <QStackedWidget>

class ImagePage;

class CameraPage;

class ModelsPage;

enum class EPage;

class Page;


class View : public QStackedWidget {
public:
    explicit View(QWidget *parent);

    void setupUi();

    void switchPage(EPage page);
private:
    std::shared_ptr<Page> getPage(EPage page);
private:
    std::shared_ptr<Page> _activePage;
    std::map<EPage, std::shared_ptr<Page>> _pages;
};


#endif //STYLE_APPLICATION_UI_VIEW_HPP
