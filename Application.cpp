//
// Created by wizzy on 14.10.2023.
//

#include "Application.h"

Application* Application::GLFWCallbackWrapper::application = nullptr;

void Application::GLFWCallbackWrapper::setApplication(Application *p_application) {
    GLFWCallbackWrapper::application = p_application;
}

bool locked = false;
bool picking = false;

void Application::GLFWCallbackWrapper::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //add observer here for camera
    if(action == GLFW_PRESS or action == GLFW_REPEAT)
    {
        if(key == GLFW_KEY_W){
            application->camera->moveForward();
        }
        if(key == GLFW_KEY_A){
            application->camera->moveLeft(application->deltaT);
        }
        if(key == GLFW_KEY_S){
            application->camera->moveBack();
        }
        if(key == GLFW_KEY_D){
            application->camera->moveRight(application->deltaT);
        }
        if(key== GLFW_KEY_Q){
            locked = !locked;

            if(locked){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }else{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        if(key== GLFW_KEY_P){
            picking = !picking;
        }
    }
//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

int width_, height_;
int x_{0};
int y_{0};

void Application::GLFWCallbackWrapper::window_size_callback(GLFWwindow *window, int width, int height) {
//    printf("resize %d, %d\n", width, height);
    float ratio{(float)width_/(float)height_};
    application->camera->setPerspective(60, ratio, 0.1, 100);
    application->camera->notify();

    glViewport(0, 0, width_, height_);

    width_ = width;
    height_ = height;
}

void Application::GLFWCallbackWrapper::cursor_callback(GLFWwindow *window, double x, double y) {

    if(locked){

        float rotX = 100 * (float)(x - ((float)width_ / 2)) / (float)width_;
        float rotY = 100 * (float)(y - ((float)height_ / 2)) / (float)height_;

        application->camera->lookX(rotX);
        application->camera->lookY(rotY);

        glfwSetCursorPos(window, (float)width_/2, (float)height_/2);
    }
    x_ = x;
    y_ = y;

}

void Application::GLFWCallbackWrapper::button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS && picking){
        GLuint index;

        glReadPixels(x_, height_ - y_ - 10, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("button_callback [%d,%d,%d]\n", button, action, mode);
        printf("stencil index %u\n", index);

        int i = 0;
        application->scene->shapesForEach([&i, &index](Shape* shape){
            shape->material.color = {1,1,1};
            if( i+1 == index ){
                shape->material.color = {0, 1, 0};
            }
            i++;
        });

    }
}

Application::Application() {
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

    glfwSetMouseButtonCallback(window, GLFWCallbackWrapper::button_callback);

    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwSetWindowIconifyCallback(window, window_iconify_callback);

    glfwSetWindowSizeCallback(window, GLFWCallbackWrapper::window_size_callback);

    //TODO make width and height values of application and then scene
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = (float)width / (float)height;
    glViewport(0, 0, width, height);

    width_ = width;
    height_ = height;

    scenes.initialize();
    scene = scenes["Zidle"];

    scene->setWindow(window);
    camera = &scene->camera;

    scene->camera.setPerspective(60.f, ratio, 0.1f, 100.f);

}

void Application::createShaders() {
    scene->initializeShaders();
}

void Application::createModels() {

}

void Application::drawModels() {

//    shaderProgramHolder["Gradient"]->setUniform("time", (float)glfwGetTime() );

    scene->drawModels();

}

void Application::run() {

    glEnable(GL_DEPTH_TEST);

    //enable stencil
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while (!glfwWindowShouldClose(window))
    {
        deltaT = (float)glfwGetTime() - lastTime;
        lastTime = (float)glfwGetTime();

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
