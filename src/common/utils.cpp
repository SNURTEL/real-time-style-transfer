#include <c10/core/ScalarType.h>
#include <cstring>

#include <ATen/core/TensorBody.h>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <torch/script.h>

#include "common/utils.hpp"

at::Tensor cv2ToTensor(const cv::Mat &image, bool copy) {
    at::Tensor temp =
        torch::from_blob(image.data, {image.rows, image.cols, image.channels()},
                         torch::kByte)
            .permute({2, 0, 1})
            .unsqueeze(0);
    return copy ? temp.clone() : temp;
}

cv::Mat tensorToCv2(const at::Tensor &tensor, bool copy) {

    auto permuted = tensor.squeeze(0).permute({1, 2, 0});
    auto sizes = permuted.sizes();
    auto reshaped = permuted.reshape({sizes[0] * sizes[1] * 3});

    cv::Mat temp = cv::Mat{
        cv::Size{static_cast<int>(sizes[0]), static_cast<int>(sizes[1])},
        CV_8UC3, reshaped.data_ptr<uchar>()};
    return copy ? temp.clone() : temp;
}

cv::Mat transfer(const cv::Mat &image, std::shared_ptr<Model> model, float downscaleFactor) {
    cv::Mat paddedFrame;
    int longerEdge = std::max(image.size[0], image.size[1]);
    int vPadding = std::max(0, (longerEdge - image.size[0]) / 2);
    int hPadding = std::max(0, (longerEdge - image.size[1]) / 2);
    cv::copyMakeBorder(image, paddedFrame, vPadding, vPadding, hPadding, hPadding, cv::BORDER_ISOLATED);

    cv::Mat downscaled;
    cv::resize(paddedFrame, downscaled, cv::Size(paddedFrame.size[1] / downscaleFactor, paddedFrame.size[0] / downscaleFactor), 0, 0,
                cv::INTER_LINEAR);
    at::Tensor frameTensor = cv2ToTensor(downscaled, true).cuda();

    at::Tensor pred = ((model->forward(frameTensor) + 1) * 127.5)
                            .detach()
                            .clamp(0, 255)
                            .to(torch::kU8)
                            .to(torch::kCPU);
    cv::Mat predCv = tensorToCv2(pred, true);
    cv::Mat upscaled;
    cv::resize(predCv, upscaled, cv::Size(paddedFrame.size[1], paddedFrame.size[0]), 0, 0,
                cv::INTER_LINEAR);
    cv::Mat cropped = upscaled(cv::Rect(hPadding, vPadding, image.size[1], image.size[0]));
    return cropped.clone();

}

bool isCameraAvailable() {
    auto cap = cv::VideoCapture(0);
    return cap.isOpened();
}