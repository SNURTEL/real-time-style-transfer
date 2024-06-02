#include <QAction>
#include <QVBoxLayout>
#include <QToolBar>
#include <QWidget>

#include "ui/main_window.hpp"
#include "ui/view.hpp"
#include "ui/pages/page_index.hpp"


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

    // region Create central widget and layout
    _centralWidget = std::make_shared<QWidget>(this);
    _centralWidget->setObjectName(QString::fromUtf8("CentralWidget"));

    _centralLayout = std::make_shared<QVBoxLayout>(_centralWidget.get());
    _centralLayout->setObjectName(QString::fromUtf8("CentralLayout"));
    // endregion

    // region Add actions to toolbar
    _toolBar->addAction(_imageInferenceAction.get());
    _toolBar->addAction(_cameraInferenceAction.get());
    _toolBar->addAction(_modelsAction.get());
    // endregion

    // region Add view to central layout
    _view = std::make_shared<View>(this);
    _centralLayout->addWidget(_view.get());
    // endregion

    // region Connect actions to slots
    connect(_imageInferenceAction.get(), &QAction::triggered, this, [this](bool checked = false) {
        this->switchPage(PageIndex::ImageInference, checked);
    });
    connect(_cameraInferenceAction.get(), &QAction::triggered, this, [this](bool checked = false) {
        this->switchPage(PageIndex::CameraInference, checked);
    });
    connect(_modelsAction.get(), &QAction::triggered, this, [this](bool checked = false) {
        this->switchPage(PageIndex::Models, checked);
    });
    // endregion

    this->setCentralWidget(_centralWidget.get());
}

void MainWindow::switchPage(PageIndex page, bool checked) {
    if (!checked) {
        return;
    }

    // @TODO: Add mutually exclusive to all actions - only one should be checked

    _view->switchPage(page);
}
