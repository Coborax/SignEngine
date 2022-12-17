add_library(SignE STATIC src/Application.cpp)
target_include_directories(SignE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(includes/raylib)
target_link_libraries(SignE PRIVATE raylib)