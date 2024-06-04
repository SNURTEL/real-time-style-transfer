#include <iostream>
#include <memory>
#include <utility>

#include <QListWidget>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>

#include "common/model_manager.hpp"
#include "ui/pages/models_page.hpp"
#include "ui/components/model_list_element.hpp"

ModelsPage::ModelsPage(QWidget *parent) : Page(parent) {
    setupUi();
}

void ModelsPage::setupUi() {
    _layout = std::make_shared<QVBoxLayout>(this);

    _title = std::make_shared<QLabel>(this);
    _title->setText(QString::fromUtf8("Available Models"));
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setPointSize(16);
    _title->setFont(font);
    _title->setAlignment(Qt::AlignCenter);
    _layout->addWidget(_title.get());

    _listWidget = std::make_shared<QListWidget>(this);
    _listWidget->setStyleSheet("QListWidget { background: transparent; } "
                               "QListWidget::item { background: rgba(255, 255, 255, 0.1); } "
                               "QListWidget::item:selected{ background: rgba(255, 255, 255, 0.1); }");
    _listWidget->setSpacing(8);

    for (const modelManager::PretrainedModel& model : modelManager::getAllModels()) {
        auto *item = new QListWidgetItem(_listWidget.get());
        auto *widget = new ModelListElement(_listWidget.get(), model);
        item->setSizeHint(widget->sizeHint());
        _listWidget->setItemWidget(item, widget);
    }

    _layout->addWidget(_listWidget.get());
}

void ModelsPage::activatePage() {
    Page::activatePage();
    std::cout << "Activate models";
}

void ModelsPage::deactivatePage() {
    Page::deactivatePage();
    std::cout << "Deactivate models";
}
