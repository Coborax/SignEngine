add_library(SignE STATIC
        src/Application/Application.cpp
        src/Application/ApplicationLayer.h
        src/Application/Window.cpp
        src/Application/Window.h
        src/Application/ApplicationLayer.cpp
        src/Application/ImGuiLayer.cpp
        src/Application/ImGuiLayer.h

        src/Log.h
        src/Ref.h

        src/FileSystem/VirtualFileSystem.h
        src/FileSystem/VirtualFileSystem.cpp
        
        src/Renderer/Renderer.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer2D.h
        src/Renderer/Renderer2D.cpp
        src/Renderer/IndexBuffer.h
        src/Renderer/IndexBuffer.cpp
        src/Renderer/VertexBuffer.h
        src/Renderer/VertexBuffer.cpp
        src/Renderer/VertexArray.h
        src/Renderer/VertexArray.cpp
        src/Renderer/Shader.h
        src/Renderer/Shader.cpp

        src/Platform/OpenGL/OpenGLRenderer.h
        src/Platform/OpenGL/OpenGLRenderer.cpp
        src/Platform/OpenGL/OpenGLVertexBuffer.h
        src/Platform/OpenGL/OpenGLVertexBuffer.cpp
        src/Platform/OpenGL/OpenGLIndexBuffer.h
        src/Platform/OpenGL/OpenGLIndexBuffer.cpp
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLShader.h
        src/Platform/OpenGL/OpenGLShader.cpp

        src/Scene/Scene.h
        src/Scene/Scene.cpp
        src/Scene/Components.h
        src/Scene/Entity.cpp
        src/Scene/Entity.h
        src/Scene/SceneSerializer.cpp
        src/Scene/SceneSerializer.h

        src/Scripting/LuaScriptGlue.cpp
        src/Scripting/LuaScriptGlue.h
        src/Scripting/LuaScriptEngine.cpp
        src/Scripting/LuaScriptEngine.h)
target_include_directories(SignE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#### VCPKG ####

# Add EnTT
find_package(EnTT CONFIG REQUIRED)
include_directories(${EnTT_INCLUDE_DIR})
target_link_libraries(SignE PRIVATE EnTT::EnTT)

# Add ImGui
find_package(imgui CONFIG REQUIRED)
include_directories(${imgui_INCLUDE_DIR})
link_directories(${imgui_LIBRARY_DIR})
target_link_libraries(SignE PRIVATE imgui::imgui)

# Add yaml-cpp 
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(SignE PRIVATE yaml-cpp)

# Add spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(SignE PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# Add Lua
find_package(Lua CONFIG REQUIRED)
target_include_directories(SignE PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(SignE PRIVATE ${LUA_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(SignE PRIVATE OpenGL::GL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(SignE PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(SignE PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(SignE PRIVATE glm::glm)
