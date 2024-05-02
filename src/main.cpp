#include <iostream>
#include <ostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "common/manager.hpp"
#include "ui/application.hpp"
#include "common/camera.hpp"

int main(int, char *[]) {
// int main(int argc, char *argv[]) {
    // std::shared_ptr<ModelManager> manager = std::make_shared<ModelManager>();
    // if (!manager->loadModel("dummy_model.pt")) {
    //     std::cout << "Cannot load model. Check if dummy_model.pt exists in "
    //                  "same directory as application";
    //     return -1;
    // }

    // StyleApplication app(argc, argv, manager);
    // return app.exec();

    auto cam = Camera::build();

    if (!cam) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return -1;
    }

    for (;;) {
        auto frame = cam->nextFrame();
        if (!frame) {
            std::cerr << "Error getting frame" << std::endl;
            return -2;
        }

        cv::imshow("Live", frame.value());
        if (cv::waitKey(5) >= 0)
        break;
    }
}
