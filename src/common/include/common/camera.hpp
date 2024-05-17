#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <istream>
#include <opencv2/videoio.hpp>
#include <optional>

class Camera {
  public:
    static std::optional<Camera> build(int device = 0,
                                       int apiPreference = cv::CAP_ANY);

    std::optional<cv::Mat> nextFrame();

  protected:
    explicit Camera(cv::VideoCapture videoCapture);

    cv::VideoCapture _videoCapture;

  private:
    Camera();
};

#endif // __CAMERA_H__