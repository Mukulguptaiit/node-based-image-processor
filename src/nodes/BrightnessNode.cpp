#include "nodes/BrightnessNode.hpp"
#include <glad/glad.h>
#include "imgui.h"
#include "imnodes.h"

BrightnessNode::BrightnessNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void BrightnessNode::setInput(const cv::Mat& input) {
    if (!input.empty()) {
        inputImage = input.clone();
    }
}

void BrightnessNode::process() {
    if (inputImage.empty()) return;

    inputImage.convertTo(outputImage, -1, 1, brightness); // brightness bias

    updateTexture();
}

void BrightnessNode::updateTexture() {
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

void BrightnessNode::drawUI() {
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

    ImGui::SliderInt("Brightness", &brightness, -100, 100);

    if (!outputImage.empty()) {
        float aspect = outputImage.cols / (float)outputImage.rows;
        float previewWidth = 150.0f;
        ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(previewWidth, previewWidth / aspect));
    }

    ImNodes::EndNode();
}

cv::Mat BrightnessNode::getOutput() {
    return outputImage;
}