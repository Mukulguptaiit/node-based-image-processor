#pragma once

#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <glad/glad.h>
#include <string>

class ImageEffectNode : public Node {
public:
    ImageEffectNode(int id, const std::string& name);

    void drawUI() override;
    void process() override;
    cv::Mat getOutput() override;
    void setInput(const cv::Mat& image);

    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

private:
    cv::Mat inputImage, outputImage;
    GLuint textureID = 0;

    enum EffectType {
        EFFECT_BRIGHTNESS,
        EFFECT_BLUR,
        EFFECT_GRAYSCALE,
        EFFECT_INVERT,
        EFFECT_EDGE,
        EFFECT_CUSTOM_KERNEL
    };

    int currentEffect = EFFECT_BRIGHTNESS;

    // Parameters
    int brightness = 0;
    int blurRadius = 5;
    bool edgeUseCanny = false;
    int cannyThreshold1 = 100, cannyThreshold2 = 200;
    int sobelKernelSize = 3;

    float customKernel[3][3] = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    void updateTexture();
};
