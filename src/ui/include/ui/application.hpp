#ifndef STYLE_APPLICATION_UI_APPLICATION_HPP
#define STYLE_APPLICATION_UI_APPLICATION_HPP

#include <QApplication>

class MainWindow;


/**
 * @brief Main Qt application class
 */
class StyleApplication : public QApplication {
public:
    StyleApplication(int argc, char **argv);

private:
    /**
     * @brief Main Window
     */
    std::shared_ptr<MainWindow> mainWindow;
};


#endif // STYLE_APPLICATION_UI_APPLICATION_HPP