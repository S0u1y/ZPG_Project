//
// Created by Filip on 14.10.2023.
//

#include "Application.h"

#include "Models/suzi_smooth.h"
#include "Models/Sphere.h"

Application* Application::GLFWCallbackWrapper::application = nullptr;

void Application::GLFWCallbackWrapper::setApplication(Application *p_application) {
    GLFWCallbackWrapper::application = p_application;
}

void Application::GLFWCallbackWrapper::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(action == GLFW_PRESS or action == GLFW_REPEAT)
    switch(key){
        case GLFW_KEY_W:{

            application->camera.moveForward();

            break;
        }
        case GLFW_KEY_A:{

            application->camera.moveLeft(application->deltaT);

            break;
        }
        case GLFW_KEY_S:{

            application->camera.moveBack();

            break;
        }
        case GLFW_KEY_D:{

            application->camera.moveRight(application->deltaT);
            break;
        }
        case GLFW_KEY_RIGHT:{

            application->camera.lookX(1);
            break;
        }
        case GLFW_KEY_LEFT:{

            application->camera.lookX(-1);

            break;
        }
    }
//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::GLFWCallbackWrapper::window_size_callback(GLFWwindow *window, int width, int height) {
//    printf("resize %d, %d\n", width, height);
    application->camera.setPerspective(60, (float)width/(float)height, 0.1, 100);
    glViewport(0, 0, width, height);
}

void Application::GLFWCallbackWrapper::cursor_callback(GLFWwindow *window, double x, double y) {
//    printf("cursor_callback\n");
}


Application::Application() {
    shaderProgram.createShader("MainShader",
                               "#version 330\n"
                                             "layout(location=0) in vec4 vp;"
                                             "layout(location=1) in vec4 acolor;"
                                             "out vec4 color;"
                                             "uniform mat4 MVP;"
                                             "uniform mat4 viewMatrix;"
                                             "uniform mat4 projectionMatrix;"
                                             "void main () {"
                                             "    gl_Position = projectionMatrix * viewMatrix * MVP * vp;"
                                             "    color = acolor;"
                                             "}"
                                             ,"#version 330\n"
                                                  "out vec4 frag_colour;"
                                                  "in vec4 color;"
                                                  "void main () {"
                                                  "    frag_colour = color;"
                                                  "}");



    shaderProgram.getShader("MainShader").linkCamera(&camera);
    camera.linkShader(&shaderProgram.getShader("MainShader"));
    camera.setPerspective(60.f, 4.f/3.f, 0.1f, 100.f);
    GLFWCallbackWrapper::setApplication(this);
}

void Application::initialize() {

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
    glfwSetKeyCallback(window, GLFWCallbackWrapper::key_callback);

    glfwSetCursorPosCallback(window, GLFWCallbackWrapper::cursor_callback);

    glfwSetMouseButtonCallback(window, button_callback);

    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwSetWindowIconifyCallback(window, window_iconify_callback);

    glfwSetWindowSizeCallback(window, GLFWCallbackWrapper::window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = (float)width / (float)height;
    glViewport(0, 0, width, height);

}

void Application::createShaders() {//create class working with shaders..
    shaderProgram.createAllShaders();
}

void Application::createModels() {
    shapes.push_back(unique_ptr<Shape>(new Sphere(0,0,0)));
//    shapes[0]->scale(glm::vec3(0.3));
}

void Application::drawModels() {

//    shapes[0]->rotate(glm::radians(1.f), glm::vec3(1,1,0)); //rotate model :)
    camera.metoda();

    for (const auto &item : shapes){

        item->draw(shaderProgram.getShader("MainShader"));
    }


}

void Application::run() {

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        deltaT = (float)glfwGetTime() - lastTime;
        lastTime = (float)glfwGetTime();

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
}
