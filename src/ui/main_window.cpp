#include <QAction>
#include <QVBoxLayout>
#include <QToolBar>
#include <QWidget>

#include "ui/main_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    setWindowTitle("Style Transfer Application");
    resize(800, 600);

    // region Create Actions
    QIcon imageIcon;
    QIcon cameraIcon;
    QIcon modelsIcon;
    imageIcon.addFile(QString::fromUtf8("resources/image.png"), QSize(), QIcon::Normal, QIcon::Off);
    cameraIcon.addFile(QString::fromUtf8("resources/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
    modelsIcon.addFile(QString::fromUtf8("resources/models.png"), QSize(), QIcon::Normal, QIcon::Off);

    _imageInferenceAction = std::make_shared<QAction>(this);
    _imageInferenceAction->setObjectName(QString::fromUtf8("ImageInferenceAction"));
    _imageInferenceAction->setCheckable(true);
    _imageInferenceAction->setChecked(false);
    _imageInferenceAction->setEnabled(true);
    _imageInferenceAction->setIcon(imageIcon);
    _imageInferenceAction->setText("Image Inference");
    _imageInferenceAction->setToolTip("Switch to image inference");

    _cameraInferenceAction = std::make_shared<QAction>(this);
    _cameraInferenceAction->setObjectName(QString::fromUtf8("CameraInferenceAction"));
    _cameraInferenceAction->setCheckable(true);
    _cameraInferenceAction->setChecked(false);
    _cameraInferenceAction->setEnabled(true);
    _cameraInferenceAction->setIcon(cameraIcon);
    _cameraInferenceAction->setText("Camera Inference");
    _cameraInferenceAction->setToolTip("Switch to camera inference");

    _modelsAction = std::make_shared<QAction>(this);
    _modelsAction->setObjectName(QString::fromUtf8("ModelsAction"));
    _modelsAction->setCheckable(true);
    _modelsAction->setChecked(false);
    _modelsAction->setEnabled(true);
    _modelsAction->setIcon(modelsIcon);
    _modelsAction->setText("Models repository");
    _modelsAction->setToolTip("Display available models");
    // endregion

    // region Create Toolbar
    _toolBar = std::make_shared<QToolBar>(this);
    _toolBar->setObjectName(QString::fromUtf8("ToolBar"));
    _toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addToolBar(Qt::TopToolBarArea, _toolBar.get());
    this->insertToolBarBreak(_toolBar.get());
    // endregion

    // region Main Widget and Layout
    centralWidget = std::make_shared<QWidget>(this);
    centralWidget->setObjectName(QString::fromUtf8("CentralWidget"));

    centralLayout = std::make_shared<QVBoxLayout>(centralWidget.get());
    centralLayout->setObjectName(QString::fromUtf8("CentralLayout"));
    // endregion

    // region Add actions to toolbar
    _toolBar->addAction(_imageInferenceAction.get());
    _toolBar->addAction(_cameraInferenceAction.get());
    _toolBar->addAction(_modelsAction.get());
    // endregion

    // @TODO: Add elements to centralLayout

    this->setCentralWidget(centralWidget.get());
}