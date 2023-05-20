# Add the console application
add_executable(Sandbox src/main.cpp)
target_link_libraries(Sandbox PRIVATE SignE)

# Add EnTT
find_package(EnTT CONFIG REQUIRED)
# include_directories(${EnTT_INCLUDE_DIR})
target_link_libraries(Sandbox PRIVATE EnTT::EnTT)

# Add ImGui
find_package(imgui CONFIG REQUIRED)
include_directories(${imgui_INCLUDE_DIR})
link_directories(${imgui_LIBRARY_DIR})
target_link_libraries(Sandbox PRIVATE imgui::imgui)

# Add yaml-cpp 
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(Sandbox PRIVATE yaml-cpp)

# Add spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(Sandbox PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# Add Lua
find_package(Lua CONFIG REQUIRED)
target_include_directories(Sandbox PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(Sandbox PRIVATE ${LUA_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(Sandbox PRIVATE OpenGL::GL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Sandbox PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Sandbox PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Sandbox PRIVATE glm::glm)

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(Sandbox PRIVATE tinyobjloader::tinyobjloader)
