#include <memory>

#include "ui/application.hpp"
#include "ui/main_window.hpp"

StyleApplication::StyleApplication(int argc, char **argv) : QApplication(argc, argv) {
    mainWindow = std::make_shared<MainWindow>();
    mainWindow->show();
}