#ifndef STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP
#define STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP

#include <QMainWindow>

class QPushButton;
class QLabel;
class QPixmap;
class ModelManager;

class MainWindow : public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setImage(QPixmap &map);

    void setModelManager(std::shared_ptr<ModelManager> manager);

  private:
    std::string imageFilename;
    std::shared_ptr<ModelManager> modelManager;
    std::shared_ptr<QPushButton> loadButton;
    std::shared_ptr<QPushButton> runButton;
    std::shared_ptr<QLabel> image;
    std::shared_ptr<QLabel> text;

    void onLoadButtonClicked();
    void onRunButtonClicked();
};

#endif // STYLE_APPLICATION_UI_MAIN_APPLICATION_HPP
