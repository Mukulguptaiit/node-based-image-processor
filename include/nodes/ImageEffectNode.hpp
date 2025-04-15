#pragma once

#include <glad/glad.h>
#include "core/Node.hpp"
#include <opencv2/opencv.hpp>
#include <string>

class ImageEffectNode : public Node {
public:
    ImageEffectNode(int nodeId, const std::string& name);

    void process() override;
    void drawUI() override;
    cv::Mat getOutput() override;
    void setInput(const cv::Mat& input);

    int getInputAttrId() const { return id + 1; }
    int getOutputAttrId() const { return id + 2; }

private:
    enum EffectType {
        EFFECT_BRIGHTNESS = 0,
        EFFECT_BLUR,
        EFFECT_GRAYSCALE,
        EFFECT_INVERT
    };

    int currentEffect = 0; // dropdown index
    const char* effectNames[4] = { "Brightness", "Blur", "Grayscale", "Invert" };

    cv::Mat inputImage, outputImage;
    GLuint textureID = 0;

    // Effect parameters
    int brightness = 0;      // -100 to 100
    int blurRadius = 5;      // 1–20
    bool directional = false;
    bool vertical = false;

    void updateTexture();
};
