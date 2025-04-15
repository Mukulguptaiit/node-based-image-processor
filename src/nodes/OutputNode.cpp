#include <glad/glad.h>
#include "nodes/OutputNode.hpp"
#include "imnodes.h"
#include "imgui.h"
#include <iostream>

OutputNode::OutputNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void OutputNode::setInput(const cv::Mat& input) {
    if (!input.empty()) {
        imageRGB = input.clone();  // assume already RGB
        cv::cvtColor(imageRGB, imageBGR, cv::COLOR_RGB2BGR);  // for saving
        updateTexture();
    }
}

void OutputNode::updateTexture() {
    if (imageRGB.empty()) return;

    if (textureID != 0)
        glDeleteTextures(1, &textureID);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imageRGB.cols, imageRGB.rows, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, imageRGB.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OutputNode::process() {
    // no-op
}

void OutputNode::drawUI() {
    ImNodes::BeginNode(id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(name.c_str());
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id + 1);
    ImGui::Text("Image In");
    ImNodes::EndInputAttribute();

    if (!imageRGB.empty()) {
        float aspect = imageRGB.cols / (float)imageRGB.rows;
        float previewWidth = 150.0f;

        ImGui::Image((ImTextureID)(intptr_t)textureID,
                     ImVec2(previewWidth, previewWidth / aspect));

        ImGui::Text("Output Format:");
        ImGui::RadioButton("JPG", format == "JPG"); if (ImGui::IsItemClicked()) format = "JPG";
        ImGui::SameLine();
        ImGui::RadioButton("PNG", format == "PNG"); if (ImGui::IsItemClicked()) format = "PNG";

        if (format == "JPG") {
            ImGui::SliderInt("Quality", &quality, 10, 100);
        }

        if (ImGui::Button("💾 Save Image")) {
            saveImage();
        }
    }

    ImNodes::EndNode();
}

void OutputNode::saveImage() {
    std::vector<int> params;
    std::string filename;

    if (format == "JPG") {
        filename = "output.jpg";
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(quality);
    } else {
        filename = "output.png";
    }

    bool ok = cv::imwrite(filename, imageBGR, params);
    if (ok) {
        std::cout << "✅ Image saved to " << filename << std::endl;
    } else {
        std::cerr << "❌ Failed to save image!\n";
    }
}

cv::Mat OutputNode::getOutput() {
    return imageRGB;  // optionally return output for chaining
}