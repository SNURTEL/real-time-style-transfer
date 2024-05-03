#include <torch/script.h>
#include <opencv2/core.hpp>
#include "common/utils.hpp"

at::Tensor cv2ToTensor(const cv::Mat &image)
{
    return torch::from_blob(image.data,
                            {image.rows, image.cols, image.channels()},
                            torch::kByte)
        .unsqueeze(0);
}

cv::Mat tensorToCv2(const at::Tensor &tensor)
{
    auto sizes = tensor.sizes();
    return cv::Mat{static_cast<int>(sizes[0]), static_cast<int>(sizes[1]), CV_32FC(static_cast<int>(sizes[2])), tensor.data_ptr()};
}
