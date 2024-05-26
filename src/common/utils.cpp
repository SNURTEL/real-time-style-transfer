#include <c10/core/ScalarType.h>
#include <cstring>

#include <ATen/core/TensorBody.h>
#include <opencv2/core.hpp>
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
