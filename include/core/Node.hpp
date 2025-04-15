#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Node {
public:
    int id;
    std::string name;

    // ✅ These must be virtual for `override` to work
    virtual void process() = 0;
    virtual void drawUI() = 0;
    virtual cv::Mat getOutput() = 0;

    virtual ~Node() = default;
};