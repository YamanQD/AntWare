#include <Camera.h>
using namespace aw;
using namespace glm;
Camera::Camera(float FOV, float aspectRatio) : FOV(FOV), aspectRatio(aspectRatio)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Camera::setFOV(float FOV)
{
    this->FOV = FOV;
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}
void Camera::setAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}
void Camera::update()
{
    vec3 camPos = transform.getPosition();
    vec3 camDir = vec3(0, 0, -1);
    vec3 camUp = vec3(0, 1, 0);
    mat3 rotationMat = mat3(transform.getRotation());
    camDir = rotationMat * camDir;
    camUp = rotationMat * camUp;
    vec3 lookedAt = camDir + camPos;

    gluLookAt(camPos.x, camPos.y, camPos.z,
              lookedAt.x, lookedAt.y, lookedAt.z,
              camUp.x, camUp.y, camUp.z);
}