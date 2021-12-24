#include <Renderer.h>
using namespace aw;
Renderer::Renderer()
{
}
Renderer &Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}
void Renderer::init()
{
    glewExperimental = true;
    glewInit();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void Renderer::renderScene(Scene *scene)
{
    scene->camera.update();
    for (unsigned i = 0; i < scene->lights.size(); ++i)
    {
        scene->lights[i].update();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        scene->gameObjects[i]->draw();
    }
    glFlush();
    WINDOW.internal.display();
}
void Renderer::terminate()
{
}