add_library(SignE STATIC
        src/Application/Application.cpp
        src/Application/ApplicationLayer.h
        src/Log.h
        src/Renderer/Renderer2D.h
        src/Renderer/Renderer2D.cpp
        src/Scene/Scene.h
        src/Scene/Scene.cpp
        src/Application/ApplicationLayer.cpp
        src/Application/ImGuiLayer.cpp
        src/Application/ImGuiLayer.h
        src/Scene/Components.h
        src/Scene/Entity.cpp
        src/Scene/Entity.h)
target_include_directories(SignE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add Raylib
add_subdirectory(includes/raylib)
target_link_libraries(SignE PRIVATE raylib)

# Add spdlog
add_subdirectory(includes/spdlog)
target_link_libraries(SignE PRIVATE spdlog)

# Add EnTT
add_subdirectory(includes/entt)
target_link_libraries(SignE PRIVATE EnTT)

# Add ImGui
add_library(imgui STATIC
        includes/imgui/imgui.cpp
        includes/imgui/imgui.h
        includes/imgui/imstb_rectpack.h
        includes/imgui/imstb_textedit.h
        includes/imgui/imstb_truetype.h
        includes/imgui/imgui_demo.cpp
        includes/imgui/imgui_draw.cpp
        includes/imgui/imgui_internal.h
        includes/imgui/imgui_tables.cpp
        includes/imgui/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/imgui)
target_link_libraries(SignE PRIVATE imgui)

# Add rlImGui
add_library(rlImGui STATIC
        includes/rlImGui/rlImGui.cpp
        includes/rlImGui/rlImGui.h
        includes/rlImGui/rlImGuiColors.h
)
target_include_directories(rlImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/rlImGui)
target_link_libraries(rlImGui PRIVATE raylib)
target_link_libraries(rlImGui PRIVATE imgui)
target_link_libraries(SignE PRIVATE rlImGui)