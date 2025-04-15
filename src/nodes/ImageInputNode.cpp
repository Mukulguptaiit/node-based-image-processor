#include <glad/glad.h>
#include "nodes/ImageInputNode.hpp"
#include "imnodes.h"
#include "imgui.h"
#include <iostream>

ImageInputNode::ImageInputNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
    loadImage(path);
}

void ImageInputNode::loadImage(const std::string& filepath) {
    image = cv::imread(filepath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filepath << std::endl;
        return;
    }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    updateTexture();
}

void ImageInputNode::updateTexture() {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image.cols, image.rows, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ImageInputNode::process() {
    // nothing to do — image is already loaded
}

void ImageInputNode::drawUI() {
    ImNodes::BeginNode(id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(name.c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(id + 1);
    ImGui::Text("Image Out");
    ImNodes::EndOutputAttribute();

    if (!image.empty()) {
        ImGui::Text("Size: %dx%d", image.cols, image.rows);
        ImGui::Text("Channels: %d", image.channels());

        float aspect = image.cols / (float)image.rows;
        float previewWidth = 150.0f;
        ImGui::Image((ImTextureID)(intptr_t)textureID,
                     ImVec2(previewWidth, previewWidth / aspect));
    }

    ImNodes::EndNode();
}

cv::Mat ImageInputNode::getOutput() {
    return image;
}