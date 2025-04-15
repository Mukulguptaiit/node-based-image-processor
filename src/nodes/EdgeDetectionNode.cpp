#include <glad/glad.h>
#include "nodes/EdgeDetectionNode.hpp"
#include "imnodes.h"
#include "imgui.h"

EdgeDetectionNode::EdgeDetectionNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void EdgeDetectionNode::setInput(const cv::Mat& input) {
    inputImage = input.clone();
}

void EdgeDetectionNode::process() {
    if (inputImage.empty()) return;

    cv::Mat gray;
    if (inputImage.channels() == 3)
        cv::cvtColor(inputImage, gray, cv::COLOR_RGB2GRAY);
    else
        gray = inputImage;

    if (mode == EdgeMode::Sobel) {
        cv::Mat gradX, gradY;
        cv::Sobel(gray, gradX, CV_16S, 1, 0, sobelKernel);
        cv::Sobel(gray, gradY, CV_16S, 0, 1, sobelKernel);

        cv::Mat absX, absY;
        cv::convertScaleAbs(gradX, absX);
        cv::convertScaleAbs(gradY, absY);

        cv::addWeighted(absX, 0.5, absY, 0.5, 0, edgeImage);
    } else {
        cv::Canny(gray, edgeImage, cannyThreshold1, cannyThreshold2);
    }
}

void EdgeDetectionNode::drawUI() {
    ImNodes::BeginNode(id);
    ImNodes::BeginNodeTitleBar(); ImGui::TextUnformatted(name.c_str()); ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(getInputAttrId());
    ImGui::Text("Input Image");
    ImNodes::EndInputAttribute();

    ImGui::Text("Edge Mode:");
    int selected = static_cast<int>(mode);
    ImGui::RadioButton("Sobel", &selected, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Canny", &selected, 1);
    mode = static_cast<EdgeMode>(selected);

    if (mode == EdgeMode::Sobel) {
        ImGui::SliderInt("Sobel Kernel", &sobelKernel, 3, 7);
        if (sobelKernel % 2 == 0) sobelKernel += 1; // must be odd
    } else {
        ImGui::SliderInt("Threshold 1", &cannyThreshold1, 0, 255);
        ImGui::SliderInt("Threshold 2", &cannyThreshold2, 0, 255);
    }

    ImNodes::BeginOutputAttribute(getOutputAttrId());
    ImGui::Text("Edges Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

cv::Mat EdgeDetectionNode::getOutput() {
    return edgeImage;
}