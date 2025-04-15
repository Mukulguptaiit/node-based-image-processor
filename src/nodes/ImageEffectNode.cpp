#include "nodes/ImageEffectNode.hpp"
#include <glad/glad.h>
#include "imgui.h"
#include "imnodes.h"
#include <opencv2/imgproc.hpp>

ImageEffectNode::ImageEffectNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void ImageEffectNode::setInput(const cv::Mat& image) {
    inputImage = image.clone();
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

        case EFFECT_BLUR:
            cv::GaussianBlur(temp, outputImage, cv::Size(blurRadius * 2 + 1, blurRadius * 2 + 1), 0);
            break;

        case EFFECT_GRAYSCALE:
            cv::cvtColor(temp, outputImage, cv::COLOR_RGB2GRAY);
            cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2RGB);
            break;

        case EFFECT_INVERT:
            cv::bitwise_not(temp, outputImage);
            break;

        case EFFECT_EDGE:
            if (edgeUseCanny) {
                cv::Mat gray;
                cv::cvtColor(temp, gray, cv::COLOR_RGB2GRAY);
                cv::Canny(gray, gray, cannyThreshold1, cannyThreshold2);
                cv::cvtColor(gray, outputImage, cv::COLOR_GRAY2RGB);
            } else {
                cv::Mat gray, grad_x, grad_y, abs_grad_x, abs_grad_y;
                cv::cvtColor(temp, gray, cv::COLOR_RGB2GRAY);
                cv::Sobel(gray, grad_x, CV_16S, 1, 0, sobelKernelSize);
                cv::Sobel(gray, grad_y, CV_16S, 0, 1, sobelKernelSize);
                cv::convertScaleAbs(grad_x, abs_grad_x);
                cv::convertScaleAbs(grad_y, abs_grad_y);
                cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, gray);
                cv::cvtColor(gray, outputImage, cv::COLOR_GRAY2RGB);
            }
            break;

        case EFFECT_CUSTOM_KERNEL: {
            cv::Mat kernel(3, 3, CV_32F, customKernel);
            cv::filter2D(temp, outputImage, -1, kernel);
            break;
        }
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

    const char* effectNames[] = {
        "Brightness", "Blur", "Grayscale", "Invert", "Edge Detect", "Custom Kernel"
    };

    ImGui::Combo("Effect", &currentEffect, effectNames, IM_ARRAYSIZE(effectNames));

    switch (currentEffect) {
        case EFFECT_BRIGHTNESS:
            ImGui::SliderInt("Brightness", &brightness, -100, 100);
            break;

        case EFFECT_BLUR:
            ImGui::SliderInt("Radius", &blurRadius, 1, 20);
            break;

        case EFFECT_EDGE:
            ImGui::Checkbox("Use Canny", &edgeUseCanny);
            if (edgeUseCanny) {
                ImGui::SliderInt("Threshold 1", &cannyThreshold1, 0, 255);
                ImGui::SliderInt("Threshold 2", &cannyThreshold2, 0, 255);
            } else {
                ImGui::SliderInt("Sobel Kernel", &sobelKernelSize, 1, 7);
                if (sobelKernelSize % 2 == 0) sobelKernelSize += 1;
            }
            break;

        case EFFECT_CUSTOM_KERNEL:
            ImGui::Text("Custom 3x3 Kernel:");
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    ImGui::PushID(i * 3 + j);
                    ImGui::InputFloat("##kernel", &customKernel[i][j], 0.1f, 1.0f, "%.2f");
                    ImGui::PopID();
                    if (j < 2) ImGui::SameLine();
                }
            }
            break;
    }

    if (!outputImage.empty()) {
        float aspect = outputImage.cols / (float)outputImage.rows;
        float previewWidth = 150.0f;
        ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(previewWidth, previewWidth / aspect));
    }

    ImNodes::EndNode();
}
