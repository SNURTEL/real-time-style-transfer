#include "model/manager.hpp"
#include "ui/application.hpp"

int main(int argc, char *argv[]) {
    std::shared_ptr<ModelManager> manager = std::make_shared<ModelManager>();
    if (!manager->loadModel("dummy_model.pt")) {
        std::cout << "Cannot load model. Check if dummy_model.pt exists in "
                     "same directory as application";
        return -1;
    }

    StyleApplication app(argc, argv, manager);
    return StyleApplication::exec();
}