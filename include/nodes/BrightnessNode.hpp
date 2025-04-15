#pragma once

#include <glad/glad.h>          // ✅ Fix: for GLuint
#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>

class BrightnessNode : public Node {
public:
    BrightnessNode(int nodeId, const std::string& name);

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;

    void setInput(const cv::Mat& input);
    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

private:
    cv::Mat inputImage, outputImage;
    int brightness = 0;  // -100 to 100
    GLuint textureID = 0;

    void updateTexture();
};