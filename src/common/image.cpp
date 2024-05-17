#include "common/image.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

std::optional<cv::Mat> image::loadImage(const std::string &filename) {
    std::string path = cv::samples::findFile(filename);
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);

    return image.empty() ? std::nullopt : std::make_optional(image);
}