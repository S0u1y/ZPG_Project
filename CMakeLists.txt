cmake_minimum_required(VERSION 3.20)
project(Test)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp
        Application.h
        Shape.h
        Shader.h Composite/Composite.h)

#Link libraries on unix OS
if(UNIX)

    find_package(OpenGL REQUIRED)
    #find_package(GLUT REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(GLEW REQUIRED)

    include_directories(${GLEW_INCLUDE_DIRS})

    target_link_libraries(Test ${OPENGL_LIBRARIES} glfw glm::glm ${GLEW_LIBRARIES})

endif ()

#Link libraries on Windows OS
if(WIN32)

    set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

    find_package(OpenGL REQUIRED)
    set(GLFW_DIR "${LIBS_DIR}/glfw-3.3.8.bin.WIN64")
    set(GLEW_DIR "${LIBS_DIR}/glew-2.1.0")
    set(GLM_DIR "${LIBS_DIR}/glm")

    # Nastavení cest k hlavičkovým souborům pro GLFW, GLEW, GLM
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/include)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_DIR})

    # Linkování s knihovnami GLFW, GLEW a OPENGL
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/lib-mingw-w64/glfw3.dll)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/bin/Release/x64/glew32.dll)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})

    # Kopírovaní glfw3.dll do cmake-build folder
    file(COPY ${GLFW_DIR}/lib-mingw-w64/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${GLEW_DIR}/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
endif ()


