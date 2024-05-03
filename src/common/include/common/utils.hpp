#include <torch/script.h>
#include <opencv2/core.hpp>

at::Tensor cv2ToTensor(const cv::Mat &image);

cv::Mat tensorToCv2(const at::Tensor &tensor);



