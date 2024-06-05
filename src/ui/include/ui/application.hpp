/**
 * @brief Main application module
 */
#ifndef STYLE_APPLICATION_UI_APPLICATION_HPP
#define STYLE_APPLICATION_UI_APPLICATION_HPP

#include <QApplication>

class MainWindow;

class State;

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
    std::shared_ptr<MainWindow> _mainWindow;

    /**
     * @brief State of application
     */
    std::shared_ptr<State> _state;
};

#endif // STYLE_APPLICATION_UI_APPLICATION_HPP