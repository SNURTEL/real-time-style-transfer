#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <istream>
#include <opencv2/videoio.hpp>
#include <optional>

/**
 * @brief A thin wrapper around cv2::VideoCapture.
 *
 */
class Camera {
  public:
    /**
     * @brief Create a camera object
     *
     * @param device Device Id (default=0)
     * @param apiPreference Preferred API (default=cv::CAP_ANY)
     * @return std::optional<Camera> A camera object or std::nullopt if camera
     * creation failed
     */
    static std::optional<Camera> build(int device = 0,
                                       int apiPreference = cv::CAP_ANY);

    /**
     * @brief Read a frame from camera
     *
     * @return std::optional<cv::Mat> Frame or std::nullopt if frame grabbing
     * failed
     */
    std::optional<cv::Mat> nextFrame();

  protected:
    explicit Camera(cv::VideoCapture videoCapture);

    cv::VideoCapture _videoCapture;

  private:
    Camera();
};

#endif // __CAMERA_H__