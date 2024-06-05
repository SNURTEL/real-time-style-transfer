#include "common/utils.hpp"
#include <ATen/core/TensorBody.h>
#include <complex>
#include <iostream>
#include <torch/torch.h>
#include <torch/types.h>
#undef CHECK  /* Torch provides a CHECK macro, which conflicts with Catch2 */
#include <catch2/catch_test_macros.hpp>
#include <opencv2/core/mat.hpp>

TEST_CASE("Test tensor to cv2 conversion") {
    at::IntArrayRef in_size = {1, 3, 2, 2};
    at::Tensor in = at::zeros(in_size, {torch::kU8});
    cv::Mat out = tensorToCv2(in);
    cv::Size required_size = cv::Size(2, 2);
    REQUIRE(out.size() == required_size);
    REQUIRE(out.channels() == 3);
}

TEST_CASE("Test tensor to cv2 conversion copy") {
    at::IntArrayRef in_size = {1, 3, 2, 2};
    at::Tensor in = at::zeros(in_size, {torch::kU8});
    cv::Mat out = tensorToCv2(in, true);
    REQUIRE(static_cast<unsigned long>(
                std::abs(out.data - static_cast<uchar *>(in.data_ptr()))) >=
            in.numel() *
                torch::elementSize(torch::typeMetaToScalarType(in.dtype())));
    REQUIRE(static_cast<unsigned long>(
                std::abs(out.data - static_cast<uchar *>(in.data_ptr()))) >=
            out.total() * out.elemSize());
}

TEST_CASE("Test cv2 to tensor conversion") {
    cv::Mat in = cv::Mat::ones(2, 2, CV_8UC3);
    at::Tensor out = cv2ToTensor(in);
    at::IntArrayRef required_size = {1, 3, 2, 2};
    REQUIRE(out.sizes() == required_size);
}

TEST_CASE("Test cv2 to tensor conversion copy") {
    cv::Mat in = cv::Mat::ones(2, 2, CV_8UC3);
    at::Tensor out = cv2ToTensor(in, true);
    REQUIRE(static_cast<unsigned long>(
                std::abs(in.data - static_cast<uchar *>(out.data_ptr()))) >=
            out.numel() *
                torch::elementSize(torch::typeMetaToScalarType(out.dtype())));
    REQUIRE(static_cast<unsigned long>(
                std::abs(in.data - static_cast<uchar *>(out.data_ptr()))) >=
            in.total() * in.elemSize());
}