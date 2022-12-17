add_library(SignE STATIC src/Application/Application.cpp src/Application/ApplicationLayer.h src/Log.h src/Renderer/Renderer2D.h src/Renderer/Renderer2D.cpp)
target_include_directories(SignE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(includes/raylib)
target_link_libraries(SignE PRIVATE raylib)

add_subdirectory(includes/spdlog)
target_link_libraries(SignE PRIVATE spdlog)