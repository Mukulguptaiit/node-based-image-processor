#include <glad/glad.h>
#include "nodes/ThresholdNode.hpp"
#include "imnodes.h"
#include "imgui.h"

ThresholdNode::ThresholdNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void ThresholdNode::setInput(const cv::Mat& input) {
    inputImage = input.clone();
}

void ThresholdNode::process() {
    if (inputImage.empty()) return;

    cv::Mat gray;
    if (inputImage.channels() == 3)
        cv::cvtColor(inputImage, gray, cv::COLOR_RGB2GRAY);
    else
        gray = inputImage;

    switch (mode) {
        case ThresholdMode::Binary:
            cv::threshold(gray, binaryImage, thresholdValue, 255, cv::THRESH_BINARY);
            break;
        case ThresholdMode::Adaptive:
            cv::adaptiveThreshold(gray, binaryImage, 255,
                cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
            break;
        case ThresholdMode::Otsu:
            cv::threshold(gray, binaryImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            break;
    }
}

void ThresholdNode::drawUI() {
    ImNodes::BeginNode(id);
    ImNodes::BeginNodeTitleBar(); ImGui::TextUnformatted(name.c_str()); ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(getInputAttrId());
    ImGui::Text("Grayscale In");
    ImNodes::EndInputAttribute();

    int selected = static_cast<int>(mode);
    ImGui::Text("Mode:");
    ImGui::RadioButton("Binary", &selected, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Adaptive", &selected, 1);
    ImGui::SameLine();
    ImGui::RadioButton("Otsu", &selected, 2);
    mode = static_cast<ThresholdMode>(selected);

    if (mode == ThresholdMode::Binary) {
        ImGui::SliderInt("Threshold", &thresholdValue, 0, 255);
    }

    ImNodes::BeginOutputAttribute(getOutputAttrId());
    ImGui::Text("Binary Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

cv::Mat ThresholdNode::getOutput() {
    return binaryImage;
}