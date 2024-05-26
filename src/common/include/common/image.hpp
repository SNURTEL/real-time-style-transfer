#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <torch/script.h>

namespace image {
/**
 * @brief Convenience function to load an image from file into cv2::Mat
 *
 * @param filename File path
 * @param mode Imead mode (deafult=cv::IMREAD_GRAYSCALE)
 * @return std::optional<cv::Mat> Image or std::nullopt if reading failed
 */
std::optional<cv::Mat> loadImage(const std::string &filename,
                                 cv::ImreadModes mode = cv::IMREAD_GRAYSCALE);
} // namespace image
#endif // __IMAGE_H__