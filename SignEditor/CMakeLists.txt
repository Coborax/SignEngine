# Add the console application
add_executable(SignEditor src/main.cpp src/EditorLayer.cpp src/EditorLayer.h)
target_link_libraries(SignEditor PRIVATE SignE)

# Add EnTT
find_package(EnTT CONFIG REQUIRED)
# include_directories(${EnTT_INCLUDE_DIR})
target_link_libraries(SignEditor PRIVATE EnTT::EnTT)

# Add ImGui
find_package(imgui CONFIG REQUIRED)
include_directories(${imgui_INCLUDE_DIR})
link_directories(${imgui_LIBRARY_DIR})
target_link_libraries(SignEditor PRIVATE imgui::imgui)

# Add yaml-cpp 
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE yaml-cpp)

# Add spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# Add Lua
find_package(Lua CONFIG REQUIRED)
target_include_directories(SignEditor PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(SignEditor PRIVATE ${LUA_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(SignEditor PRIVATE OpenGL::GL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(SignEditor PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE glm::glm)

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE tinyobjloader::tinyobjloader)

find_package(imguizmo CONFIG REQUIRED)
target_link_libraries(SignEditor PRIVATE imguizmo::imguizmo)
