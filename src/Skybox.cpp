#include <Skybox.h>
using namespace aw;
Skybox::Skybox(Camera *camera, const char *texture) : GameObject(
                                                          Mesh("Assets/Models/Cube.glb", texture),
                                                          Material(),
                                                          nullptr,
                                                          true,
                                                          4),
                                                      camera(camera) {}
void Skybox::start() {}
void Skybox::update() {}
void Skybox::draw()
{
    if (camera)
    {
        transform.setPosition(camera->transform.getPosition());
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);
        glPushMatrix();
        applyTransform();
        meshPtr->draw();
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glDepthMask(GL_TRUE);
    }
}