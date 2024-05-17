#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "common/image.hpp"

std::optional<cv::Mat> image::loadImage(const std::string &filename,
                                        cv::ImreadModes mode) {
    std::string path = cv::samples::findFile(filename);
    cv::Mat image = cv::imread(path, mode);

    return image.empty() ? std::nullopt : std::make_optional(image);
}