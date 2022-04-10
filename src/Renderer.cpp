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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Renderer::renderScene(Scene *scene)
{
    scene->camera.update();
    for (unsigned i = 0; i < scene->lights.size(); ++i)
    {
        scene->lights[i].update();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->skybox.draw();
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        if (i == 1)
            continue; // muzzle
        if (scene->gameObjects[i]->getClass() == CLASSES::ANT)
            continue; // Draw ants last for better transpernecy
        scene->gameObjects[i]->draw();
    }
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        if (scene->gameObjects[i]->getClass() != CLASSES::ANT)
            continue;
        scene->gameObjects[i]->draw();
    }
    glDisable(GL_LIGHTING);
    scene->gameObjects[1]->draw();
    glEnable(GL_LIGHTING);
    HUD.draw();
    glFlush();
    WINDOW.internal.display();
}
void Renderer::terminate()
{
}