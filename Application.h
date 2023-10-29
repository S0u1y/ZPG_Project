//
// Created by wizzy on 27.9.23.
//

#ifndef TEST_APPLICATION_H
#define TEST_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <memory>

#include "Camera.h"
#include "Shaders/ShaderProgramHolder.h"
#include "Light.h"
#include "Scene.h"

#include "Scenes/Scenes.h"

class Shape;

using std::vector, std::unique_ptr;

class Application {
private:

    GLFWwindow* window;

    ShaderProgramHolder shaderProgramHolder;

    Camera* camera;

    Light light;
    vector<unique_ptr<Shape>> shapes;

    Scenes scenes;
    Scene* scene;

    float deltaT{0};
    float lastTime{0};

    static void error_callback(int error, const char* description){ fputs(description, stderr); }

    static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

    static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }



    static void button_callback(GLFWwindow* window, int button, int action, int mode){
        if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
    }

    class GLFWCallbackWrapper{
    public:
        GLFWCallbackWrapper() = delete;
        GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
        GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
        ~GLFWCallbackWrapper() = delete;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursor_callback(GLFWwindow *window, double x, double y);
        static void window_size_callback(GLFWwindow* window, int width, int height);

        static void setApplication(Application* p_application);

    private:
        static Application* application;
    };



public:
    explicit Application();

    void initialize();;

    void createShaders();;
    void createModels();;

    void drawModels();

    void run();;
};




#endif //TEST_APPLICATION_H
