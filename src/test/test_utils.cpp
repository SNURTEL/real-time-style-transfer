#include <ATen/core/TensorBody.h>
#include <catch2/catch_test_macros.hpp>
#include "common/utils.hpp"
#include <opencv2/core/mat.hpp>
#include <torch/torch.h>
#include <iostream>
#include <torch/types.h>

TEST_CASE("Test cv2::Mat to at::Tensor conversion") { 
    at::IntArrayRef in_size = { 1, 3, 2, 2 };
    at::Tensor in = at::zeros(in_size, {torch::kU8});  
    cv::Mat out = tensorToCv2(in);
    cv::Size required_size = cv::Size(2, 2);
    REQUIRE(out.size() == required_size);
    REQUIRE(out.channels() == 3);
}