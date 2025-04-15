#pragma once
#include <glad/glad.h>
#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>

enum class EdgeMode { Sobel = 0, Canny = 1 };

class EdgeDetectionNode : public Node {
public:
    EdgeDetectionNode(int nodeId, const std::string& name);

    void setInput(const cv::Mat& input);
    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;

    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

private:
    cv::Mat inputImage;
    cv::Mat edgeImage;

    EdgeMode mode = EdgeMode::Sobel;
    int sobelKernel = 3;

    int cannyThreshold1 = 50;
    int cannyThreshold2 = 150;
};