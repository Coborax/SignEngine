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
        src/Scene/Entity.h
        src/Scripting/LuaScriptEngine.cpp
        src/Scripting/LuaScriptEngine.h)
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

# Set Lua source files
# set(LUA_SOURCES
#     includes/lua/src/lapi.c
#     includes/lua/src/lauxlib.c
#     includes/lua/src/lbaselib.c
#     includes/lua/src/lcode.c
#     includes/lua/src/ldblib.c
#     includes/lua/src/ldebug.c
#     includes/lua/src/ldo.c
#     includes/lua/src/ldump.c
#     includes/lua/src/lfunc.c
#     includes/lua/src/lgc.c
#     includes/lua/src/linit.c
#     includes/lua/src/liolib.c
#     includes/lua/src/llex.c
#     includes/lua/src/lmathlib.c
#     includes/lua/src/lmem.c
#     includes/lua/src/loadlib.c
#     includes/lua/src/lobject.c
#     includes/lua/src/lopcodes.c
#     includes/lua/src/loslib.c
#     includes/lua/src/lparser.c
#     includes/lua/src/lstate.c
#     includes/lua/src/lstring.c
#     includes/lua/src/lstrlib.c
#     includes/lua/src/ltable.c
#     includes/lua/src/ltablib.c
#     includes/lua/src/ltm.c
#     includes/lua/src/lundump.c
#     includes/lua/src/lvm.c
#     includes/lua/src/lzio.c
# )
# # Compile Lua as a static library
# add_library(lua STATIC ${LUA_SOURCES})
# target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/lua/src)
# target_link_libraries(SignE PUBLIC lua)

find_package(Lua 5.4 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(SignE PUBLIC ${LUA_LIBRARIES})

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
