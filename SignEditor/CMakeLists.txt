# Add the console application
add_executable(SignEditor src/main.cpp src/EditorLayer.cpp src/EditorLayer.h)
target_link_libraries(SignEditor PRIVATE SignE)

# Add ImGui
find_package(imgui CONFIG REQUIRED)
include_directories(${imgui_INCLUDE_DIR})
link_directories(${imgui_LIBRARY_DIR})
target_link_libraries(SignEditor PRIVATE imgui::imgui)
