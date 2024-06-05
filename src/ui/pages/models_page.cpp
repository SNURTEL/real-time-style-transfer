#include <iostream>
#include <memory>
#include <utility>

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>

#include "common/model_manager.hpp"
#include "ui/components/model_list_element.hpp"
#include "ui/pages/models_page.hpp"
#include "ui/state.hpp"

ModelsPage::ModelsPage(QWidget *parent, std::shared_ptr<State> state)
    : Page(parent, state) {
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
    _listWidget->setStyleSheet(
        "QListWidget { background: transparent; } "
        "QListWidget::item { background: rgba(255, 255, 255, 0.1); } "
        "QListWidget::item:selected{ background: rgba(255, 255, 255, 0.1); }");
    _listWidget->setSpacing(8);

    for (const modelManager::PretrainedModel &model :
         modelManager::getAllModels()) {
        auto *item = new QListWidgetItem(_listWidget.get());
        auto *widget =
            new ModelListElement(_listWidget.get(), model, _state,
                                 std::bind(&ModelsPage::updateChildren, this));
        _buttons.emplace_back(widget);
        item->setSizeHint(widget->sizeHint());
        _listWidget->setItemWidget(item, widget);
    }

    _layout->addWidget(_listWidget.get());
}

void ModelsPage::updateChildren() {
    for (ModelListElement *button : _buttons) {
        button->updateState();
        button->updateUi();
    }
}

void ModelsPage::activatePage() {
    Page::activatePage();

    for (int i = 0; i < _listWidget->count(); ++i) {
        QListWidgetItem *item = _listWidget->item(i);
        auto *widget =
            dynamic_cast<ModelListElement *>(_listWidget->itemWidget(item));
        widget->updateState();
        widget->updateUi();
    }
}

void ModelsPage::deactivatePage() { Page::deactivatePage(); }
