#include <filesystem>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <torch/types.h>

#include "common/camera.hpp"
#include "common/model.hpp"
#include "common/utils.hpp"
#include "ui/application.hpp"

namespace fs = std::filesystem;

int main(int, char *[]) {
    std::cout << "Current path is " << fs::current_path() << '\n';
    const std::string MODEL_FILE = "models/style_vangogh.ts";

    auto _model = Model::fromFile(MODEL_FILE);
    if (!_model) {
        std::cout << "Cannot load model. Check if " << MODEL_FILE << "  exists."
                  << std::endl;
        return -1;
    }

    Model &model = _model.value();

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
        cv::Mat scaledFrame;
        cv::resize(frame.value(), scaledFrame, cv::Size(256, 256), 0, 0,
                   cv::INTER_LINEAR);
        at::Tensor frameTensor = cv2ToTensor(scaledFrame, true).cuda();

        at::Tensor pred = ((model.forward(frameTensor) + 1) * 127.5)
                              .detach()
                              .clamp(0, 255)
                              .to(torch::kU8)
                              .to(torch::kCPU);
        cv::Mat predCv = tensorToCv2(pred, true);
        cv::Mat upscaled;
        cv::resize(predCv, upscaled, cv::Size(1024, 1024), 0, 0,
                   cv::INTER_LINEAR);

        cv::imshow("Live", upscaled.clone());

        if (cv::waitKey(5) >= 0)
            break;
    }
}
