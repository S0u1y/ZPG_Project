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

#include "Shader.h"
#include "Camera.h"
#include "Shape.h"
#include "Square.h"
#include "Triangle.h"

#include "Models/suzi_flat.h"
#include "Models/sphere.h"
#include "Model.h"

using std::vector, std::unique_ptr;

class Application {
private:


    static void error_callback(int error, const char* description){ fputs(description, stderr); }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
    }

    static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

    static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

    static void window_size_callback(GLFWwindow* window, int width, int height){
        printf("resize %d, %d \n", width, height);
        glViewport(0, 0, width, height);
    }

    static void cursor_callback(GLFWwindow *window, double x, double y){ printf("cursor_callback \n"); }

    static void button_callback(GLFWwindow* window, int button, int action, int mode){
        if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
    }

    GLFWwindow* window;

    Shader shaderMain;
    Camera camera{&shaderMain};

    vector<unique_ptr<Shape>> shapes;

public:
    explicit Application() {
        shaderMain.linkCamera(&camera);
        camera.setPerspective(60.f, 4.f/3.f, 0.1f, 5.f);
    }

    void initialize(){

        glfwSetErrorCallback(error_callback);
        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            exit(EXIT_FAILURE);
        }
        /*
        //inicializace konkretni verze
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        */

        window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        glewExperimental = GL_TRUE;
        glewInit();

        // Sets the key callback
        glfwSetKeyCallback(window, key_callback);

        glfwSetCursorPosCallback(window, cursor_callback);

        glfwSetMouseButtonCallback(window, button_callback);

        glfwSetWindowFocusCallback(window, window_focus_callback);

        glfwSetWindowIconifyCallback(window, window_iconify_callback);

        glfwSetWindowSizeCallback(window, window_size_callback);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = (float)width / (float)height;
        glViewport(0, 0, width, height);

    };

    void createShaders(){//create class working with shaders..
        shaderMain.create();
    };
    void createModels(){
//        shapes.push_back(unique_ptr<Shape>(new Square(0,0,0))); //create class containing shapes
//        shapes.push_back(unique_ptr<Shape>(new Square(0,0,0)));
        shapes.push_back(unique_ptr<Shape>(new Model(0,0,0,sphere, sizeof(sphere)/sizeof(sphere[0]))));
        shapes[0]->scale(glm::vec3(0.3));

    };

    void drawModels(){

        shapes[0]->rotate(glm::radians(1.f), glm::vec3(1,1,0)); //rotate model :)

//        shapes[1]->rotate(glm::radians(1.f), glm::vec3(0,0,-1));
//
////        //orbit O.O
//
//        shapes[0]->rotate(glm::radians(1.f), glm::vec3(0,0,-1));
//        shapes[0]->move(glm::vec3(1,0,0));

        for (const auto &item : shapes){
            camera.metoda();
            item->draw(shaderMain);
        }

//        shapes[0]->move(glm::vec3(-1,0,0));


    }

    void run(){

        glEnable(GL_DEPTH_TEST);

        while (!glfwWindowShouldClose(window))
        {
            // clear color and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            drawModels();

            // update other events like input handling
            glfwPollEvents();
            // put the stuff we’ve been drawing onto the display
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    };
};


#endif //TEST_APPLICATION_H