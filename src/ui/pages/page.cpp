#include "ui/pages/page.hpp"

void Page::activatePage() {
    _active = true;
}

void Page::deactivatePage() {
    _active = false;
}

bool Page::isActive() {
    return _active;
}