#include <Skybox.h>
using namespace aw;
Skybox::Skybox(Camera *camera, const char *texture) : GameObject(
                                                          Mesh("Assets/Models/Skybox.glb", texture),
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
        glCullFace(GL_FRONT);
        transformationMat = applyTransform();
        glUniformMatrix4fv(GameObject::modelLocation, 1, GL_FALSE, &transformationMat[0][0]);
        meshPtr->draw();
        glDepthMask(GL_TRUE);
        glCullFace(GL_BACK);
    }
}