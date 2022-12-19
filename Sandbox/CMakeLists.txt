# Add the console application
add_executable(Sandbox src/main.cpp)
target_link_libraries(Sandbox PRIVATE SignE)

target_link_libraries(Sandbox PRIVATE raylib)
target_link_libraries(Sandbox PRIVATE spdlog)
target_link_libraries(Sandbox PRIVATE EnTT)
target_link_libraries(Sandbox PRIVATE imgui)