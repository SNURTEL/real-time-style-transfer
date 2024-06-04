#include <iostream>

#include "ui/pages/camera_page.hpp"
#include "ui/state.hpp"

CameraPage::CameraPage(QWidget *parent, std::shared_ptr<State> state) : Page(parent, state) {
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
