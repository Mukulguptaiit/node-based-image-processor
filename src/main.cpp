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
    static BrightnessNode brightnessNode(3, "Brightness"); // 👈 Added here
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

        brightnessNode.drawUI();
        brightnessNode.process();

        outputNode.drawUI();
        outputNode.process();

        // 🔗 Draw links
        for (const auto& [linkId, from, to] : links) {
            ImNodes::Link(linkId, from, to);

            if (from == inputNode.getOutputAttrId() && to == brightnessNode.getInputAttrId()) {
                brightnessNode.setInput(inputNode.getOutput());
            }

            if (from == brightnessNode.getOutputAttrId() && to == outputNode.getInputAttrId()) {
                outputNode.setInput(brightnessNode.getOutput());
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