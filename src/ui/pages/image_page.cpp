#include <QPushButton>

#include "ui/pages/image_page.hpp"

ImagePage::ImagePage(QWidget *parent) : Page(parent) {
    setupUi();
}

void ImagePage::setupUi() {
    btn = new QPushButton(this);
    btn->setText(QString::fromUtf8("Push me"));
}

void ImagePage::activatePage() {
    Page::activatePage();
}

void ImagePage::deactivatePage() {
    Page::deactivatePage();
}


