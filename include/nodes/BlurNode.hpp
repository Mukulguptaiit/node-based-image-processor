#pragma once
#include <glad/glad.h>          // ✅ Fix: for GLuint
#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>
class BlurNode : public Node {
public:
    BlurNode(int nodeId, const std::string& name);

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;
    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

    void setInput(const cv::Mat& input);

private:
    cv::Mat inputImage, blurredImage;
    int kernelSize = 5;
};