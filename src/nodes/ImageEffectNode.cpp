#include "nodes/ImageEffectNode.hpp"
#include <glad/glad.h>
#include "imgui.h"
#include "imnodes.h"
#include <opencv2/imgproc.hpp>

ImageEffectNode::ImageEffectNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void ImageEffectNode::setInput(const cv::Mat& input) {
    if (!input.empty())
        inputImage = input.clone();
}

cv::Mat ImageEffectNode::getOutput() {
    return outputImage;
}

void ImageEffectNode::process() {
    if (inputImage.empty()) return;

    cv::Mat temp = inputImage.clone();

    switch (currentEffect) {
        case EFFECT_BRIGHTNESS:
            temp.convertTo(outputImage, -1, 1, brightness);
            break;

        case EFFECT_BLUR: {
            int ksize = blurRadius * 2 + 1;
            if (directional)
                cv::GaussianBlur(temp, outputImage, vertical ? cv::Size(1, ksize) : cv::Size(ksize, 1), 0);
            else
                cv::GaussianBlur(temp, outputImage, cv::Size(ksize, ksize), 0);
            break;
        }

        case EFFECT_GRAYSCALE:
            cv::cvtColor(temp, outputImage, cv::COLOR_RGB2GRAY);
            cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2RGB);
            break;

        case EFFECT_INVERT:
            outputImage = cv::Scalar::all(255) - temp;
            break;
    }

    updateTexture();
}

void ImageEffectNode::updateTexture() {
    if (outputImage.empty()) return;

    if (textureID != 0)
        glDeleteTextures(1, &textureID);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 outputImage.cols, outputImage.rows, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, outputImage.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ImageEffectNode::drawUI() {
    ImNodes::BeginNode(id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(name.c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(getInputAttrId());
    ImGui::Text("Image In");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(getOutputAttrId());
    ImGui::Text("Image Out");
    ImNodes::EndOutputAttribute();

    ImGui::Combo("Effect", &currentEffect, effectNames, IM_ARRAYSIZE(effectNames));

    if (currentEffect == EFFECT_BRIGHTNESS) {
        ImGui::SliderInt("Brightness", &brightness, -100, 100);
    } else if (currentEffect == EFFECT_BLUR) {
        ImGui::SliderInt("Radius", &blurRadius, 1, 20);
        ImGui::Checkbox("Directional", &directional);
        if (directional) ImGui::Checkbox("Vertical", &vertical);
    }

    if (!outputImage.empty()) {
        float aspect = outputImage.cols / (float)outputImage.rows;
        float previewWidth = 150.0f;
        ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(previewWidth, previewWidth / aspect));
    }

    ImNodes::EndNode();
}
