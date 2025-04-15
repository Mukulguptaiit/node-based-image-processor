// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <vector>
// #include <tuple>

// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include "imnodes.h"

// #include "nodes/ImageInputNode.hpp"
// #include "nodes/OutputNode.hpp"
// #include "nodes/BrightnessNode.hpp"
// #include "nodes/ThresholdNode.hpp"
// #include "nodes/BlurNode.hpp"
// #include "nodes/EdgeDetectionNode.hpp"

// // 🔁 Track (link_id, from_attr, to_attr)
// static int currentLinkId = 100;
// static std::vector<std::tuple<int, int, int>> links;

// int main() {
//     // GLFW init
//     if (!glfwInit()) return -1;
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     GLFWwindow* window = glfwCreateWindow(1280, 720, "Node Image Editor", nullptr, nullptr);
//     if (!window) return -1;
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1);
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

//     // ImGui setup
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImNodes::CreateContext();
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 330");
//     ImGui::StyleColorsDark();

//     // 🎯 Nodes
//     static ImageInputNode inputNode(1, "Image Input");
//     static BrightnessNode brightnessNode(2, "Brightness");
//     static ThresholdNode thresholdNode(3, "Threshold");
//     static BlurNode blurNode(4, "Blur");
//     static EdgeDetectionNode edgeNode(5, "Edge Detection");
//     static OutputNode outputNode(6, "Output");

//     // Main loop
//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();

//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();
//         ImGui::Begin("Node Editor");

//         ImNodes::BeginNodeEditor();

//         // 🧱 Draw + Process all
//         inputNode.drawUI();          inputNode.process();
//         brightnessNode.drawUI();    brightnessNode.process();
//         thresholdNode.drawUI();     thresholdNode.process();
//         blurNode.drawUI();          blurNode.process();
//         edgeNode.drawUI();          edgeNode.process();
//         outputNode.drawUI();        outputNode.process();

//         // 🔌 Draw links + route images
//         for (const auto& [linkId, from, to] : links) {
//             ImNodes::Link(linkId, from, to);

//             // 📦 Routing logic
//             if (from == inputNode.getOutputAttrId()) {
//                 if (to == brightnessNode.getInputAttrId()) brightnessNode.setInput(inputNode.getOutput());
//                 if (to == blurNode.getInputAttrId())       blurNode.setInput(inputNode.getOutput());
//                 if (to == thresholdNode.getInputAttrId())  thresholdNode.setInput(inputNode.getOutput());
//                 if (to == edgeNode.getInputAttrId())       edgeNode.setInput(inputNode.getOutput());
//                 if (to == outputNode.getInputAttrId())     outputNode.setInput(inputNode.getOutput());
//             }
//             if (from == brightnessNode.getOutputAttrId()) {
//                 if (to == blurNode.getInputAttrId())       blurNode.setInput(brightnessNode.getOutput());
//                 if (to == thresholdNode.getInputAttrId())  thresholdNode.setInput(brightnessNode.getOutput());
//                 if (to == edgeNode.getInputAttrId())       edgeNode.setInput(brightnessNode.getOutput());
//                 if (to == outputNode.getInputAttrId())     outputNode.setInput(brightnessNode.getOutput());
//             }
//             if (from == blurNode.getOutputAttrId()) {
//                 if (to == thresholdNode.getInputAttrId())  thresholdNode.setInput(blurNode.getOutput());
//                 if (to == edgeNode.getInputAttrId())       edgeNode.setInput(blurNode.getOutput());
//                 if (to == outputNode.getInputAttrId())     outputNode.setInput(blurNode.getOutput());
//             }
//             if (from == thresholdNode.getOutputAttrId()) {
//                 if (to == edgeNode.getInputAttrId())       edgeNode.setInput(thresholdNode.getOutput());
//                 if (to == outputNode.getInputAttrId())     outputNode.setInput(thresholdNode.getOutput());
//             }
//             if (from == edgeNode.getOutputAttrId()) {
//                 if (to == outputNode.getInputAttrId())     outputNode.setInput(edgeNode.getOutput());
//             }
//         }

//         ImNodes::EndNodeEditor();

//         // 🔧 Accept new links
//         int fromAttr, toAttr;
//         if (ImNodes::IsLinkCreated(&fromAttr, &toAttr)) {
//             links.emplace_back(currentLinkId++, fromAttr, toAttr);
//         }

//         ImGui::End();

//         // Render
//         ImGui::Render();
//         int w, h;
//         glfwGetFramebufferSize(window, &w, &h);
//         glViewport(0, 0, w, h);
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//         glfwSwapBuffers(window);
//     }

//     // Cleanup
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImNodes::DestroyContext();
//     ImGui::DestroyContext();
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <tuple>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"

#include "nodes/ImageInputNode.hpp"
#include "nodes/OutputNode.hpp"
#include "nodes/BrightnessNode.hpp" // 👈 Include brightness node
#include "nodes/ImageEffectNode.hpp"
// 🔁 Link tracking
static int currentLinkId = 100;
static std::vector<std::tuple<int, int, int>> links; // (link_id, from_attr, to_attr)

int main() {
    // 🔧 GLFW Init
    if (!glfwInit()) {
        std::cerr << "❌ Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Node Image Editor", nullptr, nullptr);
    if (!window) {
        std::cerr << "❌ Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "❌ Failed to load OpenGL via GLAD\n";
        return -1;
    }

    // 🧠 ImGui + ImNodes setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // 🔁 Node objects
    static ImageInputNode inputNode(1, "Image Input");
    // static BrightnessNode brightnessNode(3, "Brightness"); // 👈 Added here
    static ImageEffectNode effectNode(3, "Image Effect");
    static OutputNode outputNode(2, "Output Node");

    // 🌀 Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 🧠 Frame start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Node Editor");

        ImNodes::BeginNodeEditor();

        // 🎨 Draw UI for all nodes
        inputNode.drawUI();
        inputNode.process();

        // brightnessNode.drawUI();
        // brightnessNode.process();
        effectNode.drawUI();
        effectNode.process();
        
        outputNode.drawUI();
        outputNode.process();

        // 🔗 Draw links
        for (const auto& [linkId, from, to] : links) {
            ImNodes::Link(linkId, from, to);

            // if (from == inputNode.getOutputAttrId() && to == brightnessNode.getInputAttrId()) {
            //     brightnessNode.setInput(inputNode.getOutput());
            // }

            // if (from == brightnessNode.getOutputAttrId() && to == outputNode.getInputAttrId()) {
            //     outputNode.setInput(brightnessNode.getOutput());
            // }
            // 🌞 Input → Effect
            if (from == inputNode.getOutputAttrId() && to == effectNode.getInputAttrId()) {
                effectNode.setInput(inputNode.getOutput());
            }

            // 🌞 Effect → Output
            if (from == effectNode.getOutputAttrId() && to == outputNode.getInputAttrId()) {
                outputNode.setInput(effectNode.getOutput());
            }

        }

        ImNodes::EndNodeEditor(); // ✅ scope close before IsLinkCreated

        // 📌 New connections
        int fromAttr, toAttr;
        if (ImNodes::IsLinkCreated(&fromAttr, &toAttr)) {
            links.emplace_back(currentLinkId++, fromAttr, toAttr);
        }

        ImGui::End();

        // 🖼️ Render
        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // 🧹 Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}