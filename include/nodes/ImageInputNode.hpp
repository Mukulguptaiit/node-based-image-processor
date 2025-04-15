#pragma once

#include "core/Node.hpp"
#include <glad/glad.h>
#include <opencv2/opencv.hpp>
#include <string>

class ImageInputNode : public Node {
public:
    ImageInputNode(int nodeId, const std::string& name);

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;
    int getOutputAttrId() const { return id + 1; }

private:
    cv::Mat image;
    GLuint textureID = 0;
    std::string path = "assets/sample.jpg";  // 📌 Change later with file picker

    void loadImage(const std::string& filepath);
    void updateTexture(); // convert cv::Mat to OpenGL texture
};