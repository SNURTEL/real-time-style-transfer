#include "ui/pages/page.hpp"
#include "ui/state.hpp"

Page::Page(QWidget *parent, std::shared_ptr<State> state) : QWidget(parent) {
    _state = state;
}

void Page::activatePage() { _active = true; }

void Page::deactivatePage() { _active = false; }

bool Page::isActive() { return _active; }
