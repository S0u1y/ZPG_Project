//
// Created by wizzy on 14.10.2023.
//

#include "Application.h"

#include "Factory/ModelFactory.h"

#define SCENE 0

Application* Application::GLFWCallbackWrapper::application = nullptr;

void Application::GLFWCallbackWrapper::setApplication(Application *p_application) {
    GLFWCallbackWrapper::application = p_application;
}

bool locked = false;
void Application::GLFWCallbackWrapper::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //add observer here for camera
    if(action == GLFW_PRESS or action == GLFW_REPEAT)
    {
        if(key == GLFW_KEY_W){
            application->camera.moveForward();
        }
        if(key == GLFW_KEY_A){
            application->camera.moveLeft(application->deltaT);
        }
        if(key == GLFW_KEY_S){
            application->camera.moveBack();
        }
        if(key == GLFW_KEY_D){
            application->camera.moveRight(application->deltaT);
        }
        if(key== GLFW_KEY_Q){
            locked = !locked;

            if(locked){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }else{
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }
//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

int _width, _height;

void Application::GLFWCallbackWrapper::window_size_callback(GLFWwindow *window, int width, int height) {
//    printf("resize %d, %d\n", width, height);
    float ratio{(float)width/(float)height};
    application->camera.setPerspective(60, ratio, 0.1, 100);
    glViewport(0, 0, width, height);

    _width = width;
    _height = height;
}

void Application::GLFWCallbackWrapper::cursor_callback(GLFWwindow *window, double x, double y) {

    if(locked){

        float rotX = 100 * (float)(x - ((float)_width / 2)) / (float)_width;
        float rotY = 100 * (float)(y - ((float)_height / 2)) / (float)_height;

        application->camera.lookX(rotX);
        application->camera.lookY(rotY);

        glfwSetCursorPos(window, (float)_width/2, (float)_height/2);
    }
}

//TODO place shader code into their respective files
//TODO make all shaders using the new ShaderProgram and ShaderProgramHolder
//TODO maybe create singleton for ShaderProgram ?
Application::Application() {
    /*
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
                                             "      color = mix(vec4(colorA, 1), vec4(colorB, 1), pct);\n"
                                             "}"
                                             ,"#version 330\n"
                                                  "out vec4 frag_colour;"
                                                  "in vec4 color;"
                                                  "void main () {"
                                                  "    frag_colour = color;"
                                                  "}");
    shaderProgram.createShader("Constant", "#version 400\n"
                                             "layout(location=0) in vec4 vp;"
                                             "layout(location=1) in vec4 normal;"
                                             "out vec4 color;"
                                             "uniform mat4 MVP;"
                                             "uniform mat4 viewMatrix;"
                                             "uniform mat4 projectionMatrix;"

                                             "void main () {\n"
                                             "      gl_Position = projectionMatrix * viewMatrix * MVP * vp;\n"
                                             "}"
                                            ,"#version 330\n"
                                             "out vec4 frag_colour;"
                                             "in vec4 color;"
                                             "void main () {"
                                             "    frag_colour = vec4(0,0,0.35,1);"
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

    shaderProgram.createShader("Light", "#version 400\n"
                                        "layout(location=0) in vec3 vp;"
                                        "layout(location=1) in vec3 normal;"

                                        "uniform mat4 MVP;"
                                        "uniform mat4 viewMatrix;"
                                        "uniform mat4 projectionMatrix;"

                                        "out vec3 worldNormal;"
                                        "out vec3 worldPosition;"

                                        "void main () {\n"
                                        "      gl_Position = projectionMatrix * viewMatrix * MVP * vec4(vp, 1.0);\n"
                                        "      //\n"
                                        "      worldNormal = transpose(inverse(mat3(MVP))) * normal;\n"
                                        "      worldPosition = vec3(MVP * vec4(vp, 1.0));\n"
                                        "}"
                                        ,"#version 400\n"
                                         "out vec4 frag_colour;"
                                         "in vec3 worldNormal;"
                                         "in vec4 worldPosition;"
                                         "void main () {\n"
                                         "      vec3 lightPosition = vec3(0,0,0);\n"
                                         "      vec3 lightVector = vec3(0,10,0);\n"
                                         "      float diff = max(dot(normalize(lightPosition - vec3(worldPosition)), normalize(worldNormal)), 0.0);\n"
                                         "      vec4 ambient = vec4(0.01,0.1,0.1,1.0);\n"
                                         "      vec4 diffuse = diff * vec4(1,1,1,1)\n;"
                                         "      vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);\n"
                                         "      frag_colour = ( ambient + diffuse ) * objectColor ;\n"
                                         "}");

    shaderProgram.createShader("Phong", "#version 400\n"
                                        "layout(location=0) in vec3 vp;"
                                        "layout(location=1) in vec3 normal;"

                                        "uniform mat4 MVP;"
                                        "uniform mat4 viewMatrix;"
                                        "uniform mat4 projectionMatrix;"

                                        "out vec3 worldNormal;"
                                        "out vec3 worldPosition;"

                                        "void main () {\n"
                                        "      gl_Position = projectionMatrix * viewMatrix * MVP * vec4(vp, 1.0);\n"
                                        "      //\n"
                                        "      worldNormal = transpose(inverse(mat3(MVP))) * normal;\n"
                                        "      worldPosition = vec3(MVP * vec4(vp, 1.0));\n"
                                        "}"
                                        ,"#version 400\n"
                                         "out vec4 frag_colour;"
                                         "in vec3 worldNormal;"
                                         "in vec4 worldPosition;"
                                         ""
                                         "uniform vec3 cameraPosition;"
                                         "void main () {\n"
                                         "      vec3 lightPosition = vec3(0,0,0);\n"
                                         "      vec3 lightVector = vec3(0,10,0);\n"
                                         "      vec3 lightDirection = normalize(lightPosition - vec3(worldPosition));\n"
                                         "      float diff = max(dot(normalize(lightPosition - vec3(worldPosition)), normalize(worldNormal)), 0.0);\n"
                                         ""
                                         "      float specularLight = 0.50f;\n"
                                         "      vec3 reflectionDirection = reflect(-lightDirection, worldNormal);\n"
                                         "      vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));\n"
                                         "      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);\n"
                                         "      float specular = specAmount * specularLight;\n"
                                         ""
                                         "      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0);\n"
                                         "      vec4 diffuse = diff * vec4(1, 1, 1, 1)\n;"
                                         ""
                                         ""
                                         "      vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);\n"
                                         "      frag_colour = ( ambient + diffuse + specular )* objectColor ;\n"
                                         "}");

    shaderProgram.createShader("Blinn-Phong", "#version 400\n"
                                        "layout(location=0) in vec3 vp;"
                                        "layout(location=1) in vec3 normal;"

                                        "uniform mat4 MVP;"
                                        "uniform mat4 viewMatrix;"
                                        "uniform mat4 projectionMatrix;"

                                        "out vec3 worldNormal;"
                                        "out vec3 worldPosition;"

                                        "void main () {\n"
                                        "      gl_Position = projectionMatrix * viewMatrix * MVP * vec4(vp, 1.0);\n"
                                        "      //\n"
                                        "      worldNormal = transpose(inverse(mat3(MVP))) * normal;\n"
                                        "      worldPosition = vec3(MVP * vec4(vp, 1.0));\n"
                                        "}"
                                        ,"#version 400\n"
                                         "out vec4 frag_colour;"
                                         "in vec3 worldNormal;"
                                         "in vec4 worldPosition;"
                                         ""
                                         "uniform vec3 cameraPosition;"
                                         "void main () {\n"
                                         "      vec3 lightPosition = vec3(0,0,0);\n"
                                         "      vec3 lightVector = vec3(0,10,0);\n"
                                         "      vec3 lightDirection = normalize(lightPosition - vec3(worldPosition));\n"
                                         "      float diff = max(dot(normalize(lightPosition - vec3(worldPosition)), normalize(worldNormal)), 0.0);\n"
                                         ""
                                         "      vec3 halfwayDir = normalize ( lightDirection + cameraPosition );\n"
                                         "      float specularLight = 0.50f;\n"
                                         "      vec3 reflectionDirection = reflect(-lightDirection, worldNormal);\n"
                                         "      vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));\n"
                                         "      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);\n"
                                         "      vec3 specular = lightDirection * reflectionDirection * max((worldNormal * halfwayDir), 0);\n"
                                         ""
                                         ""
                                         ""
                                         ""
                                         "      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0);\n"
                                         "      vec4 diffuse = diff * vec4(1, 1, 1, 1)\n;"
                                         ""
                                         ""
                                         "      vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);\n"
                                         "      frag_colour = ( ambient + diffuse + vec4(specular,1) )* objectColor ;\n"
                                         "}");*/


//    camera.addObserver(shaderProgram.getShaderp("MainShader"));//TODO add for-each loop to shaderProgram
//    camera.addObserver(shaderProgram.getShaderp("Gradient"));
//    camera.addObserver(shaderProgram.getShaderp("Light"));
//    camera.addObserver(shaderProgram.getShaderp("Phong"));
//    camera.addObserver(shaderProgram.getShaderp("Blinn-Phong"));
//    camera.addObserver(shaderProgram.getShaderp("Constant"));


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

void Application::createShaders() {
    shaderProgramHolder.createShader("Gradient", new ShaderProgram(Shader("gradient.vert"), Shader("gradient.frag")));

    camera.addObserver(shaderProgramHolder.getShaderp("Gradient"));
}

//TODO create scene class
void Application::createModels() {

    camera.notify(); //initial render for camera. Shaders need to be created!

    switch(SCENE){
        case 0:
        {

            auto sphere0 = new Sphere(1.5,0,0);
            sphere0->setShader(shaderProgramHolder.getShaderp("Gradient"));

//            auto sphere1 = new Sphere(-1.5,0,0);
//            sphere1->setShader(shaderProgram.getShaderp("MainShader"));
//
//            auto sphere2 = new Sphere(0,1.5,0);
//            sphere2->setShader(shaderProgram.getShaderp("Light"));
//
//            auto sphere3 = new Sphere(0,-1.5,0);
//            sphere3->setShader(shaderProgram.getShaderp("MainShader"));
//
////    auto suziF = ModelFactory::createModel("suzi_flat", 0,0,0);
////    suziF->setShader(shaderProgram.getShaderp("MainShader"));
//
//
            shapes.push_back(unique_ptr<Shape>(sphere0));
//            shapes.push_back(unique_ptr<Shape>(sphere1));
//            shapes.push_back(unique_ptr<Shape>(sphere2));
//            shapes.push_back(unique_ptr<Shape>(sphere3));

//    shapes.push_back(unique_ptr<Shape>(suziF));

//    shapes[0]->scale(glm::vec3(0.3));

            break;
        }
        case 1:{

//            auto sphere0 = new Sphere(0,0,1.5);
//            sphere0->setShader(shaderProgram.getShaderp("Light"));
//            shapes.push_back(unique_ptr<Shape>(sphere0));
            break;
        }
        case 2:{

//            auto sphere0 = new Sphere(1.5,0,0);
//            sphere0->setShader(shaderProgram.getShaderp("Light"));
//
//            auto sphere1 = new Sphere(-1.5,0,0);
//            sphere1->setShader(shaderProgram.getShaderp("Light"));
//
//            auto sphere2 = new Sphere(0,1.5,0);
//            sphere2->setShader(shaderProgram.getShaderp("Light"));
//
//            auto sphere3 = new Sphere(0,-1.5,0);
//            sphere3->setShader(shaderProgram.getShaderp("Light"));
//
//            shapes.push_back(unique_ptr<Shape>(sphere0));
//            shapes.push_back(unique_ptr<Shape>(sphere1));
//            shapes.push_back(unique_ptr<Shape>(sphere2));
//            shapes.push_back(unique_ptr<Shape>(sphere3));

            break;
        }
        case 3:{

//            auto sphere0 = new Sphere(1.5,0,0);
//            sphere0->setShader(shaderProgram.getShaderp("Light"));
//
//            auto sphere1 = new Sphere(-1.5,0,0);
//            sphere1->setShader(shaderProgram.getShaderp("Phong"));
//
//            auto sphere2 = new Sphere(0,1.5,0);
//            sphere2->setShader(shaderProgram.getShaderp("Blinn-Phong"));
//
//            auto sphere3 = new Sphere(0,-1.5,0);
//            sphere3->setShader(shaderProgram.getShaderp("Constant"));
//
//            shapes.push_back(unique_ptr<Shape>(sphere0));
//            shapes.push_back(unique_ptr<Shape>(sphere1));
//            shapes.push_back(unique_ptr<Shape>(sphere2));
//            shapes.push_back(unique_ptr<Shape>(sphere3));

            break;
        }
    }


}

void Application::drawModels() {

    shaderProgramHolder.getShader("Gradient").setUniform("time", (float)glfwGetTime() );

    switch(SCENE){
        case 0:
        {
//            shapes[2]->rotate(glm::radians(1.f), glm::vec3(1,0,0));

            break;
        }
    }



    for (const auto &item : shapes){

        item->draw();
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
