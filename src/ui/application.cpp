#include <memory>

#include "../model/manager.hpp"
#include "application.hpp"
#include "main_window.hpp"


StyleApplication::StyleApplication(int argc, char **argv, const std::shared_ptr<ModelManager> &manager) : QApplication(
        argc,
        argv) {
    modelManager = manager;
    mainWindow = std::make_shared<MainWindow>();
    mainWindow->setModelManager(manager);
    mainWindow->show();
}
