#include <glad/glad.h>
#include "nodes/BlurNode.hpp"
#include "imnodes.h"
#include "imgui.h"

BlurNode::BlurNode(int nodeId, const std::string& name) {
    this->id = nodeId;
    this->name = name;
}

void BlurNode::setInput(const cv::Mat& input) {
    inputImage = input.clone();
}

void BlurNode::process() {
    if (!inputImage.empty() && kernelSize > 0) {
        int k = kernelSize * 2 + 1; // odd
        cv::GaussianBlur(inputImage, blurredImage, cv::Size(k, k), 0);
    }
}

void BlurNode::drawUI() {
    ImNodes::BeginNode(id);
    ImNodes::BeginNodeTitleBar(); ImGui::TextUnformatted(name.c_str()); ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(getInputAttrId());
    ImGui::Text("Input Image");
    ImNodes::EndInputAttribute();

    ImGui::SliderInt("Radius", &kernelSize, 1, 20);

    ImNodes::BeginOutputAttribute(getOutputAttrId());
    ImGui::Text("Blurred Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

cv::Mat BlurNode::getOutput() {
    return blurredImage;
}