# Add the console application
add_executable(SignEditor src/main.cpp src/EditorLayer.cpp src/EditorLayer.h)
target_link_libraries(SignEditor PRIVATE SignE)

target_link_libraries(SignEditor PRIVATE raylib)
target_link_libraries(SignEditor PRIVATE spdlog)
target_link_libraries(SignEditor PRIVATE EnTT)
target_link_libraries(SignEditor PRIVATE imgui)