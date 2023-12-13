

#include "Application.h"

int main()
{
    Application app{};

    app.initialize();
    app.createShaders();
    app.createModels();
    app.run();


}