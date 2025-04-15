#pragma once

#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>

class OutputNode : public Node {
public:
    OutputNode(int nodeId, const std::string& name);

    void setInput(const cv::Mat& input);  // 👈 from connected node

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;
    int getInputAttrId() const { return id + 1; }

private:
    cv::Mat image;  
    cv::Mat imageRGB;  // RGB version for OpenGL
    cv::Mat imageBGR;  // BGR version for saving to file
    GLuint textureID = 0;

    std::string format = "JPG";
    int quality = 90;

    void updateTexture();
    void saveImage();
};