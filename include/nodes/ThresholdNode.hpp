#pragma once
#include <glad/glad.h>          // ✅ Fix: for GLuint
#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>

enum class ThresholdMode { Binary = 0, Adaptive = 1, Otsu = 2 };

class ThresholdNode : public Node {
public:
    ThresholdNode(int nodeId, const std::string& name);

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;
    void setInput(const cv::Mat& input);

    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

private:
    cv::Mat inputImage, binaryImage;
    int thresholdValue = 128;
    ThresholdMode mode = ThresholdMode::Binary;
};
