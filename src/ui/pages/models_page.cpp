#include <iostream>

#include "ui/pages/models_page.hpp"

ModelsPage::ModelsPage(QWidget *parent) : Page(parent) {
    setupUi();
}

void ModelsPage::setupUi() {

}

void ModelsPage::activatePage() {
    Page::activatePage();
    std::cout << "Activate models";
}

void ModelsPage::deactivatePage() {
    Page::deactivatePage();
    std::cout << "Deactivate models";
}
