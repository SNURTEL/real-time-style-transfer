#include <iostream>
#include <ostream>

#include "common/utils.hpp"
#include "ui/application.hpp"

int main(int argc, char **argv) {
    if (!isCameraAvailable()) {
        std::cout << "No cameras available!" << std::endl;
        return -1;
    }

    StyleApplication app(argc, argv);
    return StyleApplication::exec();
}
