cmake_minimum_required(VERSION 3.10)
project(NodeImageEditor)

set(CMAKE_CXX_STANDARD 17)

# -------------------------------
# 🔹 OpenCV
# -------------------------------
set(OpenCV_DIR "/opt/homebrew/Cellar/opencv/4.11.0_1/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# -------------------------------
# 🔹 GLFW (via pkg-config)
# -------------------------------
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# -------------------------------
# 🔹 Glad (OpenGL Loader)
# -------------------------------
add_library(glad STATIC src/utils/glad.c)
target_include_directories(glad PUBLIC include)

# -------------------------------
# 🔹 ImGui
# -------------------------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
    /opt/homebrew/include            # GLFW headers
)

# -------------------------------
# 🔹 ImNodes
# -------------------------------
set(IMNODES_IMGUI_TARGET_NAME imgui)
add_subdirectory(external/imnodes)

# -------------------------------
# 🔹 Includes
# -------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    external/imgui
    external/imnodes
)

# -------------------------------
# 🔹 Source Files
# -------------------------------
file(GLOB_RECURSE SOURCES src/*.cpp)

# -------------------------------
# 🔹 Executable
# -------------------------------
add_executable(NodeImageEditor ${SOURCES})

# -------------------------------
# 🔹 Link All Libraries
# -------------------------------
target_link_libraries(NodeImageEditor PRIVATE
    glad
    ${GLFW_LIBRARIES}
    imgui
    imnodes
    ${OpenCV_LIBS}
)