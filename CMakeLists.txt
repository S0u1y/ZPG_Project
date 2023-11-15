cmake_minimum_required(VERSION 3.22.1)
include(CMakePrintHelpers)

project(Test)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE MODELS "${CMAKE_SOURCE_DIR}/Models/*")
file(GLOB_RECURSE COMPOSITE_TRANSFORMATIONS "${CMAKE_SOURCE_DIR}/Composite/Transformation/*")
file(GLOB_RECURSE SHADERS_SOURCES "${CMAKE_SOURCE_DIR}/Shaders/Sources/*")

file(COPY ${SHADERS_SOURCES} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp
        Application.h
        Application.cpp
        Camera.h
        Camera.cpp
        Composite/Composite.h
        ${MODELS} ${COMPOSITE_TRANSFORMATIONS}
        Factory/ModelFactory.cpp Factory/ModelFactory.h
        Observer/Observer.cpp
        Observer/Observer.h
        Observer/Subject.cpp
        Observer/Subject.h Light.cpp Light.h
        Shaders/Shader.cpp
        Shaders/Shader.h
        Shaders/ShaderLoader.cpp
        Shaders/ShaderLoader.h
        Shaders/ShaderProgram.cpp
        Shaders/ShaderProgram.h
        Shaders/ShaderProgramHolder.cpp
        Shaders/ShaderProgramHolder.h Material.cpp Material.h Scene.cpp Scene.h Scenes/Scenes.h Scenes/Scenes.cpp Composite/killmeplease.cpp Composite/killmeplease.h
        Scenes/Scenes_07.h
        Scenes/Scenes_07.cpp
        CameraLight.cpp
        CameraLight.h
        Scenes/Scenes_08.cpp
        Scenes/Scenes_08.h
        DirectionalLight.cpp
        DirectionalLight.h
        Textures/Texture.cpp
        Textures/Texture.h
        ModelLoader.cpp
        ModelLoader.h
        Textures/TextureHolder.cpp
        Textures/TextureHolder.h
        Textures/CubemapTexture.cpp
        Textures/CubemapTexture.h
        Models/skycube.h
        Models/CubemapModel.cpp
        Models/CubemapModel.h
)


#Link libraries on unix OS
if(UNIX)

    find_package(OpenGL REQUIRED)
    #find_package(GLUT REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(assimp REQUIRED)

    include_directories(${GLEW_INCLUDE_DIRS})
    include_directories(${ASSIMP_INCLUDE_DIRS})

    cmake_print_variables(ASSIMP_INCLUDE_DIRS assimp::assimp GLEW_INCLUDE_DIRS)

    target_link_libraries(Test glfw glm::glm ${GLEW_LIBRARIES} "/usr/lib/libSOIL.so" assimp::assimp ${OPENGL_LIBRARIES})

endif ()

#Link libraries on Windows OS
if(WIN32)

    find_package(OpenGL REQUIRED)
    find_package(assimp REQUIRED)
    find_package(Soil REQUIRED)

    set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)


    set(GLFW_DIR "${LIBS_DIR}/glfw-3.3.8.bin.WIN64")
    set(GLEW_DIR "${LIBS_DIR}/glew-2.1.0")
    set(GLM_DIR "${LIBS_DIR}/glm")

    target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_DIR})

    target_include_directories(${PROJECT_NAME} PUBLIC include)

    cmake_print_variables(ASSIMP_INCLUDE_DIRS assimp::assimp GLEW_INCLUDE_DIRS)
    cmake_print_variables(SOIL_INCLUDE_DIRS Soil::Soil SOIL_LIBRARIES SOIL_INCLUDE_LIBRARIES)
    cmake_print_variables(Soil::soil)
    cmake_print_variables(assimp ASSIMP_INCLUDE_LIBRARIES ASSIMP_LIBRARIES)
    cmake_print_variables(SOIL ASSIMP include OPENGL_gl_LIBRARY)

    target_link_libraries(${PROJECT_NAME} ${GLFW_DIR}/lib-vc2022/glfw3.lib)
    target_link_libraries(${PROJECT_NAME} ${GLEW_DIR}/lib/Release/x64/glew32.lib)
    target_link_libraries(${PROJECT_NAME} assimp::assimp ${ASSIMP_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} soil)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

    file(COPY ${GLFW_DIR}/lib-vc2022/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${GLEW_DIR}/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
endif ()

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${SHADERS_SOURCES} ${CMAKE_BINARY_DIR})

