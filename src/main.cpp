
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
#include "nodes/ImageEffectNode.hpp"  // ✅ Unified effect node

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

    // 🧱 Node instances
    static ImageInputNode inputNode(1, "Image Input");
    static ImageEffectNode effectNode(3, "Image Effect");
    static OutputNode outputNode(2, "Output Node");

    // 🌀 Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 🧠 Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Node Editor");

        ImNodes::BeginNodeEditor();

        // 🎨 Draw and process nodes
        inputNode.drawUI();
        inputNode.process();

        effectNode.drawUI();
        effectNode.process();

        outputNode.drawUI();
        outputNode.process();

        // 🔗 Handle links and routing
        for (const auto& [linkId, from, to] : links) {
            ImNodes::Link(linkId, from, to);

            if (from == inputNode.getOutputAttrId() && to == effectNode.getInputAttrId()) {
                effectNode.setInput(inputNode.getOutput());
            }

            if (from == effectNode.getOutputAttrId() && to == outputNode.getInputAttrId()) {
                outputNode.setInput(effectNode.getOutput());
            }
        }

        ImNodes::EndNodeEditor(); // ✅ required after all UI calls

        // 📌 Handle new connections
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
