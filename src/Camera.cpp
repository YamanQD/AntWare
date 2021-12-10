#include <Camera.h>
using namespace aw;
Camera::Camera()
{
    aspectRatio = 4.0 / 3.0;
    FOV = 45.0f;
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}
Camera::Camera(float FOV, float aspectRatio) : FOV(FOV), aspectRatio(aspectRatio)
{
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
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