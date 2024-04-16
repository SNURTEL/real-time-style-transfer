#include <torch/script.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <memory>


int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: example-app <path-to-exported-script-module>\n";
        return -1;
    }


    torch::jit::script::Module module;
    try {
        module = torch::jit::load(argv[1]);
    }
    catch (const c10::Error& e) {
        std::cerr << "error loading the model\n";
        return -1;
    }

    std::cout << "Model loaded.\n";

    std::string image_path = cv::samples::findFile("../51.png");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    cv::imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window

    if(k == 's')
    {
        cv::imwrite("starry_night.png", img);
    }
}
