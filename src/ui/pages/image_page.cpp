#include <iostream>

#include <QPushButton>

#include "ui/pages/image_page.hpp"
#include "ui/state.hpp"

ImagePage::ImagePage(QWidget *parent, std::shared_ptr<State> state) : Page(parent, state) {
    setupUi();
}

void ImagePage::setupUi() {
    btn = new QPushButton(this);
    btn->setText(QString::fromUtf8("Push me"));
}

void ImagePage::activatePage() {
    Page::activatePage();
    std::cout << "Activate image";
}

void ImagePage::deactivatePage() {
    Page::deactivatePage();
    std::cout << "Deactivate image";
}


