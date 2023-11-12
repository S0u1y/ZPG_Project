cmake_minimum_required(VERSION 3.20)
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
        ModelLoader.h)


#Link libraries on unix OS
if(UNIX)

    find_package(OpenGL REQUIRED)
    #find_package(GLUT REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(GLEW REQUIRED)
#    find_package(SOIL REQUIRED) # for loading textures

    include_directories(${GLEW_INCLUDE_DIRS})
    link_directories("/usr/local/lib/libSOIL.a")


    target_link_libraries(Test ${OPENGL_LIBRARIES} glfw glm::glm ${GLEW_LIBRARIES})

endif ()

#Link libraries on Windows OS
if(WIN32)

    include(CMakePrintHelpers)

    find_package(assimp REQUIRED)

    set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

    find_package(OpenGL REQUIRED)
    set(GLFW_DIR "${LIBS_DIR}/glfw-3.3.8.bin.WIN64")
    set(GLEW_DIR "${LIBS_DIR}/glew-2.1.0")
    set(GLM_DIR "${LIBS_DIR}/glm")
    set(SOIL_DIR "${LIBS_DIR}/soil")
#    set(ASSIMP_DIR "${LIBS_DIR}/assimp/assimp")

#    find_library(ASSIMP_LIBRARY NAMES assimp-vc143-mtd HINTS ${ASSIMP_DIR}/lib/Debug)
#    cmake_print_variables(ASSIMP_LIBRARY)

    target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_DIR})

#    target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_DIR}/include)

#    library does get found, but linking it all together does not work..
    file(GLOB_RECURSE SOIL_SOURCES "${SOIL_DIR}/include/*.c")
    cmake_print_variables(SOIL_SOURCES)
#    add_library(Testus ${SOIL_DIR}/include/SOIL.c ${SOIL_DIR}/include/stb_image_aug.c ${SOIL_DIR}/include/image_DXT.c ${SOIL_DIR}/include/image_helper.c)
    add_library(Testus ${SOIL_SOURCES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${SOIL_DIR}/include)
#    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE ${SOIL_DIR}/lib/libSOIL.a)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} Testus)

    target_link_libraries(${PROJECT_NAME} ${GLFW_DIR}/lib-mingw-w64/glfw3.dll)
    target_link_libraries(${PROJECT_NAME} ${GLEW_DIR}/bin/Release/x64/glew32.dll)
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_DIR}/bin/Debug/assimp-vc143-mtd.dll)
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARY})
    target_link_libraries(${PROJECT_NAME} assimp::assimp)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

    file(COPY ${GLFW_DIR}/lib-mingw-w64/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${GLEW_DIR}/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
#    file(COPY ${ASSIMP_DIR}/bin/Debug/assimp-vc143-mtd.dll DESTINATION ${CMAKE_BINARY_DIR})
#    file(COPY ${ASSIMP_DIR}/lib/Debug/assimp-vc143-mtd.lib DESTINATION ${CMAKE_BINARY_DIR})
endif ()

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${SHADERS_SOURCES} ${CMAKE_BINARY_DIR})

