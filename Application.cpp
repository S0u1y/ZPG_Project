//
// Created by Filip on 14.10.2023.
//

#include "Application.h"

#include "Factory/ModelFactory.h"

Application* Application::GLFWCallbackWrapper::application = nullptr;

void Application::GLFWCallbackWrapper::setApplication(Application *p_application) {
    GLFWCallbackWrapper::application = p_application;
}

bool locked = false;
//TODO make camera into an observer, that listens to this callback
void Application::GLFWCallbackWrapper::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //add observer here for camera
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
        case GLFW_KEY_Q:{

            locked = !locked;

            if(locked){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }else{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            break;
        }
    }
//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

int _width, _height;

//TODO make camera into an observer, that listens to this callback
void Application::GLFWCallbackWrapper::window_size_callback(GLFWwindow *window, int width, int height) {
//    printf("resize %d, %d\n", width, height);
    application->camera.setPerspective(60, (float)width/(float)height, 0.1, 100);
    glViewport(0, 0, width, height);

    _width = width;
    _height = height;
}

//TODO make camera into an observer, that listens to this callback
void Application::GLFWCallbackWrapper::cursor_callback(GLFWwindow *window, double x, double y) {

    if(locked){

        float rotX = 100 * (float)(x - ((float)_width / 2)) / (float)_width;
        float rotY = 100 * (float)(y - ((float)_height / 2)) / (float)_height;

        application->camera.lookX(rotX);
        application->camera.lookY(rotY);

        glfwSetCursorPos(window, (float)_width/2, (float)_height/2);
    }
}


Application::Application() {
    shaderProgram.createShader("Gradient",
                               "#version 400\n"
                                             "layout(location=0) in vec4 vp;"
                                             "layout(location=1) in vec4 normal;"

                                             "vec3 colorA = vec3(0.9,0.141,0.149);"
                                             "vec3 colorB = vec3(1.000,0.833,0.224);"

                                             "out vec4 color;"
                                             "uniform mat4 MVP;"
                                             "uniform mat4 viewMatrix;"
                                             "uniform mat4 projectionMatrix;"

                                             "uniform float time;"

                                             "void main () {\n"
                                             "      gl_Position = projectionMatrix * viewMatrix * MVP * vp;\n"
                                             "      float pct = abs(sin(time));\n"
                                             "      color = mix(vec4(colorA, 1), normal, pct);\n"
                                             "}"
                                             ,"#version 330\n"
                                                  "out vec4 frag_colour;"
                                                  "in vec4 color;"
                                                  "void main () {"
                                                  "    frag_colour = color;"
                                                  "}");
    shaderProgram.createShader("MainShader", "#version 400\n"
                                             "layout(location=0) in vec4 vp;"
                                             "layout(location=1) in vec4 normal;"
                                             "out vec4 color;"
                                             "uniform mat4 MVP;"
                                             "uniform mat4 viewMatrix;"
                                             "uniform mat4 projectionMatrix;"

                                             "void main () {\n"
                                             "      gl_Position = projectionMatrix * viewMatrix * MVP * vp;\n"
                                             "      color = normal;\n"
                                             "}"
                                            ,"#version 330\n"
                                             "out vec4 frag_colour;"
                                             "in vec4 color;"
                                             "void main () {"
                                             "    frag_colour = color;"
                                             "}");



    shaderProgram.getShader("MainShader").linkCamera(&camera);
    shaderProgram.getShaderp("Gradient")->linkCamera(&camera);

    camera.linkShader(shaderProgram.getShaderp("MainShader"));
    camera.linkShader(shaderProgram.getShaderp("Gradient"));

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

    //TODO make width and height values of application and then scene
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = (float)width / (float)height;
    glViewport(0, 0, width, height);

    _width = width;
    _height = height;

}

void Application::createShaders() {//create class working with shaders..
    shaderProgram.createAllShaders();
}

//TODO create scene class
void Application::createModels() {
    camera.notifyShaders(); //initial render for camera. Shaders need to be created!

    auto sphere0 = new Sphere(1.5,0,0);
    sphere0->setShader(shaderProgram.getShaderp("Gradient"));

    auto sphere1 = new Sphere(-1.5,0,0);
    sphere1->setShader(shaderProgram.getShaderp("MainShader"));

    auto sphere2 = new Sphere(0,1.5,0);
    sphere2->setShader(shaderProgram.getShaderp("Gradient"));

    auto sphere3 = new Sphere(0,-1.5,0);
    sphere3->setShader(shaderProgram.getShaderp("MainShader"));

    auto suziF = ModelFactory::createModel("suzi_flat", 0,0,0);
    suziF->setShader(shaderProgram.getShaderp("MainShader"));


    shapes.push_back(unique_ptr<Shape>(sphere0));
    shapes.push_back(unique_ptr<Shape>(sphere1));
    shapes.push_back(unique_ptr<Shape>(sphere2));
    shapes.push_back(unique_ptr<Shape>(sphere3));

    shapes.push_back(unique_ptr<Shape>(suziF));

//    shapes[0]->scale(glm::vec3(0.3));
}

void Application::drawModels() {

//    shapes[0]->rotate(glm::radians(1.f), glm::vec3(1,1,0)); //rotate model :)

    shaderProgram.getShader("Gradient").setUniformFloat("time", (float)glfwGetTime() );

    shapes[0]->rotate(glm::radians(1.f), glm::vec3(0,1,0));
    shapes[0]->move(-1.5, 0, 0);

    shapes[1]->rotate(glm::radians(1.f), glm::vec3(0,1,0));
    shapes[1]->move(1.5, 0, 0);

    for (const auto &item : shapes){

        item->draw();
    }

    shapes[0]->move(1.5, 0, 0);
    shapes[1]->move(-1.5, 0, 0);
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
