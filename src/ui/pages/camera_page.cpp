#include <iostream>

#include "ui/pages/camera_page.hpp"

CameraPage::CameraPage(QWidget *parent) : Page(parent) {
    setupUi();
}

void CameraPage::setupUi() {

}

void CameraPage::activatePage() {
    Page::activatePage();
    std::cout << "Activate camera";
}

void CameraPage::deactivatePage() {
    Page::deactivatePage();
    std::cout << "Deactivate camera";
}
