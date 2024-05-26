#include <opencv2/core.hpp>
#include <torch/script.h>

/**
 * @brief Convert a cv2 image of shape [x, y, channels] to a Torch tensor of
 * shape [1, channels, x, y] and type torch::kByte.
 *
 * @param image Original cv2 image
 * @param copy Whether to copy the underlying buffer  (default=true)
 * @return at::Tensor Image converted to tensor
 */
at::Tensor cv2ToTensor(const cv::Mat &image, bool copy = false);

/**
 * @brief Convert a Torch tensor of shape [1, channels, x, y] and type
 * torch::kU8 to a cv2 image.
 *
 * @param tensor Original tensor
 * @param copy Whether to copy the underlying buffer (default=true)
 * @return cv::Mat Tensor converted to image
 */
cv::Mat tensorToCv2(const at::Tensor &tensor, bool copy = false);
