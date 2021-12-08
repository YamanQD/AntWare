#include <Renderer.h>
using namespace aw;
Renderer::Renderer() {}
Renderer &Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}
void Renderer::init()
{
    glewExperimental = true;
    glewInit();
}
void Renderer::terminate()
{
}