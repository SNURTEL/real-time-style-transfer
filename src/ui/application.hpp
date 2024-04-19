#ifndef STYLE_APPLICATION_UI_APPLICATION_HPP
#define STYLE_APPLICATION_UI_APPLICATION_HPP


#include <QApplication>

class ModelManager;

class MainWindow;

class StyleApplication : public QApplication {
public:
    StyleApplication(int argc, char *argv[], const std::shared_ptr<ModelManager>& manager);

private:
    std::shared_ptr<ModelManager> modelManager;
    std::shared_ptr<MainWindow> mainWindow;
};


#endif //STYLE_APPLICATION_UI_APPLICATION_HPP
