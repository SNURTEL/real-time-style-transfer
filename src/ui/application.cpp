#include <memory>

#include "ui/application.hpp"
#include "ui/main_window.hpp"
#include "ui/state.hpp"

StyleApplication::StyleApplication(int argc, char **argv) : QApplication(argc, argv) {
    _state = std::make_shared<State>();
    _mainWindow = std::make_shared<MainWindow>(nullptr, _state);
    _mainWindow->show();
}