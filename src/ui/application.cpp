#include <memory>

#include "ui/application.hpp"
#include "ui/main_window.hpp"

StyleApplication::StyleApplication(int argc, char **argv) : QApplication(argc, argv) {
    mainWindow = std::make_shared<MainWindow>();
    mainWindow->show();
}



// #include <memory>
// // cppcheck-suppress missingInclude
// #include "common/manager.hpp"
// #include "ui/application.hpp"
// #include "ui/main_window.hpp"

// StyleApplication::StyleApplication(int argc, char **argv,
//                                    const std::shared_ptr<ModelManager>
//                                    &manager)
//     : QApplication(argc, argv) {
//     modelManager = manager;
//     mainWindow = std::make_shared<MainWindow>();
//     mainWindow->setModelManager(manager);
//     mainWindow->show();
// }

