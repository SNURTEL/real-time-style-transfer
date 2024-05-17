#include <istream>
#include <optional>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

#include "common/camera.hpp"

Camera::Camera(cv::VideoCapture videoCapture) : _videoCapture(videoCapture) {}

std::optional<Camera> Camera::build(int device, int apiPreference) {
    auto camera = Camera(cv::VideoCapture(device, apiPreference));

    if (!camera._videoCapture.open(device, apiPreference)) {
        return std::nullopt;
    }

    return camera;
}

std::optional<cv::Mat> Camera::nextFrame() {
    cv::Mat buf;

    return _videoCapture.read(buf) ? std::optional<cv::Mat>{buf} : std::nullopt;
}
