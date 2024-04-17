#include <torch/script.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <memory>
#include <vector>


torch::Tensor to_tensor(cv::Mat img) {
    return torch::from_blob(img.data, { img.rows, img.cols, img.channels() }, torch::kByte).unsqueeze(0);
}


int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cerr << "usage: example-app <path-to-exported-script-module> <image file>\n";
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

    std::string image_path = cv::samples::findFile(argv[2]);
    cv::Mat img = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    at::Tensor img_tensor = to_tensor(img).to(torch::kFloat32);
        
    std::vector<torch::jit::IValue> input;
    input.push_back(img_tensor);

    auto output = module.forward(input); 
    int out_class = torch::argmax(output.toTensor()).item<int>();

    std::map<int, std::string> class_to_name{
        {0, "T-shirt/top"},
        {1, "Trouser"},
        {2, "Pullover"},
        {3, "Dress"},
        {4, "Coat"},
        {5, "Sandal"},
        {6, "Shirt"},
        {7, "Sneaker"},
        {8, "Bag"},
        {9, "Ankle boot"}
    };

    std::cout << "Predicted class: " << out_class << std::endl;
    std::cout << "Class name:: " << class_to_name[out_class] << std::endl;
    std::cout << "Raw output: " << output << std::endl;

    cv::imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window

    if(k == 's')
    {
        cv::imwrite("saved_image.png", img);
    }
}
