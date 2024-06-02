#ifndef STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP
#define STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP

#include <QMainWindow>

class QAction;

class QVBoxLayout;

class QToolBar;

class QWidget;

class View;


/**
 * @brief Main application window
 */
class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupUi();

private:
    std::shared_ptr<QAction> _imageInferenceAction;
    std::shared_ptr<QAction> _cameraInferenceAction;
    std::shared_ptr<QAction> _modelsAction;

    std::shared_ptr<QWidget> _centralWidget;
    std::shared_ptr<QVBoxLayout> _centralLayout;
    std::shared_ptr<QToolBar> _toolBar;
    std::shared_ptr<View> _view;
};

#endif // STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP