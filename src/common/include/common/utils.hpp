#include <opencv2/core.hpp>
#include <torch/script.h>

/**
 * @brief Convert a cv2 image of shape [x, y, channels] to a Torch tensor of
 * shape [1, channels, x, y] and type torch::kByte.
 *
 * @param image
 * @return at::Tensor
 */
at::Tensor cv2ToTensor(const cv::Mat &image, bool copy=false);

cv::Mat tensorToCv2(const at::Tensor &tensor, bool copy=false);
