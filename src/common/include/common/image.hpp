#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <opencv2/core.hpp>
#include <torch/script.h>

namespace image {
std::optional<cv::Mat> loadImage(const std::string &filename);
}
#endif // __IMAGE_H__