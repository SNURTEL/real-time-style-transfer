#ifndef STYLE_APPLICATION_UI_VIEW_HPP
#define STYLE_APPLICATION_UI_VIEW_HPP

#include <QStackedWidget>

class ImagePage;

class CameraPage;

class ModelsPage;


class View : public QStackedWidget {
public:
    View(QWidget *parent);

    void setupUi();

private:
    std::shared_ptr<ImagePage> _imagePage;
    std::shared_ptr<CameraPage> _cameraPage;
    std::shared_ptr<ModelsPage> _modelsPage;
};


#endif //STYLE_APPLICATION_UI_VIEW_HPP
